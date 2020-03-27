package com.example.lightcontextstate;


import org.eclipse.paho.client.mqttv3.MqttCallback;
import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttException;

import java.util.ArrayList;


/*La classe permet de communiquer avec l'Arduino via le broker mqtt et permet ainsi de mettre à jour
l'état des lumières*/

public class LightContextMqttManager {
    private ContextManagementActivity activity;
    private MqttClient mqttClient;
    private MqttCallback mqttCallback;
    private ArrayList<LightContextStateListener> listeners = new ArrayList<>();

    LightContextMqttManager(ContextManagementActivity activity,MqttClient mqttClient){
        this.activity=activity;
        mqttCallback=new LightContextMqttCallback(this);
        this.mqttClient=mqttClient;
        this.mqttClient.setCallback(mqttCallback);
        listeners.add(activity);

    }
    LightContextMqttManager(ContextManagementActivity activity,String server, String client){
        this.activity=activity;
        try {
            this.mqttClient = new MqttClient(server, client);
        } catch (IllegalArgumentException ex){

        }
        catch (MqttException e){
            e.printStackTrace();
        }
        mqttCallback=new LightContextMqttCallback(this);
        mqttClient.setCallback(mqttCallback);
        listeners.add(activity);

    }

    public void connect(){
        try {
            mqttClient.connect();
        }
        catch(MqttException e){
            e.printStackTrace();
        }
    }

    public void subscribe(String topicFilter){
        try {
            mqttClient.subscribe(topicFilter);
        }
        catch(MqttException e){
            e.printStackTrace();
        }

    }

    public ContextManagementActivity getActivity(){return activity;}

    public ArrayList<LightContextStateListener> getListeners() {
        return listeners;
    }

    public MqttClient getMqttClient() {
        return mqttClient;
    }
}