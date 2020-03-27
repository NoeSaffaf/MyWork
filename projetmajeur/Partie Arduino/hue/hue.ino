/* Ce code arduino constitue notre partie du projet de majeur du group SAFFAF/LEMEE/SOARES DE PAULA
Ce code permet d'une part, d'interagir avec le serveur par des requetes mqtt, d'autre part, interagir avec le broker,
et donc au Philips hue.

Il est donc possible de modifier les paramatres suivants, via des requettes MQTT venant du serveur.

Status: ON / OFF
Brightness: 0 à 255
Color: 0 à 65025
Saturation: 0 à 255  

Il est aussi possible de modifier le Brightness grace au potentiomètre, et le status grace au bouton du hardware.
ATENTION! CELA N'AFFECTE QUE LA LAMPE DESIGNEE(soit la 17), si il y a plusieurs lampes, les autres ne sont pas affectés.

Le code est écrit pour plusieurs lampes, et le fonctionnement du code est le suivant:

Via le Wifi, on instancie un client MQTT et on se connecte au broker. On se subscribe au bon poste, puis, lors de la réception d'un message.
On décortique le JSON recu  

La librairie Mqtt est MQTT.h, la librairie http est ArduinoHttpClient.h

*/




#include <string.h>

#include <SPI.h>
#include <WiFiNINA.h>
#include <ArduinoHttpClient.h>
#include <ArduinoJson.h>
#include <MQTT.h>


//#define POTENTIOMETER_PIN A4 
#define POTENTIOMETER_PIN 3 




/*On instancie les paramètres nécéssaires pour établir les connections*/
 
const char* wifi_ssid     = "lab-iot-1";
const char* wifi_password = "lab-iot-1"; 

const char* mqtt_host ="max.isasecret.com";
const uint16_t mqtt_port =1723; 
String ID = "484";


String idlight="1";

String maintopiclight = "api";
String topiclight = "torturesNinjas/arduino/light/";
String topicserver="torturesNinjas/server/light";

/* In which pins is my buttons plugged? */
#define BUTTON_PIN 1 /*1*/

/* Des Variables pour nos mesures */
int potentiometerValue;
int buttonState = 0;         
int lastState=0;
int lastValue=0;

/* Des Variables pour nos ID/Identifiants */
String m_username="LSJjZEVvDAkXGIZIl8n-g2KEAzAZfGRpgH3fCgW5";


uint32_t t0, t ;

/* Temps défini. */
#define DELTA_T 1000

/* Des objets WIFI et MQTT*/
WiFiClient wifi_client;
MQTTClient mqtt_client;
IPAddress address(192,168,1,131);
HttpClient client(wifi_client,address,80);

String contenttype = "application/x-www-form-urlencoded";

/*Le mqtt est-il connecté*/
bool mqtt_connected;

/*Méthode pour demander un authentifiant (username) à philips hue*/
String getUsername(){

	/*Nous postons une requete http pour obtenir un username avec la méthode post*/
    client.beginRequest();
    client.sendHeader("Content-Type", "text/plain");

    client.post("{\"devicetype\": \"my_hue_app#monarduino\"}");
    String bufferUsername = client.readString();
    Serial.print("bufferUsername : ");
    Serial.println(bufferUsername);
	
	
    /*On stocke la réponse dans un JSON alloué, puis nous extrayons le username donné via un parsing sur arduino, cette méthode n'est pas utilisé*/
    const int capacity=JSON_OBJECT_SIZE(1);
    StaticJsonDocument<capacity> usernameJSON;
    DeserializationError err=deserializeJson(usernameJSON, bufferUsername);
    String username="";

    if(err) {
      Serial.print(F("deserializeJson() failed with code "));
      Serial.println(err.c_str());
    }

    else {
  
      username=String((char) usernameJSON["success"]["username"]);
      Serial.print("Votre Username est : \n");
      Serial.print(username);
      Serial.print("\n");
    }
    
    return username;
}



/*Avec le username, on effectue un post pour connaitre toute les lumieres disponible (fonctionnement similaire que pour le username, méthode non plus utilisé)*/
int* getNewLights(){

    String monurl="http://192.168.1.131/api/"+m_username+"/lights";
    client.beginRequest();
    int httpCode = client.get(monurl);
   
    if (httpCode > 0) { //on verifie que la requete fonctionne
        Serial.println("On est ici");
        String bufferlist = client.readString();
        int malistID[100];
        Serial.println(bufferlist);

        const int capacity=50000;
        StaticJsonDocument<capacity> listJSON;
        DeserializationError err=deserializeJson(listJSON, bufferlist);
        
        if(err) {
          Serial.print(F("deserializeJson() failed with code "));
          Serial.println(err.c_str());
         }

        else { // On parcours la liste des lampes pour stocker les ID"
          JsonObject obj=listJSON.as<JsonObject>();
          int i = 0;
		  
          for(auto kv: obj) {
            
			      const char* lampeID=kv.key().c_str();
				    malistID[i]=atoi(lampeID);
				    i++;  
			    }                                      
       }       
       return malistID;
    }
 
    else {
      Serial.println((String) httpCode);
      Serial.println("La requtte GETnewlights ne fonctionne pas !\n");
    }
}


/*A partir d'une ID, on peut récupérer le contenu d'une lampe, cette méthode renvoie un JSON Object*/
JsonObject getJSONlampe(String id){

    String monurl="http://192.168.1.131/api/"+m_username+"/lights/"+id;
    client.beginRequest();
    int httpCode = client.get(monurl);
   
    if (httpCode > 0) { //on verifie que la requete fonctionne
      
        String bufferlist = client.readString();
        Serial.print(bufferlist);
        Serial.print("\n");

        //remplacer a json_objectsize(2) par le nombre de lampe+1
        const int capacity=JSON_ARRAY_SIZE(2) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(10);
        StaticJsonDocument<capacity> listJSON;
        DeserializationError err=deserializeJson(listJSON, bufferlist);
        
        if(err) {
          Serial.print(F("deserializeJson() failed with code "));
          Serial.println(err.c_str());
         }

        else {
          
          JsonObject obj=listJSON.as<JsonObject>();   
          return obj;                                      
          }
        }        
      
 
    else {
      Serial.println("La requête GET ne fonctionne pas !\n");
    }
}


/*Cette Méthode envoie au serveur (par requete MQTT) les données d'une lampe selon son ID*/
void sendMessage(String id){
  JsonObject json=getJSONlampe(id);
  json["id"]=atol(id.c_str());
  String message;
  //json.print(message);
  serializeJson(json,message);
  mqtt_client.publish(topiclight.c_str(),message.c_str());
  Serial.println("Json envoyé : ");
  Serial.println(message);
}


/*Méthode put qui change le brightness selon l'ID renseigné par requete HTTP au broker*/
void changeBrightness(uint8_t bri, String id ){

    String monurl="http://192.168.1.131/api/"+m_username+"/lights/"+id+"/state";
    client.beginRequest();
    client.sendHeader("Content-Type", "text/plain");

    String Stringbri = String((char)bri);
    
    String myBody="{\"bri\":"+Stringbri+"}"; 
    client.put(monurl,contenttype,myBody);
}


/*Méthode put qui change le color selon l'ID renseigné par requete HTTP au broker*/
void changeColor(uint16_t color , String id ){

    String monurl="http://192.168.1.131/api/"+m_username+"/lights/"+id+"/state";
    client.beginRequest();
    client.sendHeader("Content-Type", "text/plain");

    String Stringcolor = String((char)color);
    String myBody="{\"hue\":"+Stringcolor+"}"; 
    
    client.put(monurl,contenttype,myBody);     
}


/*Méthode qui change la saturation selon l'ID renseigné par requete HTTP au broker*/
void changeSaturation(uint8_t sat , String id ){

    String monurl="http://192.168.1.131/api/"+m_username+"/lights/"+id+"/state";
    client.beginRequest();
    client.sendHeader("Content-Type", "text/plain");

    String Stringsat = String((char)sat);
    String myBody="{\"hue\":"+Stringsat+"}"; 
    
    client.put(monurl,contenttype,myBody);        
}


/*Méthode qui change le state selon l'ID renseigné par requete HTTP au broker*/
void changeState(String state, String id ){

    Serial.print("bonjour");
    String monurl="http://192.168.1.131/api/"+m_username+"/lights/"+id+"/state";
    client.beginRequest();
    client.sendHeader("Content-Type", "text/plain");
    String myBody="";
    if (strcmp(state.c_str(),"ON")){
      myBody="{\"on\":true}"; 
    }
    else if (strcmp(state.c_str(),"OFF")){
      myBody="{\"on\":false}";
    }
    Serial.print(myBody);
    client.put(monurl,contenttype,myBody);
}


/*Méthode qui prend un string qui est en fait un JSON Object, et appelle les méthodes de changement de paramètres en fonctions du contenu du JSON*/
void callback(String &intopic, String &payload) {
  Serial.print("bonjour");
  Serial.print(payload);
  const int capacity= JSON_OBJECT_SIZE(5); 
  StaticJsonDocument<capacity> listJSON;
  DeserializationError err=deserializeJson(listJSON, payload);
        
        if(err) {
          Serial.print(F("deserializeJson() failed with code "));
          Serial.println(err.c_str());
         }

        else {
          
          JsonObject obj=listJSON.as<JsonObject>();    
          String id= String((char)obj["id"]);
          String state=String((char)obj["status"]);
          uint8_t bri=(uint8_t) obj["bri"];
          uint16_t hue=(uint16_t) obj["hue"];
          uint8_t sat=(uint8_t) obj["sat"];
          changeState(state,id);
          changeBrightness(bri,id);
          changeColor(hue,id);
          changeSaturation(sat,id);
		  
		  /*On envoie un message pour indiqué au serveur que les modifications ont bien été traitées*/
          sendMessage(id);
          }  
}


/* Initialisation de notre arduino avec MQTT, HTTP, etc.. */
void setup() {
  Serial.begin(9600) ;
  delay(100) ;
  Serial.println("Initializing...\n") ;

  // On initialise nos pins
  pinMode(POTENTIOMETER_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT);

  // Time begins now!
  t0 = t = millis() ;

  WiFi.begin(wifi_ssid, wifi_password); 

  mqtt_connected=false;

}


void loop() {  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("En attente de connexion WiFi\n");
    delay(500);
    WiFi.begin(wifi_ssid, wifi_password);  
  }

  if (!mqtt_connected){
    mqtt_client.begin(mqtt_host,mqtt_port, wifi_client);
    delay(500);
    mqtt_client.connect("","majinfo2019","Y@_oK2");
    mqtt_client.subscribe(String(topicserver).c_str());
    mqtt_client.onMessage(callback);
    mqtt_connected=true;  
    Serial.print("Mqtt connecté :");
    Serial.println(String(mqtt_client.connected()));
  }   

  /*int* m_malistID=getNewLights();
  Serial.println(m_malistID[0]);*/
 
          
  t = millis() ;
  if ( (t - t0) >= DELTA_T ) {
    t0 = t ;

	/*On attend un message du serveur, puis on appelle la méthode callback en cas de réponse*/
    

    buttonState = digitalRead(BUTTON_PIN);
    potentiometerValue = digitalRead(POTENTIOMETER_PIN); 

    Serial.print("potentiometer value: ");
    Serial.print(potentiometerValue);

    Serial.print(" ; button value: ");
    Serial.println(buttonState);

    //On allume ou eteind la lampe via le bouton sur le hardware SUR LA LAMPE 17 UNIQUEMENT
   
      if (!lastState==buttonState){
        changeState(String(buttonState), String(17));
        //sendMessage(String(17));
      }
    

    // On change l'intensité de la la lampe via le potentiomètre sur le hardware SUR LA LAMPE 17 UNIQUEMENT
    // On verifie que l'intensité est modifiée de plus ou moins 5
 
      if (potentiometerValue>lastValue+5 || potentiometerValue<lastValue-5 ){
        uint8_t value = (uint8_t) potentiometerValue;
        changeBrightness(value,String(17));
        sendMessage(String(17));
      }
    

    lastState=buttonState;
    lastValue=potentiometerValue;
  }
}
