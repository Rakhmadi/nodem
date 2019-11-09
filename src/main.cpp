//ByRakhmadiwalker ////
#include <Arduino.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include <SPI.h>
#include <MFRC522.h>
//cridential hospot
const char *ssid="HexaTera";
const char *pass="qwertyuiop";
WiFiServer server(80);
#define SS_PIN 5
#define RST_PIN 4
MFRC522 mrfc255( SS_PIN, RST_PIN );
void setup() {
  delay(1000);
  Serial.begin(9600);
  SPI.begin();
  mrfc255.PCD_Init();

  WiFi.mode(WIFI_OFF);
  delay(1000);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,pass);
  Serial.print("  ");
  Serial.print("connecting");
  
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
    Serial.print("\n-----------------------------------");
    Serial.print("\nTersambung ke : ");
    Serial.print(ssid);
    Serial.print("\n-----------------------------------");
    Serial.print("\nIp Address    : ");
    Serial.print(WiFi.localIP());
    Serial.print("\n-----------------------------------");
    }

void loop() {
  if( ! mrfc255.PICC_IsNewCardPresent()){
    return;
  }
  if(mrfc255.PICC_ReadCardSerial()){
    return;
  }
   //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mrfc255.uid.size; i++) 
  {
     Serial.print(mrfc255.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mrfc255.uid.uidByte[i], HEX);
     content.concat(String(mrfc255.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mrfc255.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "BD 31 15 2B") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    delay(3000);
  }
 
 else   {
    Serial.println(" Access denied");
    delay(3000);
  }
} 

