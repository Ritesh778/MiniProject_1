#define BLYNK_TEMPLATE_ID "TMPLLlDZUwKM"
#define BLYNK_DEVICE_NAME "firealarm"
#define BLYNK_AUTH_TOKEN "hGvK2hSNSxOZ_5jJ6C4c04vgBDnW69P0"
#include <ESP8266WiFi.h>


// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "realme 6";
char pass[] = "jyotsna4502";
//WidgetLCD lcd(V4);
BlynkTimer timer;
int pinValue = 0;

#define LED1 D1
//#define LED2 D4
#define Buzzer D3
#define Sensor D0


// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V0) {
  pinValue = param.asInt();
}
BLYNK_CONNECTED() {
  // Request the latest state from the server
  Blynk.syncVirtual(V0);
}

// This function is called every time the device is connected to the Blynk.Cloud

// This function sends Arduino's uptime every second to Virtual Pin 2.
void notifiaction() {
  int sensor = digitalRead(Sensor);
  if (pinValue == 1) {

    Serial.println("System is ON");
    if (sensor == 1) {
      //digitalWrite(LED2, HIGH);
      digitalWrite(LED1, LOW);
      digitalWrite(Buzzer, LOW);
    } else {
      Blynk.logEvent("filealarm","FIRE ALERT!!!");
      //Blynk.email("kud91719@gmail.com", "Subject", "Parigettu");
      //digitalWrite(LED2, LOW);
      digitalWrite(LED1, HIGH);
      digitalWrite(Buzzer, HIGH);
      
    }
  } else{

    Serial.println("System is OFF");
  }
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  pinMode(LED1, OUTPUT);
  //pinMode(LED2, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(Sensor, INPUT);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,150), 8080);

  // Setup a function to be called every second
  timer.setInterval(1000L, notifiaction);
}

void loop()
{
  Blynk.run();
  timer.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}
