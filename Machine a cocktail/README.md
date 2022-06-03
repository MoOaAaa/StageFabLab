# Sommaire <!-- omit in toc -->

- [1. Matériaux](#1-matériaux)
- [2. Utilisation](#2-utilisation)
  - [2.1. Fonctionnalités](#21-fonctionnalités)
  - [2.2. Programme](#22-programme)


# 1. Matériaux
Voici la liste des matériaux que nous avons utilisé pour créer notre machine à cocktail :
- Un Arduino Uno
- Une plaque d’extension  Arduino
- Un écran LCD 16x2
- Un joystick
- Une plaque de 4 relais 5V
- Un générateur 24V DC
- Trois moteurs 24V
- Trois systèmes de pompes
- Un support pour les moteurs
- Une prise de secteur 120V
- Des tubes en plastique
- Un tuyau en PVC
- Un embout pour diminuer la taille de la sortie du tuyau
- Trois planches de bois 60x40cm
- Des vis en fonction


# 2. Utilisation
## 2.1. Fonctionnalités
La machine dispose d'un menu vous permettant de choisir entre 4 options :
- Cocktail avec alcool (un des moteur tournera bien moins longtemps que les autres)
- Cocktail sans alcool (à peu près le même temps pour tous les moteurs)
- Purge de la machine (fait tourner les 3 moteurs 30 secondes un par un)
- Création cocktail (permet de créer votre propre cocktail)

Ces fonctions sont accessibles à partir du menu affiché sur l'écran LCD et contrôlable verticalement
avec le joystick. <br/>
Le menu de création de cocktail permet un déplacement horizontal pour sélectionner
le moteur et un déplacement vertical pour la quantité. <br/>
Une pression sur le joystick permet de confirmer son choix.

## 2.2. Programme
La partie technique du programme se trouve dans le header
[GestionMenu.h](https://github.com/MoOaAaa/StageFabLab/blob/main/Machine%20a%20cocktail/Creation%20Cocktail/lib/Cocktails/GestionMenu.h),
et est utilisé pour gérer l'entièreté de la machine. Les fonctions citées dans
[2.1.](#21-fonctionnalités) se trouvent dans l'ordre aux lignes :
- [382](https://github.com/MoOaAaa/StageFabLab/blob/main/Machine%20a%20cocktail/Creation%20Cocktail/lib/Cocktails/GestionMenu.h#L382)
- [400](https://github.com/MoOaAaa/StageFabLab/blob/main/Machine%20a%20cocktail/Creation%20Cocktail/lib/Cocktails/GestionMenu.h#L400)
- [420](https://github.com/MoOaAaa/StageFabLab/blob/main/Machine%20a%20cocktail/Creation%20Cocktail/lib/Cocktails/GestionMenu.h#L420)
- [316](https://github.com/MoOaAaa/StageFabLab/blob/main/Machine%20a%20cocktail/Creation%20Cocktail/lib/Cocktails/GestionMenu.h#L316)

