#include "Arduino.h"
#include "LTimer.h"
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11

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
Serial.print(F("% Temperature: "));
Serial.print(t);
Serial.print(F("'C "));
Serial.print(f);
Serial.print(F("'F Heat index: "));
Serial.print(hic);
Serial.print(F("'C "));
Serial.print(hif);
Serial.println(F("'F"));
}

void setup() {
Serial.begin(9600);
Serial.println(F("DHTxx test!"));

dht.begin();


timer1.begin();


timer1.start(1000, LTIMER_REPEAT_MODE, _callback1, NULL);
}

void loop() {

dht.readTemperature();

}
