package com.example.lightcontextstate;

import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.MqttCallback;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;

/*La classe indique ce qui doit être fait lorsqu'un message Mqtt arrive*/

public class LightContextMqttCallback implements MqttCallback {
    LightContextMqttManager mqttManager;

    LightContextMqttCallback(LightContextMqttManager mqttManager){
        this.mqttManager=mqttManager;
    }

    @Override
    public void connectionLost(Throwable cause) {
        cause.printStackTrace();
    }

    @Override
    public void messageArrived(String topic, MqttMessage message) throws Exception {
        String m=message.toString();
        LightContextState lcs=getLightContextState(m);
        if (lcs!=null&&lcs.getId()==mqttManager.getActivity().getLightId()) {
            ArrayList<LightContextStateListener> listeners = mqttManager.getListeners();
            for (int i = 0; i < listeners.size(); i++) {
                listeners.get(i).onUpdate(lcs);
            }
        }

    }

    @Override
    public void deliveryComplete(IMqttDeliveryToken token) {
        try {
            String m = token.getMessage().toString();

            LightContextState lcs = getLightContextState(m);
            if (lcs != null) {
                ArrayList<LightContextStateListener> listeners = mqttManager.getListeners();
                for (int i = 0; i < listeners.size(); i++) {
                    listeners.get(i).onUpdate(lcs);
                }
            }
        }
        catch (MqttException e){
            e.printStackTrace();
        }

    }

    public LightContextState getLightContextState(String m){
        JSONObject obj=new JSONObject();
        long id=0;
        String status=new String();
        int bri=0;
        int colour=0;
        int sat=0;

        try {
            JSONObject json = new JSONObject(m);

            id=json.getLong("id");
            status = json.getJSONObject("state").getString("on");
            bri = json.getJSONObject("state").getInt("bri");
            colour = json.getJSONObject("state").getInt("hue");
            sat = json.getJSONObject("state").getInt("sat");
        }
        catch(JSONException e){
            e.printStackTrace();
        }

        LightContextState lcs=new LightContextState(id,status,bri,colour,sat);



        return lcs;
    }
}
