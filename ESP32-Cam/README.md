# Sommaire <!-- omit in toc -->

- [1. Travail sur les modules ESP32](#1-travail-sur-les-modules-esp32)
- [2. Suivis de développement](#2-suivis-de-développement)
  - [2.1. Stream de la caméra](#21-stream-de-la-caméra)
    - [2.1.1. Stream simple](#211-stream-simple)
    - [2.1.2. Toggle du stream](#212-toggle-du-stream)
  - [2.2. Motion Capture](#22-motion-capture)
    - [2.2.1.  Camera Test](#221--camera-test)
    - [2.2.2. Simple Motion Detection](#222-simple-motion-detection)
    - [2.2.3. Motion Detection Stream](#223-motion-detection-stream)
- [3. Mise en place sur les imprimantes 3D](#3-mise-en-place-sur-les-imprimantes-3d)
  - [3.1. Imprimantes du FabLab](#31-imprimantes-du-fablab)
  - [3.2. Support de caméra](#32-support-de-caméra)

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
lien](https://all3dp.com/2/esp32-cam-arduino-tutorial/#:~:text=Restart%20Arduino%20IDE%20and%20connect,AI%20Thinker%20ESP32%2DCAM%E2%80%9D)
montrant les différentes façon de connecter une caméra ESP32 à votre ordinateur. <br/>

> Lors de l'upload du code, ne pas oublier d'appuyer sur le bouton `reset`, puis de retirer la
> connexion entre `GPIO0` et `GND`.

Autre point important dans mon cas, le wifi du cégep étant un wifi de type `WPA2 - Entreprise`, la
connection se fait avec les identifiants personnels des étudiants/employés (pour moi, numéro
étudiant et mot de passe). Pour me faciliter la chose pour le moment, j'ai créé un point d'accès
mobile sur mon pc et ai utilisé cette connection pour la caméra. Cependant, après quelques
recherches j'ai découvert qu'il était possible de connecter les caméras à un wifi `WPA2` (exemple
[ici](https://github.com/martinius96/ESP32-eduroam/blob/master/2021/experimental_example/experimental_example.ino)
avec un wifi eduroam).

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
reprise du [2.1.1](#211-stream-simple)** <br/>
Il s'agît d'un site simple, avec un bouton pour montrer le stream ou non avec un bouton.
Pour le moment, le stream ne peut s'afficher uniquement si il n'y a qu'une seule instance du stream
(celle du site uniquement)

## 2.2. Motion Capture

**Les codes du [3.1.1](#311-camera-test) et du [3.1.2](#312-simple-motion-detection) sont pris des exemples de la librairie
[EloquentArduino](https://github.com/eloquentarduino/EloquentArduino).**
### 2.2.1.  Camera Test

**Code disponible
[ici](https://github.com/MoOaAaa/StageFabLab/tree/main/ESP32/ESP32-Camera-Test). Pris de
l'exemple ici : [Test your
camera](https://eloquentarduino.com/projects/esp32-arduino-motion-detection#test-your-camera)**<br/>
Cette partie est là juste pour tester si la librairie fonctionnait correctement. J'ai eu quelques
problèmes en utilisant PlatformIO sur VSCode, cependant si vous utilisez ArduinoIDE tout devrait
bien aller. Au cas ou vous utilisez PlatformIO ou autre, voici les changements que j'ai apporté au
code de l'exemple de EloquentArduino :
> * Ajout de `#include "Arduino.h"` dans le fichier `main.cpp`.
> * Changement de la déclaration des membres en `protected` des lignes 239-244 aux lignes 22-27 du
> fichier [BaseImage.h](https://github.com/eloquentarduino/EloquentArduino/blob/master/src/eloquent/vision/image/BaseImage.h).

### 2.2.2. Simple Motion Detection
**Code disponible
[ici](https://github.com/MoOaAaa/StageFabLab/tree/main/ESP32/ESP32-Simple-Motion-Detection). Pris de
l'exemple ici : [Realtime Motion Detection without
PIR](https://eloquentarduino.com/projects/esp32-arduino-motion-detection#realtime-motion-detection-without-pir)**<br/>
Ici, l'exemple à la caméra de détecter mouvement, grâce au changement de pixels dans l'image. La
caméra envoie ensuite un message au moniteur de série pour dire qu'il y a eu un changement de pixels
dans le flux d'images, donc un mouvement. Cela implique que la caméra soit statique lors de son
fonctionnement.

### 2.2.3. Motion Detection Stream
**Code disponible
[ici](https://github.com/MoOaAaa/StageFabLab/tree/main/ESP32/ESP32-Motion-Detection-Stream). Basé
sur cet exemple
[ci](https://eloquentarduino.github.io/2020/06/easy-esp32-camera-http-video-streaming-server/) mais
largement changé (partie serveur web reprise du [2.1.1](#211-stream-simple), plus refactoring de la
librairie pour enlever les erreurs)**<br />
Dans ce test, j'ai voulu voir si on pouvait lancer un stream à partir du moment où la caméra
détectait un mouvement. Avec la librairie c'était très simple à réaliser (en plus de suivre les
tutos), mais différentes versions de la librairie donc du code m'ont fait perdre beaucoup de temps.
Cependant, après quelques efforts j'ai pu effectivement lancer un stream lorsque la caméra détecte
du mouvement. Il ne me reste plus qu'à essayer de fixer la caméra sur une des imprimantes 3D et de
voir si elle détecte quand l'impression se lance!

# 3. Mise en place sur les imprimantes 3D

## 3.1. Imprimantes du FabLab
Le fablab dispose de plusieurs imprimantes 3D, toutes du model [Prusa
Mk3S](https://www.prusa3d.com/category/original-prusa-i3-mk3s/). Le but avec ces imprimantes serait
idéalement de faire pour que tout le monde puisse accéder au stream lorsque qu'un site internet du
FabLab sera en place. Mais ce sera dans le futur, car je n'ai toujours pas trouvé de solution au
problème du client unique sur le stream de la caméra. Donc pour l'instant nous allons nous contenter
d'attacher la caméra sur l'imprimante avec un support mobile.

## 3.2. Support de caméra
 J'ai trouvé [cette boîte](https://www.thingiverse.com/thing:3463679) sur
 [Thingiverse](https://www.thingiverse.com/), qui me permettrait de mettre la caméra à
 l'intérieur. Il me suffit maintenant juste de tester les caméras pour savoir quelle adresse IP
 correspond à quelle caméra et de modifier la boîte pour pouvoir l'accrocher à l'imprimante.
