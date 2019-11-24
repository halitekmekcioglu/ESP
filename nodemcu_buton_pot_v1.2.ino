/*
static const uint8_t D0   = 16;
static const uint8_t D1   = 5;
static const uint8_t D2   = 4;
static const uint8_t D3   = 0;
static const uint8_t D4   = 2;
static const uint8_t D5   = 14;
static const uint8_t D6   = 12;
static const uint8_t D7   = 13;
static const uint8_t D8   = 15;
static const uint8_t D9   = 3;
static const uint8_t D10  = 1;
*/

bu bir denemedir


#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "ssid";
const char* password = "pwd";
const char* mqtt_server = "iot.eclipse.org";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
int lp =0;
int np=0;
char msg[50];
int value = 0;
char mesaj[50];
int msj=0;
int valb=0;

int A =16;    //Butonlar denenmiştir.
int B=5;
int C=4;
int D=0;

int AS = 0; 
int BS = 0; 
int CS = 0; 
int DS = 0;

int LED =2;
void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  if ((char)payload[0] == '1') {
    digitalWrite(LED, LOW); } 
    else {
    digitalWrite(LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
     // client.publish("OTEPT", "hello world");
      // ... and resubscribe
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {

 
pinMode(A, INPUT);
pinMode(B, INPUT);
pinMode(C, INPUT);
pinMode(D, INPUT);
pinMode(LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

}

void loop() {
 AS=digitalRead(A);
  BS=digitalRead(B);
   CS=digitalRead(C);
    DS=digitalRead(D);

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
 if (now - lastMsg > 100) {
     lastMsg = now;

      int np = analogRead(A0);
 if (abs(np - lp) >= abs(5)) {
     lp = np;
    
    int val=analogRead(A0);
     String msg="Joystik X ekseni degeri: ";
     msg= msg+ val;
     char message[58];
     msg.toCharArray(message,58);
     Serial.println(message);
  
     //publish sensor data to MQTT broker 

      client.publish("OTEPT", message);
    

    
      // butons

      if(AS==false){
      String msj=" A BUTONUNA BASILDI:";
    msj= msj+ millis();   
     msj.toCharArray(mesaj,50);
     Serial.println(mesaj);
  
     //publish sensor data to MQTT broker 

      client.publish("OTEPT", mesaj);
      }
      
        if(BS==false){
      String msj=" B BUTONUNA BASILDI";
     msj.toCharArray(mesaj,50);
     Serial.println(mesaj);
  
     //publish sensor data to MQTT broker 

      client.publish("OTEPT", mesaj);
      }
      
        if(CS==false){
      String msj=" C BUTONUNA BASILDI:";   
     msj.toCharArray(mesaj,50);
     Serial.println(mesaj);
  
     //publish sensor data to MQTT broker 

      client.publish("OTEPT", mesaj);
      }
      
      
        if(DS==false){
      String msj=" D BUTONUNA BASILDI:";   
     msj.toCharArray(mesaj,50);
     Serial.println(mesaj);
  
     //publish sensor data to MQTT broker 

      client.publish("OTEPT", mesaj);
      }
      
  }
 }
/*
  
    AS=digitalRead(A);
  if(AS==LOW){
   //digitalWrite(LED, HIGH);
   Serial.println("AAAAAAAA aktif");
   }
  //else{ digitalWrite(LED, LOW);}
  
  BS=digitalRead(B);
  if(BS==LOW){
  //digitalWrite(LED, HIGH);
   //Serial.println("BBBBBBBBB aktif");
   }
   
 
  CS=digitalRead(C);
  if(CS==LOW){
      // digitalWrite(LED, HIGH);
   Serial.println("CCCCCCCCCCCCCCCCC aktif");
   }
  //else{ digitalWrite(LED, LOW);}
    
   DS=digitalRead(D);
  if(DS==LOW){
     // digitalWrite(LED, HIGH);
   Serial.println("DDDDDDDDDD aktif");
   }
    //else{ digitalWrite(LED, LOW);}
    delay(500);
    */
}
