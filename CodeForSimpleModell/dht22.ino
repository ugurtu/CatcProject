#include "DHT.h"

#define DHTPIN 2 //Pin Nummer wo der Sensor angeschlossen ist
#define DHTTYPE DHT22 //Definition was fuer ein Sensor ausgelesen wird.
#define pinRed 4 // LEDPin4
#define pinGreen 5 //LEDPin5

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //Serial.println("DHT22 Testprogramm");
  pinMode(pinRed, OUTPUT);
  pinMode(pinGreen, OUTPUT);

  dht.begin();

}

void loop() {
  delay(2000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Fehler beim auslesen des Sensors!");
    return;
  }

  if (t >= 15.00 && t <= 18.00) {
    digitalWrite(pinRed, LOW);
    digitalWrite(pinGreen, HIGH);
  }
  else  {
    digitalWrite(pinGreen,LOW);
    digitalWrite(pinRed, HIGH);
    
  }
   
   Serial.print(digitalRead(pinRed));
   Serial.print(" ");
   Serial.print(digitalRead(pinGreen));
   Serial.print(" ");
   Serial.println(t);


}
