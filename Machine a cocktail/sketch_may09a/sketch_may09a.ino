#include <LiquidCrystal.h>

int moteur1 = 8;
int moteur2 = 9;
int moteur3 = 10;
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
  
  digitalWrite(moteur1, HIGH);
  lcd.setCursor(0, 0);
  lcd.print("Moteur pin 8 en cours");
  delay(1000);
  lcd.clear();
  
  digitalWrite(moteur1, LOW);
  lcd.setCursor(0, 0);
  lcd.print("Moteur pin 8 terminé");
  delay(1000);
  lcd.clear();
  
  digitalWrite(moteur2, HIGH);
  lcd.setCursor(0, 0);
  lcd.print("Moteur pin 9 en cours");
  delay(1000);
  lcd.clear();
  
  
  digitalWrite(moteur2, LOW);
  lcd.setCursor(0, 0);
  lcd.print("Moteur pin 9 terminé");
  delay(1000);
  lcd.clear();
  
  digitalWrite(moteur3, HIGH);
  lcd.setCursor(0, 0);
  lcd.print("Moteur pin 10 en cours");
  delay(1000);
  lcd.clear();
  
  digitalWrite(moteur3, LOW);
  lcd.setCursor(0, 0);
  lcd.print("Moteur pin 10 terminé");
  delay(1000);
  lcd.clear();
}
