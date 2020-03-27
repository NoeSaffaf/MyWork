package com.example.lightcontextstate;

import android.app.Activity;
import android.widget.Toast;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.JsonObjectRequest;
import com.android.volley.toolbox.Volley;

import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;


/* La classe permet de communiquer avec le serveur*/

public class LightContextHttpManager {

    private RequestQueue queue;
    private Activity activity;
    private ArrayList<LightContextStateListener> listeners=new ArrayList<>();
    String CONTEXT_SERVER_URL="https://faircorp-tortures-ninjas.cleverapps.io/api/lights/";

    LightContextHttpManager(ContextManagementActivity activity){
        this.activity=activity;
        this.queue= Volley.newRequestQueue(activity);
        listeners.add(activity);
    }

    void switchLight(Long id){
        String url=CONTEXT_SERVER_URL+id+"/switch";
        JsonObjectRequest contextRequest = new JsonObjectRequest
                (Request.Method.PUT, url, null, new Response.Listener<JSONObject>() {

                    @Override
                    public void onResponse(JSONObject response) {
                        try {
                            String id = response.getString("id");
                            if( response.getString("status").equals("ON")){
                                response.put("status","OFF");

                            }
                            else{
                                response.put("status","ON");
                            }
                            Toast.makeText(activity,"Succes",Toast.LENGTH_LONG);
                        } catch (JSONException e) {
                            e.printStackTrace();
                        }

                    }
                }, new Response.ErrorListener() {

                    @Override
                    public void onErrorResponse(VolleyError error) {
                        // Some error to access URL : Room may not exists...
                        Toast toast= Toast.makeText(activity,"erreur: La lumière n'existe pas",Toast.LENGTH_SHORT);
                        toast.show();
                    }
                });
        queue.add(contextRequest);

    }

    void retrieveLightContextState(Long id) {
        /* Toast essaiToast=Toast.makeText(activity,"Debut HTTP",Toast.LENGTH_LONG);
         essaiToast.show();*/


        String url = CONTEXT_SERVER_URL+ id + "/";

        //get room sensed context
        JsonObjectRequest contextRequest = new JsonObjectRequest
                (Request.Method.GET, url, null, new Response.Listener<JSONObject>() {

                    @Override
                    public void onResponse(JSONObject response) {
                        try {
                            long id = response.getLong("id");
                            String lightStatus =response.getString("status");
                            int bri=response.getInt("bri");
                            int colour=response.getInt("colour");
                            int sat=response.getInt("sat");
                            // do something with results...
                            // notify main activity for update...
                            LightContextState state=new LightContextState(id,lightStatus,bri,colour,sat);
                            Toast toast= Toast.makeText(activity,lightStatus,Toast.LENGTH_SHORT);
                            toast.show();
                            //liste.add(alarmReceiver);
                            for (int i=0;i<listeners.size();i++){
                                listeners.get(i).onUpdate(state);
                            }
                        } catch (JSONException e) {
                            e.printStackTrace();
                        }

                    }
                }, new Response.ErrorListener() {

                    @Override
                    public void onErrorResponse(VolleyError error) {
                        // Some error to access URL : Room may not exists...
                        Toast toast= Toast.makeText(activity,"erreur",Toast.LENGTH_SHORT);
                        toast.show();
                    }
                });
        queue.add(contextRequest);

    }

    public void setColour(Long id,String colour){
        String url=CONTEXT_SERVER_URL+id+"/set-light-"+colour;
        JsonObjectRequest contextRequest = new JsonObjectRequest
                (Request.Method.PUT, url, null, new Response.Listener<JSONObject>() {

                    @Override
                    public void onResponse(JSONObject response) {
                        try {
                            long id = response.getLong("id");
                            String lightStatus =response.getString("status");
                            int bri=response.getInt("bri");
                            int colour=response.getInt("colour");
                            int sat=response.getInt("sat");
                            // do something with results...
                            // notify main activity for update...
                            LightContextState state=new LightContextState(id,lightStatus,bri,colour,sat);
                            Toast toast= Toast.makeText(activity,lightStatus,Toast.LENGTH_SHORT);
                            toast.show();
                            for (int i=0;i<listeners.size();i++){
                                listeners.get(i).onUpdate(state);
                            }
                        } catch (JSONException e) {
                            e.printStackTrace();
                        }

                    }
                }, new Response.ErrorListener() {

                    @Override
                    public void onErrorResponse(VolleyError error) {
                        // Some error to access URL : Room may not exists...
                        Toast toast= Toast.makeText(activity,"erreur: La lumière n'existe pas",Toast.LENGTH_SHORT);
                        toast.show();
                    }
                });


        queue.add(contextRequest);

    }

}
