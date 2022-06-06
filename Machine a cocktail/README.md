# Sommaire <!-- omit in toc -->

- [1. Matériaux](#1-matériaux)
- [2. Utilisation](#2-utilisation)
  - [2.1. Fonctionnalités](#21-fonctionnalités)
  - [2.2. Programme](#22-programme)
- [3. Montage électrique](#3-montage-électrique)
  - [Fonctionnement d'un relais](#fonctionnement-dun-relais)
  - [Montage électrique](#montage-électrique)


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
- [382 - FonctionCocktailAlcool()](https://github.com/MoOaAaa/StageFabLab/blob/main/Machine%20a%20cocktail/Creation%20Cocktail/lib/Cocktails/GestionMenu.h#L382)
- [400 - FonctionCocktailSansAlcool()](https://github.com/MoOaAaa/StageFabLab/blob/main/Machine%20a%20cocktail/Creation%20Cocktail/lib/Cocktails/GestionMenu.h#L400)
- [420 - FonctionPurger()](https://github.com/MoOaAaa/StageFabLab/blob/main/Machine%20a%20cocktail/Creation%20Cocktail/lib/Cocktails/GestionMenu.h#L420)
- [316 - lancementCreation()](https://github.com/MoOaAaa/StageFabLab/blob/main/Machine%20a%20cocktail/Creation%20Cocktail/lib/Cocktails/GestionMenu.h#L316)


# 3. Montage électrique
## Fonctionnement d'un relais
Un relais permet de contrôler des appareils demandant un fort courant électrique via un plus faible
courant électrique. Les relais sont comme des interrupteurs mais activés par de l'électricité.

<img 
  src="./images/FonctionnementRelais.gif" 
  alt="Fonctionnement Relais" 
  width="50%" 
  height="50%"
  />

Dans notre cas, les relais nous permettent de contrôler des moteurs 24V DC grâce à un arduino qui ne
délivre que du 5V DC.

Les relais existent sous plusieurs formes, mais les relais que nous utilisons sont des relais à 5
pins comme celui-ci :

<img
  src="./images/RelayPinout.jpg"
  alt="12V/5pin RElay pinout" 
/>

## Montage électrique