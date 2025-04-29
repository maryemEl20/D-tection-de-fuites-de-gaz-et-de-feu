/*
**les bibliothèques nécessaires pour utiliser le capteur DHT, le servo-moteur et l'écran LCD.
*/
#include <DHT.h>
#include <Servo.h>
#include <LiquidCrystal.h>
//Définition des Broches et des Variables
#define DHTTYPE DHT11  // Type du capteur DHT
#define DHTPIN 8
/* Change the threshold value with your own reading */
#define Threshold 40
#define RedLed 6
#define GreenLed 13
#define smoke A0
#define flame 10
#define buzzer 7
//Initialisation des Composants
  DHT dht(DHTPIN, DHTTYPE);
  Servo myservo; 
const int rs = 12, en = 9, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
float sensorValue;  //variable to store sensor value
int sensorflame;
//Configuration Initiale
void setup() {
  lcd.begin(16, 2);
  delay(100);
  dht.begin();
  pinMode(flame,INPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(GreenLed,OUTPUT);
  pinMode(RedLed,OUTPUT);
  pinMode(smoke,INPUT);
  myservo.attach(11);
  Serial.begin(9800);

}

void loop() {
  // Lecture des capteurs de fumée et de flamme
  sensorflame = digitalRead(flame);
  sensorValue = analogRead(smoke); //read analog input 

// Contrôle des LEDs, du servo-moteur et du buzzer en fonction des lectures
    if(sensorValue > Threshold or sensorflame == HIGH)
  {
    // Serial.println(" | Smoke detected!");
    digitalWrite(RedLed,HIGH);
    digitalWrite(GreenLed,LOW);
    myservo.write(250);
    tone(buzzer, 500,200); // Allumer le buzzer pour 250 ms à une fréquence de 500 Hz (LED rouge)
    delay(100);

  }else{
    digitalWrite(GreenLed,HIGH);
    digitalWrite(RedLed,LOW);
    myservo.write(-250);
    noTone(buzzer);
  }
  // Affichage de la température et de l'humidité sur l'écran LCD
  float temp = dht.readTemperature();  // Lire la température
  float humid = dht.readHumidity();

    if (isnan(humid) || isnan(temp) ) {
        Serial.println(F("Failed to read from DHT sensor!"));
        delay(500);
        return;
      }
  
  // Serial.print("Temperature en Celsius: ");
  // Serial.println(temp);

  // Affichage de la température sur l'écran LCD
  lcd.clear();  // Effacer l'écran LCD
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print(" C");
  
  lcd.setCursor(0, 1);
  lcd.print("Humid: ");
  lcd.print(humid);
  lcd.print(" %");
  delay(200); //Pause entre les lectures
//Falme and Sensor
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sensor Flame: ");
  lcd.print(sensorflame);
  lcd.setCursor(0, 1);
  lcd.print("Sensor gas: ");
  lcd.print(sensorValue);
  delay(200);

  //

  delay(50); // wait 2s for next reading

}
