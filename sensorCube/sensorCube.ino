 #include "DHT.h"
  
  #define DHTPIN 50 //Pin Nummer wo der Sensor angeschlossen ist
  #define DHTTYPE DHT22 //Definition was fuer ein Sensor ausgelesen wird.
  
  
  //initializing and declaring led rows
    int column[16]={48,46,44,42,40,38,36,34,32,30,28,26,24,22,A4,A5};
    
  //initializing and declaring led layers
    int layer[4]={A3,A2,A1,A0};
  // Setup
  
    float h = 0;
    float t = 0;
  
  long randNumber;
    int time = 250;
  
   DHT dht(DHTPIN, DHTTYPE);
   
  void setup()
  {
    //setting rows to ouput
    for(int i = 0; i<16; i++)
    {
      pinMode(column[i], OUTPUT);
    }
    //setting layers to output
    for(int i = 0; i<4; i++)
    {
      pinMode(layer[i], OUTPUT);
    }
    //seeding random for random pattern
    randomSeed(analogRead(10));
    Serial.begin(9600);
    dht.begin();
  }
  
  // The Loop
  void loop(){
    
     h = dht.readHumidity();
     t = dht.readTemperature();
     printTemp();

     if(t < 15.00){
      coldSleepTemp();
       printTemp();     
     }

    if (t >= 18.00 ){
      hotSleepTemp();
      printTemp();
     }

    else{
      if(h < 40.00){
        downUpRain();
        printTemp();
      }
      if(h >= 60.00){
        topDownRain();
        printTemp();
      }
      else{
        goodForSleeping();
        printTemp();
      }
     }
  }

  void coldSleepTemp()
    {
      int x = 75;
      for(int i = 0; i<4; i++)
      {
        digitalWrite(layer[i], 0);
      }
      for(int y = 0; y<5; y++)
      {
        for(int count = 0; count<1; count++)
        { 
          for(int i = 4; i>0; i--)
          {
            digitalWrite(layer[i], 1);
            delay(x);
            digitalWrite(layer[i], 0);
          }
          for(int i = 4; i !=0; i--)
          {
            digitalWrite(layer[i-1], 1);
            delay(x);
            digitalWrite(layer[i-1], 0);
          }
        }
        for(int i = 0; i<4; i++)
        {
          digitalWrite(layer[i], 1);
          delay(x);
        }
        for(int i = 4; i!=0; i--)
        {
          digitalWrite(layer[i-1], 0);
          delay(x);
        }
          printTemp(); 
      }
    }
  
    void hotSleepTemp() {
    turnEverythingOff();
    int x = 90;
    for(int y = 4; y>0; y--) {
      for(int i = 0; i<6; i++) {
        //turn on layer
        digitalWrite(layer[y-1], 1);
        //a1
        turnColumnsOff();
        digitalWrite(column[0], 0);
        digitalWrite(column[5], 0);
        digitalWrite(column[10], 0);
        digitalWrite(column[15], 0);
        delay(x);
        //b1
        turnColumnsOff();
        digitalWrite(column[4], 0);
        digitalWrite(column[5], 0);
        digitalWrite(column[10], 0);
        digitalWrite(column[11], 0);
        delay(x);
        //c1
        turnColumnsOff();
        digitalWrite(column[6], 0);
        digitalWrite(column[7], 0);
        digitalWrite(column[8], 0);
        digitalWrite(column[9], 0);
        delay(x);
        //d1
        turnColumnsOff();
        digitalWrite(column[3], 0);
        digitalWrite(column[6], 0);
        digitalWrite(column[9], 0);
        digitalWrite(column[12], 0);
        delay(x);
        //d2
        turnColumnsOff();
        digitalWrite(column[2], 0);
        digitalWrite(column[6], 0);
        digitalWrite(column[9], 0);
        digitalWrite(column[13], 0);
        delay(x);
        //d3
        turnColumnsOff();
        digitalWrite(column[1], 0);
        digitalWrite(column[5], 0);
        digitalWrite(column[10], 0);
        digitalWrite(column[14], 0);
        delay(x);
      }
        printTemp(); 
     }
      //d4
      turnColumnsOff();
      digitalWrite(column[0], 0);
      digitalWrite(column[5], 0);
      digitalWrite(column[10], 0);
      digitalWrite(column[15], 0);
      delay(x);
      printTemp(); 
    }

    void topDownRain() {
      turnEverythingOff();
      int x = 100;
      for(int i = 0; i!=60; i+=2) {
        int randomColumn = random(0,16);
        digitalWrite(column[randomColumn], 0);
        digitalWrite(layer[3], 1);
        delay(x+50);
        digitalWrite(layer[3], 0);
        digitalWrite(layer[2], 1);
        delay(x+115);
        digitalWrite(layer[2], 0);
        digitalWrite(layer[1], 1);
        delay(x+250);
        digitalWrite(layer[1], 0);
        digitalWrite(layer[0], 1);
        delay(x+50);
        digitalWrite(layer[0], 0);
        digitalWrite(column[randomColumn], 1);
         h = dht.readHumidity();
         t = dht.readTemperature();
        printTemp();
      }
    }
  
  void downUpRain()
  {
    turnEverythingOff();
    int x = 100;
    for(int i = 0; i!=60; i+=2)
    {
      int randomColumn = random(0,16);
      digitalWrite(column[randomColumn], 0);
      digitalWrite(layer[0], 1);
      delay(x+50);
      digitalWrite(layer[0], 0);
      digitalWrite(layer[1], 1);
      delay(x+115);
      digitalWrite(layer[1], 0);
      digitalWrite(layer[2], 1);
      delay(x+250);
      digitalWrite(layer[2], 0);
      digitalWrite(layer[3], 1);
      delay(x+50);
      digitalWrite(layer[3], 0);
      digitalWrite(column[randomColumn], 1);
     h = dht.readHumidity();
     t = dht.readTemperature();
     printTemp();
    }
  }

    void goodForSleeping()
  {
    turnEverythingOff();
    int x = 1000;
    for(int i = 0; i<16; i++)
    {
      digitalWrite(column[i], 0);
    }
    //turning on layers
    for(int i = 0; i<2; i++)
    {
      digitalWrite(layer[i], 1);
    }
    delay(x);
  }
  
  void turnColumnsOff()
  {
    for(int i = 0; i<16; i++)
    {
      digitalWrite(column[i], 1);
    }
      printTemp(); 
  }
  
  void printTemp(){
     h = dht.readHumidity();
     t = dht.readTemperature();
     Serial.print("Humidity in % ");
     Serial.print(h);
     Serial.print(" Temperature in °C: ");
     Serial.println(t); 
    }
    
  void turnEverythingOn() {
    for(int i = 0; i<16; i++)
    {
      digitalWrite(column[i], 0);
    }
    //turning on layers
    for(int i = 0; i<4; i++)
    {
      digitalWrite(layer[i], 1);
    }
  }
  
  void turnEverythingOff() {
     for(int i = 0; i<16; i++)
     {
       digitalWrite(column[i], 1);
     }
     for(int i = 0; i<4; i++)
     {
       digitalWrite(layer[i], 0);
     }
   }
