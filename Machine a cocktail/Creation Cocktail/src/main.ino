#include "Wire.h"
#include <LiquidCrystal.h>
#include "GestionMenu.h"

// Déclaration des pins au relai/moteur 
#define moteur1 8
#define moteur2 9
#define moteur3 10

#define vitesseMoteur1 1.8
#define vitesseMoteur2 1.9
#define vitesseMoteur3 1.5

// Déclaration de l'écran LCD
const int contrast = 60;
const int rs = 11, en = 12, d4 = 2, d5 = 3, d6 = 4, d7 = 5;
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Déclaration du joystick et ces directions
#define VRy A0
#define VRx A1
#define SW 13
// ❴✠❵┅━━━━━━┅❴✠❵
#define up 0
#define down 1
#define right 2
#define left 3
#define enter 4
#define none 5
// ❴✠❵┅━━━━━━┅❴✠❵
int lastJoystickRead;

// ❴✠❵┅━━━ Boolean ━━━┅❴✠❵
bool preparationEnCours = false;
bool premiereSelection = false;
bool creationEnCours = false;

// ❴✠❵┅━━━ Variables ━━━┅❴✠❵
int pageActuelle = 0;
int moteurPreparationActuel = 0;

int quantiteMoteur1 = 0;
int quantiteMoteur2 = 0;
int quantiteMoteur3 = 0;

GestionMenu menu(moteur1, moteur2, moteur3,
                vitesseMoteur1, vitesseMoteur2, vitesseMoteur3,
                rs, en, d4, d5, d6, d7,
                VRy, VRx, SW);

void setup() {
  // put your setup code here, to run once:
  pinMode(moteur1, OUTPUT);
  digitalWrite(moteur1, HIGH);

  pinMode(moteur2, OUTPUT);
  digitalWrite(moteur2, HIGH);

  pinMode(moteur3, OUTPUT);
  digitalWrite(moteur3, HIGH);

  menu.lcd.begin(16, 2);
  analogWrite(6, contrast);

  pinMode(VRy, INPUT);
  pinMode(VRx, INPUT);
  pinMode(SW, INPUT_PULLUP);

  menu.lcd.print("Bienvenue !");
}

void loop() {
    int currentJoystickRead = menu.readJostick();
    
    if (currentJoystickRead != lastJoystickRead)
    {
    lastJoystickRead = currentJoystickRead;


    if (preparationEnCours == false) {
        switch (currentJoystickRead){
            case up :
                 menu.moveUp();
                break;
            case down : 
                menu.moveDown();
                break;
            case right :
                if (creationEnCours == true)
                {
                    menu.moveRight();
                }
                break;
            case left : 
                if (creationEnCours == true){
                    menu.moveLeft();
                } else{
                    break;
                }
            case enter :
                if (premiereSelection == false) {
                    menu.pageConfirmation();
                }
                else if (premiereSelection == true) {
                    menu.lancementMoteur();  
                }
                else if (premiereSelection == true){
                    menu.lancementCreation();
                }
                
                break;
            default : break;
        }
    }
  } 
}