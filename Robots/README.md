# Sommaire <!-- omit in toc -->

- [1. ALLBOT by WHADDA](#1-allbot-by-whadda)
  - [1.1. Montage du ALLBOT](#11-montage-du-allbot)
  - [1.2. Programmation des fonctionnalités](#12-programmation-des-fonctionnalités)

# 1. ALLBOT by WHADDA
## 1.1. Montage du ALLBOT
Le montage du ALLBOT se fait facilement en suivant [le
guide](https://manuals.whadda.com/article.php?id=383). Cependant un point **très important** du
montage est la mise en place des jambes est l'alignement des servos moteurs. Voici le tutoriel pour
centrer un servo donné par WHADDA (lien [ici](https://manuals.whadda.com/article.php?id=390)). Je
vous conseille de faire la partie 19 avec les servos moteurs branchés à l'arduino et en marche, pour
qu'ils soient bien à 90 degrés.
## 1.2. Programmation des fonctionnalités
La programmation du robots se fait facilement grâce à la
[bibliothèque](https://github.com/Velleman/ALLBOT-lib) que Velleman nous fournit. En se servant des
servomoteurs du robot, il est possible de créer des mouvements complexes avec le robot. Un exemple
est déjà proposé sur le github et il recrée plusieurs actions pour rendre le robot plus vivant (voir
[ici](https://github.com/Velleman/ALLBOT-lib/blob/master/examples/VR408/VR408.ino)).