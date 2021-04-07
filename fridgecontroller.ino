#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#define BLYNK_PRINT Serial   

char auth[] = "----------------";
char ssid[] = "---------"; //Enter WIFI Name
char pass[] = "---------"; //Enter WIFI Password


float vref = 3.3;
float resolution = vref / 1023.0;
float temperature;


SimpleTimer timer;
 
int mq2 = A0; // smoke sensor is connected with the analog pin A0 
int data = 0; 
void setup() 
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, getSendData);
  timer.setInterval(2000, sendUptime);
}

void sendUptime()
{
  float temperature = analogRead(A1);//lm35 is connected to pin A0 on NodeMcu
  temperature = (temperature * resolution);
  temperature = temperature * 100.0;
  Serial.print("LM35 temperature: ");//serial print the value 
  Serial.println(temperature);
  Blynk.virtualWrite(V0, temperature);//send the value to blynk application
}

void loop() 
{
  timer.run(); // Initiates SimpleTimer
  Blynk.run();
}

void getSendData()
{
data = analogRead(mq2); 
  Blynk.virtualWrite(V2, data);
 
  if (data > 700 )
  {
    Blynk.notify("Smoke Detected!"); 
  }
 
}
