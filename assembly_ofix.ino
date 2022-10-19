//library & deklarasi LCD
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

//variable ultrasonik
float Rpump = 2;
int const Trig = 10;
int const Echo = 9;
int duration, distance;
int jarakx;

//varibale photodioda
int pin = A0;
int Rphoto = 3;

void setup() {
  //LCD
  lcd.init();// initialize the lcd 
  pinMode(pin, INPUT);
  pinMode(Rphoto, OUTPUT);
  Serial.begin(9600);

  //ultrasonik
   Serial.begin(9600);
   pinMode(Trig, OUTPUT);
   pinMode(Echo, INPUT);
   pinMode(Rpump, OUTPUT);
}

void loop() 
{
  //photodioda
  int data = analogRead(pin);
  delay(1000);

  //LCD photodioda
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("K=");
  lcd.setCursor(3,0);
  lcd.print(data);
  Serial.print("Kekeruhan= ");
  Serial.println(data);

  //Perulangan photodioda
    if(data>1000)
  {
    digitalWrite(Rphoto, HIGH);
    lcd.setCursor(7,0);
    lcd.print("AirKeruh");
    delay(1000);
  }
  else
  {
  digitalWrite(Rphoto, LOW);
  lcd.setCursor(7,0);
  lcd.print("AirJernih");
  }
  
  //ultrasonik
  digitalWrite(Trig, LOW);
  delayMicroseconds(10);
  digitalWrite(Trig, HIGH); 
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);

  duration = pulseIn(Echo, HIGH);
  distance = (duration/2)/29.1;
  Serial.print("jarak= ");
  Serial.println(distance);
  delay(10);

  //LCD ultrasonik
  lcd.backlight();
  lcd.setCursor(0,1);
  lcd.print("J=");
  lcd.setCursor(3,1);
  lcd.print(distance);
  
  //perulangan ultrasonik
  if(distance > 30)
  {
  digitalWrite(Rpump, HIGH);
  lcd.setCursor(6,1);
  lcd.print("TinggiMin");
  }
  else if (distance < 10)
  {
  digitalWrite(Rpump, LOW);
  lcd.setCursor(6,1);
  lcd.print("TinggiMax");
  }
}
