#include <LiquidCrystal.h>

int digPin8 = 8;
int digPin9 = 9;
int digPin10 = 10;
int contrast = 60;

LiquidCrystal lcd(11, 12, 2, 3, 4, 5);

void setup() {
  // put your setup code here, to run once:
  pinMode(digPin8, HIGH);
  pinMode(digPin9, HIGH);
  pinMode(digPin10 , HIGH);

  lcd.begin(16, 2);
  analogWrite(6, contrast);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  digitalWrite(digPin8, HIGH);
  lcd.setCursor(0, 0);
  lcd.print("Moteur pin 8");
  delay(1000);
  lcd.clear();
  
  digitalWrite(digPin8, LOW);
  lcd.setCursor(0, 0);
  lcd.print("Moteur pin 8");
  delay(1000);
  lcd.clear();
  
  digitalWrite(digPin9, HIGH);
  lcd.setCursor(0, 0);
  lcd.print("Moteur pin 9");
  delay(1000);
  lcd.clear();
  
  
  digitalWrite(digPin9, LOW);
  lcd.setCursor(0, 0);
  lcd.print("Moteur pin 9");
  delay(1000);
  lcd.clear();
  
  digitalWrite(digPin10, HIGH);
  lcd.setCursor(0, 0);
  lcd.print("Moteur pin 10");
  delay(1000);
  lcd.clear();
  
  digitalWrite(digPin10, LOW);
  lcd.setCursor(0, 0);
  lcd.print("Moteur pin 10");
  delay(1000);
  lcd.clear();
}
