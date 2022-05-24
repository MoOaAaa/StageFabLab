#include <LiquidCrystal.h>
#include "Wire.h"

#pragma once

// ❴✠❵┅━━━━━━┅❴✠❵
#define up 0
#define down 1
#define right 2
#define left 3
#define enter 4
#define none 5

class GestionMenu {
    private :
        int mn_moteur1;
        int mn_moteur2;
        int mn_moteur3;

        float mn_vitesseMoteur1;
        float mn_vitesseMoteur2;
        float mn_vitesseMoteur3;

        int mn_VRy;
        int mn_VRx;
        int mn_SW;

        // ❴✠❵┅━━━━━━┅❴✠❵
        int lastJoystickRead;

        // ❴✠❵┅━━━ Variables ━━━┅❴✠❵
        int pageActuelle = 0;
        int moteurPreparationActuel = 0;

        int quantiteMoteur1 = 0;
        int quantiteMoteur2 = 0;
        int quantiteMoteur3 = 0;

    public :
        // ❴✠❵┅━━━ Boolean ━━━┅❴✠❵
        bool preparationEnCours = false;
        bool premiereSelection = false;
        bool creationEnCours = false;

        LiquidCrystal lcd;    

        GestionMenu(int moteur1, int moteur2, int moteur3, float vitesseMoteur1, float vitesseMoteur2, float vitesseMoteur3,
                    int rs, int en, int d4, int d5, int d6, int d7,
                    int VRy, int VRx, int SW) :
                    lcd(rs,en,d4,d5,d6,d7)
        {
            mn_moteur1 = moteur1;
            mn_moteur2 = moteur2;
            mn_moteur3 = moteur3;

            mn_vitesseMoteur1 = vitesseMoteur1;
            mn_vitesseMoteur2 = vitesseMoteur2;
            mn_vitesseMoteur3 = vitesseMoteur3;

            mn_VRx = VRx;
            mn_VRy = VRy;
            mn_SW = SW;

        }

        // Fonction d'utilisation du Joystick
        int readJostick(){
            int output = none;

            int yAxis = analogRead(mn_VRy); //read Y axis value
            yAxis = map(yAxis, 0, 1023, -512, 512);

            int xAxis = analogRead(mn_VRx); //read X axis value
            xAxis = map(xAxis, 0, 1023, -512, 512);
        
            int switchValue = digitalRead(mn_SW); // read switch button value
            switchValue = map(switchValue, 0, 1, 1, 0);  // invert the input from the switch to be high when pressed

            if (switchValue == 1)
            {
                output = enter;
                Serial.println("enter"); 
            } else if (yAxis >= 400)
            {
                output = down;
                Serial.println("down");
            } else if (yAxis <= -400)
            {
                output = up;
                Serial.println("up");
            } else if (xAxis <= -400)
            {
                output = right;
                Serial.println("right");
            } else if (xAxis >= 400)
            {
                output = left;
                Serial.println("left");
            }
            return output;
        }

        void moveUp(){
            if (!creationEnCours)
            {
                if (pageActuelle == 4)
                {
                    pageActuelle = 0;
                } else {
                    pageActuelle++;
                }
                menuSelection();    
            }else{
                switch(moteurPreparationActuel){
                    case 0:
                        if(quantiteMoteur1<33){
                            quantiteMoteur1++;
                        }
                        break;
                    case 1:
                        if (quantiteMoteur2<33)
                        {
                            quantiteMoteur2++;
                        }
                        break;
                    case 2:
                        if (quantiteMoteur3<33){
                            quantiteMoteur3++;
                        }
                        break;
                    default:
                        break;
                }
                menuPreparation();
            }
        }

        void moveDown(){
            if(!creationEnCours){
                if (pageActuelle == 0)
                {
                    pageActuelle = 4;
                } else {
                    pageActuelle--;
                }
                menuSelection();
            }else{
                switch(moteurPreparationActuel){
                   case 0:
                        if(quantiteMoteur1>0){
                            quantiteMoteur1--;
                        }
                        break;
                    case 1:
                        if (quantiteMoteur2>0)
                        {
                            quantiteMoteur2--;
                        }
                        break;
                    case 2:
                        if (quantiteMoteur3>0){
                            quantiteMoteur3--;
                        }
                        break;
                    default:
                        break;
                }
                menuPreparation();
            }
        }

        void moveRight() {
            if (moteurPreparationActuel != 2)
            {
                moteurPreparationActuel++;
            }
            menuPreparation();
        }

        void moveLeft() {
            if (moteurPreparationActuel != 0)
            {
                moteurPreparationActuel--;
            }
            menuPreparation();
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
            } else if (pageActuelle == 4) {
                lcd.print("Faire cocktail");
            }    
        }

        void menuPreparation() {
            lcd.clear();
            lcd.setCursor(0,0);

            if (moteurPreparationActuel == 0)
            {
                lcd.print("    Moteur 1   >");
                lcd.setCursor(0,1);
                lcd.print("Quantite : ");
                lcd.print(quantiteMoteur1);
                lcd.print("cl");

            } else if (moteurPreparationActuel == 1){
                lcd.print("<   Moteur 2   >");
                lcd.setCursor(0,1);
                lcd.print("Quantite : ");
                lcd.print(quantiteMoteur2);
                lcd.print("cl");
            } else if (moteurPreparationActuel == 2){
                lcd.print("<   Moteur 3   ");
                lcd.setCursor(0,1);
                lcd.print("Quantite : ");
                lcd.print(quantiteMoteur3);
                lcd.print("cl");
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

            else if (pageActuelle == 4) {
                premiereSelection = true;
                lcd.print("Lancer la");
                lcd.setCursor(0,1);
                lcd.print("preparation?");
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

            else if (pageActuelle == 4){
                premiereSelection = false;
                creationEnCours = true;
                lcd.print("Debut de la");
                lcd.setCursor(0,1);
                lcd.print("creation !");
                delay(2000);
                menuPreparation();
            }
        }

        void lancementCreation() {
            lcd.clear();
            lcd.setCursor(0,0);
            if ((quantiteMoteur1 + quantiteMoteur2 + quantiteMoteur3) > 33)
            {
                lcd.print("Diminuer la");
                lcd.setCursor(0,1);
                lcd.print("taille a 33cl.");
                delay(3000);
                menuPreparation();
            }else{
                lcd.print("Creation de");
                lcd.setCursor(0,1);
                lcd.print("votre cocktail!");

                int tempsMoteur1, tempsMoteur2, tempsMoteur3;
                tempsMoteur1 = clToSeconds(1,quantiteMoteur1);
                tempsMoteur2 = clToSeconds(2,quantiteMoteur2);
                tempsMoteur3 = clToSeconds(3,quantiteMoteur3);

                Serial.println("cl to s");
                Serial.println(tempsMoteur1);
                Serial.println(tempsMoteur2);
                Serial.println(tempsMoteur3);

                int** tempsTries;
                triTemps(tempsMoteur1,tempsMoteur2,tempsMoteur3,
                        mn_moteur1, mn_moteur2, mn_moteur3, tempsTries);

                Serial.println("tempsTries : ");
                Serial.println(tempsTries[0][0]);
                Serial.println(tempsTries[1][0]);
                Serial.println(tempsTries[2][0]);

                digitalWrite(mn_moteur1, LOW);
                digitalWrite(mn_moteur2, LOW);
                digitalWrite(mn_moteur3, LOW);

                delay((tempsTries[0][0] * 1000));
                digitalWrite(tempsTries[0][1], HIGH);

                delay((tempsTries[1][0] - tempsTries[0][0]) * 1000);
                digitalWrite(tempsTries[1][1], HIGH);

                delay((tempsTries[2][0] - tempsTries[1][0]) * 1000);
                digitalWrite(tempsTries[2][1], HIGH);

                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("Fin de la");
                lcd.setCursor(0,1);
                lcd.print("Preparation !");

                preparationEnCours = false;
            }
            
        }

        void FonctionCocktailAlcool() {
            digitalWrite(mn_moteur1, LOW);
            digitalWrite(mn_moteur2, LOW);
            delay(4500);
            digitalWrite(mn_moteur1, HIGH);
            delay(25500);
            digitalWrite(mn_moteur2, HIGH);

            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Fin de la");
            lcd.setCursor(0,1);
            lcd.print("Preparation !");

            preparationEnCours = false;
        }

        void FonctionCocktailSansAlcool() {
            digitalWrite(mn_moteur1, LOW);
            digitalWrite(mn_moteur2, LOW);
            digitalWrite(mn_moteur3, LOW);
            delay(4500);
            digitalWrite(mn_moteur3, HIGH);
            delay(2500);
            digitalWrite(mn_moteur1, HIGH);
            delay(12500);
            digitalWrite(mn_moteur2, HIGH);
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Fin de la");
            lcd.setCursor(0,1);
            lcd.print("Preparation !");

            preparationEnCours = false;
        }

        void FonctionPurger() {
            digitalWrite(mn_moteur1, LOW);
            delay(30000);
            digitalWrite(mn_moteur1, HIGH);

            digitalWrite(mn_moteur2, LOW);
            delay(30000);
            digitalWrite(mn_moteur2, HIGH);

            digitalWrite(mn_moteur3, LOW);
            delay(30000);
            digitalWrite(mn_moteur3, HIGH);

            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Fin de la");
            lcd.setCursor(0,1);
            lcd.print("purge !");

            preparationEnCours = false;
        }

        int clToSeconds(int moteur, int cl){
            switch (moteur)
            {
            case 1:
                return round((10*cl) / mn_vitesseMoteur1);
                break;
            case 2:
                return round((10*cl) / mn_vitesseMoteur2);
                break;
            case 3:
                return round((10*cl) / mn_vitesseMoteur3);
                break;
            default:
                break;
            }
        }

        void triTemps(int tempsMoteur1, int tempsMoteur2, int tempsMoteur3,
                        int moteur1, int moteur2, int moteur3, int** tab)
        {
            int tempsTries[3][2];
            tempsTries[0][0] = tempsMoteur1;
            tempsTries[0][1] = moteur1;

            tempsTries[1][0] = tempsMoteur2;
            tempsTries[1][1] = moteur2;

            tempsTries[2][0] = tempsMoteur3;
            tempsTries[2][1] = moteur3;

            int n = sizeof(tempsTries) / sizeof(tempsTries[0]);

            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (tempsTries[i][0] < tempsTries[j][0])  
                    {
                        int temp[2] = {tempsTries[i][0], tempsTries[i][1]};
                        tempsTries[i][0] = tempsTries[j][0];
                        tempsTries[i][1] = tempsTries[j][1];

                        tempsTries[j][0] = temp[0];
                        tempsTries[j][1] = temp[1];

                        delete(temp);
                    }
                }
            }
                        
            for (int i = 0; i < n; i++)
            {
                tab[i][0] = tempsTries[i][0];
                tab[i][1] = tempsTries[i][1];
            }
            
        }
};