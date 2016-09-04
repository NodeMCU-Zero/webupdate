/*
  To upload through terminal you can use: curl -F "image=@firmware.bin" esp8266-webupdate.local/update
*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>

const char* host = "algobel-webupdate";
const char* ssid = "TP";
const char* password = "12345678";

ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater;
String webPage = "";

void setup(void){

  Serial.begin(115200);
  Serial.println();
  Serial.println("Booting Sketch...");
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(ssid, password);

  while(WiFi.waitForConnectResult() != WL_CONNECTED){
    WiFi.begin(ssid, password);
    Serial.println("WiFi failed, retrying.");
  }

  MDNS.begin(host);

  httpUpdater.setup(&httpServer);
  httpServer.begin();

  MDNS.addService("http", "tcp", 80);
  Serial.printf("HTTPUpdateServer ready! Open http://%s.local/update in your browser\n", host);

  pinMode(D1,OUTPUT);
}

void loop(void){
  httpServer.handleClient();
  LED();
  yield();  
}

void LED (){
  unsigned long A = millis();
  digitalWrite(D1,HIGH);
  delay(1000);
  digitalWrite(D1,LOW);
  delay(1000);
  Serial.print("Time : ");
  Serial.println((millis()-A));
  
}
