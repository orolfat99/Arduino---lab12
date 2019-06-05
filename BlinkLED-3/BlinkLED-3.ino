
#include <WiFiClient.h>
#include "MCS.h"
#include "Arduino.h"
#include "LTimer.h"
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
#define _SSID "orolfat99"
#define _KEY  "0960033155"
MCSDevice mcs("D3JKaerJ", "FmzseMuAXrwW6PqX");
MCSDisplayFloat Temp("Temperature");
MCSDisplayFloat Humidity("Humidity");
float h;
float t ;
float f ;
float hif ;

float hic ;
DHT dht(DHTPIN, DHTTYPE);
// instantiation

LTimer timer1(LTIMER_1);


void _callback1(void *usr_data)
{
  h = dht.readHumidity();

  t = dht.readTemperature();

   f = dht.readTemperature(true);


  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  
   hif = dht.computeHeatIndex(f, h);
 
  hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("'C "));
  Serial.print(f);
  Serial.print(F("'F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("'C "));
  Serial.print(hif);
  Serial.println(F("'F"));
}

void setup() {
  Serial.begin(9600);
  while(WL_CONNECTED != WiFi.status())
  {
    Serial.print("WiFi.begin(");
    Serial.print(_SSID);
    Serial.print(",");
    Serial.print(_KEY);
    Serial.println(")...");
    WiFi.begin(_SSID, _KEY);
  }
  Serial.println("WiFi connected !!");

  // setup MCS connection
  mcs.addChannel(Humidity);
   mcs.addChannel(Temp);
  while(!mcs.connected())
  {
    Serial.println("MCS.connect()...");
    mcs.connect();
  }
  Serial.println("MCS connected !!");

  Serial.println(F("DHTxx test!"));
  dht.begin();
  timer1.begin();
  timer1.start(10000, LTIMER_REPEAT_MODE, _callback1, NULL);
}

void loop() {
  mcs.process(100);
   Temp.set(hic);
   Humidity.set(h);
dht.readTemperature();

}
