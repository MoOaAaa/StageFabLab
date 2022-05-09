#include <LiquidCrystal.h>
#include "Wire.h"

#define moteur1 8
#define moteur2 9
#define moteur3 10

// Définition des cocktails
char str1[] = "a";
char str2[] = "b";
char str3[] = "c";
const char pages[] = {str1, str2, str3};
bool cocktailSelectionne = false;
bool preparationEnCours = false;

const int moteurs[] = {moteur1, moteur2, moteur3};

//LCD part
const int contrast = 60;
const int rs = 11, en = 12, d4 = 2, d5 = 3, d6 = 4, d7 = 5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//Joystick pin
#define VRy A0
#define SW 13

//Joystick values
#define up 0
#define down 1
#define enter 2
#define none 3

int currentMotorWorking;
int lastJoystickRead;

// Compteur pour la sélection du cocktail
int pageActuelle;



int readJostick(){
    int output = none;

    int yAxis = analogRead(VRy); //read Y axis value
    yAxis = map(yAxis, 0, 1023, -512, 512);
   
    int switchValue = digitalRead(SW); // read switch button value
    switchValue = map(switchValue, 0, 1, 1, 0);  // invert the input from the switch to be high when pressed

    if (switchValue == 1)
    {
        output = enter; 
    } else if (yAxis >= 400)
    {
        output = up;
    } else if (yAxis <= -400)
    {
        output = down;
    }

    return output;
}

void moveUp(){
    if (pageActuelle <= 0)
    {
        pageActuelle = (int)sizeof(pages)/sizeof(pages[0]) - 1;
    }else{
        pageActuelle--;
    }  
    menuSelection(pageActuelle);
}

void moveDown(){
    if (pageActuelle >= (int)sizeof(pages)/sizeof(pages[0]) - 1)
    {
        pageActuelle = 0;
    }else{
        pageActuelle++;
    }
    menuSelection(pageActuelle);
}

void clicked(){
    // Reset de l'écran
    lcd.clear();

    lcd.setCursor(0,0);
    if (pageActuelle == 0)
    {
      lcd.print("Aucun cocktail");
      lcd.setCursor(0,1);
      lcd.print("selectionne");
    }
    // Si nous sommes à la deuxième page alors 
    else if (pageActuelle == 1) {
        cocktailSelectionne = true;
        lcd.print("Lancer le");
        lcd.setCursor(0,1);
        lcd.print("Miami drink ?");
    } 
    // Si nous sommes à la troisième page alors
    else {
        cocktailSelectionne = true;
        lcd.print("Lancer le");
        lcd.setCursor(0,1);
        lcd.print("Lemon paradise");
    }
}

void lancerCreation() {
    // Reset de l'écran
    lcd.clear();

    lcd.setCursor(0,0);
    // Si nous sommes à la deuxième page alors 
    if (pageActuelle == 1) {
        cocktailSelectionne = false;
        preparationEnCours = true;
        lcd.print("Lancement du");
        lcd.setCursor(0,1);
        lcd.print("Miami drink");
    } 
    // Si nous sommes à la troisième page alors
    else {
        cocktailSelectionne = false;
        preparationEnCours = true;
        lcd.print("Lancement du");
        lcd.setCursor(0,1);
        lcd.print("Lemon paradise");
    }
}

void menuSelection (int pageActuelleMenu) {
    // Reset de l'écran
    lcd.clear();
    cocktailSelectionne = false;

    // Première ligne
    lcd.setCursor(0,0);
    // Si nous sommes à la première page alors
    if (pageActuelleMenu == 0)
    {
      lcd.print("Choisir cocktail");
    }
    // Si nous sommes à la deuxième page alors 
    else if (pageActuelleMenu == 1) {
        lcd.print("Miami drink");
    } 
    // Si nous sommes à la troisième page alors
    else {
        lcd.print("Lemon paradise");
    }

    // Deuxième ligne
    lcd.setCursor(0,1);
    lcd.print("Faire defiler");
}

void setup() {
  // put your setup code here, to run once:
  pinMode(moteur1, OUTPUT);
  pinMode(moteur2, OUTPUT);
  pinMode(moteur3, OUTPUT);

  lcd.begin(16, 2);
  analogWrite(6, contrast);

  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP);
}

void loop() {
    // put your main code here, to run repeatedly:
    if (preparationEnCours == false) {
        int currentJoystickRead = readJostick();
    }
    
    if (currentJoystickRead != lastJoystickRead)
    {
    lastJoystickRead = currentJoystickRead;
      
    for (int moteur : moteurs){
      analogWrite(moteur, LOW);
    }

    switch (currentJoystickRead){
        case up :
            moveUp();
            break;
        case down : 
            moveDown();
            break;
        case enter :
            if (cocktailSelectionne == false) {
                clicked();
            }
            else if (cocktailSelectionne == true) {
                lancerCreation();  
            }
            
            break;
        default : break;
    }
  } 
}
