#include "Wire.h"
#include <LiquidCrystal.h>

// Déclaration des pins au relai/moteur 
#define moteur1 8
#define moteur2 9
#define moteur3 10

// Déclaration de l'écran LCD
const int contrast = 60;
const int rs = 11, en = 12, d4 = 2, d5 = 3, d6 = 4, d7 = 5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Déclaration du joystick et ces directions
#define VRy A0
#define SW 13
// ❴✠❵┅━━━━━━┅❴✠❵
#define up 0
#define down 1
#define enter 2
#define none 3
// ❴✠❵┅━━━━━━┅❴✠❵
int lastJoystickRead;

// ❴✠❵┅━━━ Boolean ━━━┅❴✠❵
bool preparationEnCours = false;
bool premiereSelection = false;

// ❴✠❵┅━━━ Variables ━━━┅❴✠❵
int pageActuelle = 0;


// Fonction d'utilisation du Joystick
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
        output = down;
    } else if (yAxis <= -400)
    {
        output = up;
    }
    return output;
}

void moveUp(){
    if (pageActuelle == 3)
    {
        pageActuelle = 0;
    } else {
        pageActuelle++;
    }
    menuSelection();
}

void moveDown(){
    if (pageActuelle == 0)
    {
        pageActuelle = 3;
    } else {
        pageActuelle--;
    }
    menuSelection();
}

void setup() {
  // put your setup code here, to run once:
  pinMode(moteur1, OUTPUT);
  digitalWrite(moteur1, HIGH);

  pinMode(moteur2, OUTPUT);
  digitalWrite(moteur2, HIGH);

  pinMode(moteur3, OUTPUT);
  digitalWrite(moteur3, HIGH);

  lcd.begin(16, 2);
  analogWrite(6, contrast);

  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP);

  lcd.print("Bienvenue !");
}

void loop() {
    int currentJoystickRead = readJostick();
    
    if (currentJoystickRead != lastJoystickRead)
    {
    lastJoystickRead = currentJoystickRead;

    digitalWrite(moteur1, HIGH);

    if (preparationEnCours == false) {
        switch (currentJoystickRead){
            case up :
                moveUp();
                break;
            case down : 
                moveDown();
                break;
            case enter :
                if (premiereSelection == false) {
                    pageConfirmation();
                }
                else if (premiereSelection == true) {
                    lancementMoteur();  
                }
                
                break;
            default : break;
        }
    }
  } 
}

void menuSelection () {
    lcd.clear();
    lcd.setCursor(0,0);

    premiereSelection = false;

    if (pageActuelle == 0) {
      lcd.print("Aucun cocktail");
    } else if (pageActuelle == 1) {
      lcd.print("Whisky coca");
    } else if (pageActuelle == 2) {
      lcd.print("Cocktail deux");
    } else if (pageActuelle == 3) {
      lcd.print("Purger machine");
    }    
}

void pageConfirmation(){
    lcd.clear();
    lcd.setCursor(0,0);

    if (pageActuelle == 0)
    {
      lcd.print("Aucun cocktail");
      lcd.setCursor(0,1);
      lcd.print("selectionne");
    }

    else if (pageActuelle == 1) {
        premiereSelection = true;
        lcd.print("Lancer le");
        lcd.setCursor(0,1);
        lcd.print("Whisky coca ?");
    } 

    else if (pageActuelle == 2) {
        premiereSelection = true;
        lcd.print("Lancer le");
        lcd.setCursor(0,1);
        lcd.print("Cocktail deux ?");
    }

    else if (pageActuelle == 3) {
        premiereSelection = true;
        lcd.print("Lancement de");
        lcd.setCursor(0,1);
        lcd.print("la purge ?");
    }
}

void lancementMoteur() {
    lcd.clear();
    lcd.setCursor(0,0);

    if (pageActuelle == 1) {
        premiereSelection = false;
        preparationEnCours = true;
        lcd.print("Debut du");
        lcd.setCursor(0,1);
        lcd.print("Whisky coca");
        FonctionCocktailAlcool();
    } 

    else if (pageActuelle == 2) {
        premiereSelection = false;
        preparationEnCours = true;
        lcd.print("Debut du");
        lcd.setCursor(0,1);
        lcd.print("Cocktail deux");
        FonctionCocktailSansAlcool();
    }

    else if (pageActuelle == 3) {
        premiereSelection = false;
        preparationEnCours = true;
        lcd.print("Debut de la");
        lcd.setCursor(0,1);
        lcd.print("purge !");
        FonctionPurger();
    }
}

void FonctionCocktailAlcool() {
    digitalWrite(moteur1, LOW);
    digitalWrite(moteur2, LOW);
    delay(4500);
    digitalWrite(moteur1, HIGH);
    delay(25500);
    digitalWrite(moteur2, HIGH);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Fin de la");
    lcd.setCursor(0,1);
    lcd.print("Preparation !");

    preparationEnCours = false;
}

void FonctionCocktailSansAlcool() {
    digitalWrite(moteur1, LOW);
    digitalWrite(moteur2, LOW);
    digitalWrite(moteur3, LOW);
    delay(4500);
    digitalWrite(moteur3, HIGH);
    delay(2500);
    digitalWrite(moteur1, HIGH);
    delay(12500);
    digitalWrite(moteur2, HIGH);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Fin de la");
    lcd.setCursor(0,1);
    lcd.print("Preparation !");

    preparationEnCours = false;
}

void FonctionPurger() {
    digitalWrite(moteur1, LOW);
    delay(30000);
    digitalWrite(moteur1, HIGH);

    digitalWrite(moteur2, LOW);
    delay(30000);
    digitalWrite(moteur2, HIGH);

    digitalWrite(moteur3, LOW);
    delay(30000);
    digitalWrite(moteur3, HIGH);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Fin de la");
    lcd.setCursor(0,1);
    lcd.print("purge !");

    preparationEnCours = false;
}
