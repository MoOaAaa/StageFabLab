# Sommaire <!-- omit in toc -->

- [1. Travail sur les modules ESP32](#1-travail-sur-les-modules-esp32)
- [2. Suivis de développement](#2-suivis-de-développement)
  - [2.1. Stream de la caméra](#21-stream-de-la-caméra)
    - [2.1.1. Stream simple](#211-stream-simple)
    - [2.1.2. Toggle du stream](#212-toggle-du-stream)
- [3. Motion Capture](#3-motion-capture)
  - [3.1. Motion Detection](#31-motion-detection)
    - [3.1.1.  Camera Test](#311--camera-test)
    - [3.1.2. Simple Motion Detection](#312-simple-motion-detection)

# 1. Travail sur les modules ESP32

Un des projets aue mon tuteur voulait voir se réaliser était le stream des impressions 3D en ligne.
Pour ce faire il avait acheté des caméras ESP32, ainsi que du matériel électronique pouvant aller
avec. Mais étant grand novice en Arduino, j'ai du faire quelques recherches et entraînements sur les
ESP32. 

Pour ces travaux, voici le layouts du module ESP32 et de la caméra ESP32 que j'ai utilisé : 
* ESP32
    <img
        src="https://www.etechnophiles.com/wp-content/uploads/2021/03/esp32-Board-with-30-pins-Pinout.png?ezimgfmt=ng:webp/ngcb40"
        alt="ESP32 board"
    />
    
<br/>

* ESP32 Camera
    <img
        src="https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2020/03/ESP32-CAM-pinout-new.png?quality=100&strip=all&ssl=1"
        alt="ESP32 CAM"
    />
<br/>
La caméra est reliée à un programmeur UBS ESP32-CAM-MB reliée en micro USB pour l'upload, mais dans
le cas ou l'on ne dispose pas d'un programmeur MB, voici [un
lien](https://all3dp.com/2/esp32-cam-arduino-tutorial/#:~:text=Restart%20Arduino%20IDE%20and%20connect,AI%20Thinker%20ESP32%2DCAM%E2%80%9D).
montrant les différentes façon de connecter une caméra ESP32 à votre ordinateur.
> Lors de l'upload du code, ne pas oublier d'appuyer sur le bouton `reset`, puis de retirer la
> connexion entre `GPIO0` et `GND`.

# 2. Suivis de développement

  
## 2.1. Stream de la caméra
### 2.1.1. Stream simple

**Code disponible
[ici](https://github.com/MoOaAaa/StageFabLab/tree/main/ESP32/ESP32-WebApp-Simple-Stream-Server).** <br/>
Il s'agît d'un serveur simple en avec une caméra ESP qui n'affiche que le flux d'image de la caméra.
Il est basé sur [ce code](https://registry.platformio.org/libraries/espressif/esp32-camera) (Dans la
partie Readme, scroll jusqu'à l'exemple `JPEG HTTP Stream`).

### 2.1.2. Toggle du stream

**Code disponible
[ici](https://github.com/MoOaAaa/StageFabLab/tree/main/ESP32/ESP32-WebApp-Stream-Toggle). Base
reprise du [2.1.1](#211)** <br/>
Il s'agît d'un site simple, avec un bouton pour montrer le stream ou non avec un bouton.
Pour le moment, le stream ne peut s'afficher uniquement si il n'y a qu'une seule instance du stream
(celle du site uniquement)

# 3. Motion Capture

## 3.1. Motion Detection 
**Les codes du [3.1.1](#311) et du [3.1.2](#312) sont pris des exemples de la librairie
[EloquentArduino](https://github.com/eloquentarduino/EloquentArduino).**
### 3.1.1.  Camera Test

**Code disponible
[ici](https://github.com/MoOaAaa/StageFabLab/tree/main/ESP32/ESP32-Simple-Motion-Detection). Pris de
l'exemple ici : [Test your
camera](https://eloquentarduino.com/projects/esp32-arduino-motion-detection#test-your-camera)**<br/>
Cette partie est là juste pour tester si la librairie fonctionnait correctement. J'ai eu quelques
problèmes en utilisant PlatformIO sur VSCode, cependant si vous utilisez ArduinoIDE tout devrait
bien aller. Au cas ou vous utilisez PlatformIO ou autre, voici les changements que j'ai apporté au
code de l'exemple de EloquentArduino :
> * Ajout de `#include "Arduino.h";` dans le fichier `main.cpp`.
> * Changement de la déclaration des membres en `protected` des lignes 239-244 aux lignes 22-27 du
> fichier [BaseImage.h](https://github.com/eloquentarduino/EloquentArduino/blob/master/src/eloquent/vision/image/BaseImage.h).

### 3.1.2. Simple Motion Detection