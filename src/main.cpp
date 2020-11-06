#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#include <OneWire.h>
#include <DallasTemperature.h>
   
// Set WiFi credentials
#define WIFI_SSID "Deco15"
#define WIFI_PASS "greenballoon560"
#define UDP_PORT 515

// UDP
WiFiUDP UDP;
char packet[255];
char reply[] = "Packet received!";
char reply1[] = "ESP_Easy_DS1TEMP_Temperature=41.5";
IPAddress iplox(192, 168, 1, 12);

// Set your Gateway IP address
IPAddress local_IP(192, 168, 1, 100);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 0, 0);

const int pinCidlaDS = 2;

// vytvoření instance oneWireDS z knihovny OneWire
OneWire oneWireDS(pinCidlaDS);
// vytvoření instance senzoryDS z knihovny DallasTemperature
DallasTemperature senzoryDS(&oneWireDS);
   
void setup() {
  // Setup serial port
  Serial.begin(9600);
  Serial.println("Serial begin");

  senzoryDS.begin();

  // Configures static IP address
  if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("STA Failed to configure");
  }

  // Begin WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASS);
   
  // Connecting to WiFi...
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  // Loop continuously while WiFi is not connected
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
   
  // Connected to WiFi
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

/*
  // Begin listening to UDP port
  UDP.begin(UDP_PORT);
  Serial.print("Listening on UDP port ");
  Serial.println(UDP_PORT);
*/
   
}
   
void loop() {
  senzoryDS.requestTemperatures();
  Serial.print("Teplota cidla DS18B20: ");
  int teplota = senzoryDS.getTempCByIndex(0);
  Serial.print(senzoryDS.getTempCByIndex(0));
  Serial.println(" stupnu Celsia");
  /* 
  // If packet received...
  int packetSize = UDP.parsePacket();
  if (packetSize) {

    
    Serial.print("Received packet! Size: ");
    Serial.println(packetSize);
    int len = UDP.read(packet, 255);
    if (len > 0)
    {
      packet[len] = '\0';
    }
    Serial.print("Packet received: ");
    Serial.println(packet);
    */
    // Send return packet
    //UDP.beginPacket(UDP.remoteIP(), UDP.remotePort());
    UDP.beginPacket(iplox, 515);
    //UDP.write(reply);
    //char numstr[30]; // enough to hold all numbers up to 64-bits
    //reply = reply1 + itoa(teplota, numstr, 10);



    //char numstr[34]; // enough to hold all numbers up to 64-bits
    //sprintf(numstr, "%d", teplota);
    //reply = reply1 + numstr; 



    UDP.write(reply);
    UDP.endPacket();

    delay(5000);
    //ESP.deepSleep(10e6, RF_DEFAULT);
  //}
 
}
