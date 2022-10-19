//library & deklarasi LCD
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

//variable ultrasonik
float Rpump = 10;
int const Trig = 12;
int const Echo = 13;
int duration, distance;
int jarakx;
int data;

//varibale photodioda
int pin = A0;
int Rphoto = 11;


//photodioda

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

  //LCD photodioda
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("K=");
  lcd.setCursor(3,0);
  lcd.print(data);
  Serial.print("Kekeruhan= ");
  Serial.println(data);
  delay(1000);

  //Perulangan photodioda
    if(data>800)
  {
    digitalWrite(Rphoto, HIGH);
    lcd.setCursor(7,0);
    lcd.print("Air Keruh");
  }
  else
  {
  digitalWrite(Rphoto, LOW);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("K=");
  lcd.setCursor(3,0);
  lcd.print(data);
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
  jarakx = constrain(distance, 12, 23);
  if(distance >= 24)
  {
  digitalWrite(Rpump, HIGH);
  lcd.setCursor(7,1);
  lcd.print("TinggiMin");
  }
  else if (distance <=11)
  {
  digitalWrite(Rpump, LOW);
  lcd.setCursor(7,1);
  lcd.print("TinggiMax");
  }
  else if(distance == jarakx)
  {
  lcd.setCursor(7,1);
  lcd.print("AirSurut");
  }
}
