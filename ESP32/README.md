# Sommaire <!-- omit in toc -->

- [1. Travail sur les modules ESP32](#1-travail-sur-les-modules-esp32)
- [2. Suivis de développement](#2-suivis-de-développement)
  - [2.1. Stream de la caméra](#21-stream-de-la-caméra)
    - [2.1.1. Stream simple](#211-stream-simple)
    - [2.1.2 Toggle du stream](#212-toggle-du-stream)

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
lien](https://all3dp.com/2/esp32-cam-arduino-tutorial/#:~:text=Restart%20Arduino%20IDE%20and%20connect,AI%20Thinker%20ESP32%2DCAM%E2%80%9D.)
montrant les différentes façon de connecter une caméra ESP32 à votre ordinateur.

# 2. Suivis de développement

  
## 2.1. Stream de la caméra
### 2.1.1. Stream simple

**Code disponible
[ici](https://github.com/MoOaAaa/StageFabLab/tree/main/ESP32/ESP32-WebApp-Simple-Stream-Server).** <br/>
Il s'agît d'un serveur simple en avec une caméra ESP qui n'affiche que le flux d'image de la caméra.
Il est basé sur [ce code](https://registry.platformio.org/libraries/espressif/esp32-camera) (Dans la
partie Readme, scroll jusqu'à l'exemple `JPEG HTTP Stream`).

### 2.1.2 Toggle du stream

**Code disponible ici
