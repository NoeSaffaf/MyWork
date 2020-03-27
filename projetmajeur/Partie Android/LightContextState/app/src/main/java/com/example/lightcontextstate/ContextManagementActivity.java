package com.example.lightcontextstate;

import android.app.Activity;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.Menu;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import com.example.roomcontextstate.R;

import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttException;

public class ContextManagementActivity extends Activity implements LightContextStateListener {

    private LightContextState state;
    private LightContextHttpManager httpManager;
    private LightContextMqttManager mqttManager;
    private long lightId;



    /*Initialisation de l'application */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        httpManager = new LightContextHttpManager(this);
        MqttClient mqttClient;
        try{
            mqttClient=new MqttClient("tcp://max.isasecret.com:1723",MqttClient.generateClientId());
            MqttConnectOptions option=new MqttConnectOptions();
            String password="Y@_oK2";
            String username="majinfo2019";
            option.setPassword(password.toCharArray());
            option.setUserName(username);
            mqttClient.connect(option);
            mqttClient.subscribe("torturesNinjas/arduino/light");
            this.mqttManager=new LightContextMqttManager(this,mqttClient);
        }
        catch (MqttException e){
            e.printStackTrace();
            Toast.makeText(this,"Connexion Mqtt échouée",Toast.LENGTH_SHORT);
        }
        setContentView(R.layout.activity_main);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }
    /*Getter*/

    public long getLightId(){return lightId;}



    /* Ensemble des méthodes pour mettre à jour les données sur la lumière et les afficher*/
    public void onUpdate(LightContextState state) {
        this.lightId=state.getId();
        this.state=state;
        updateContextView();
    }


    private void updateContextView() {
        if (this.state != null) {
            TextView contextView = new TextView(this);
            contextView.setVisibility(View.VISIBLE);
            ((TextView) findViewById(R.id.textViewBriValue)).setText(Integer
                    .toString(state.getBri()));
            ((TextView) findViewById(R.id.textViewColourValue)).setText(Integer
                    .toString(state.getColour()));
            ((TextView) findViewById(R.id.textViewSatValue)).setText(Integer
                    .toString(state.getSat()));
            if (state.getStatus().equals(LightContextState.ON)) {
                ((ImageView) findViewById(R.id.imageView1)).setImageResource(R.drawable.ic_bulb_on);
            }
            else {
                ((ImageView) findViewById(R.id.imageView1)).setImageResource(R.drawable.ic_bulb_off);
            }
        } else {
            initView();
        }

    }

    private void initView() {
        httpManager.retrieveLightContextState(lightId);
    }

    /* Ensemble des méthodes correspondant aux boutons*/
    public void checkLight(View view){
        String light=((EditText) findViewById(R.id.editText1)).getText().toString();
        this.lightId = Long.valueOf(light).longValue();
        httpManager.retrieveLightContextState(lightId);
    }

    public void switchLight(View view){
        httpManager.switchLight(lightId);
        httpManager.retrieveLightContextState(lightId);
    }

    public void setLightRed(View view) {
        httpManager.setColour(lightId, "red");
        httpManager.retrieveLightContextState(lightId);
    }


    public void setLightGreen(View view){

        httpManager.setColour(lightId, "green");
        httpManager.retrieveLightContextState(lightId);
    }

    public void setLightBlue(View view){

        httpManager.setColour(lightId, "blue");
        httpManager.retrieveLightContextState(lightId);
    }




}
