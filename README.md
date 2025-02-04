# Simulation de Machine de Turing

## Description

Ce projet est une simulation d'une machine de Turing, permettant de tester et de visualiser le fonctionnement d'une machine de Turing à partir d'un fichier de configuration ou en mode interactif. Le programme lit un fichier de configuration décrivant la machine de Turing, exécute les transitions définies et affiche les résultats.

## Installation

1. **Cloner le dépôt**

   Clonez ce dépôt sur votre machine locale en utilisant la commande suivante :

   git clone https://github.com/Yolke/Simulation-Turing-Machine.git

2. **Accéder au répertoire du projet**

   Changez de répertoire pour entrer dans le dossier du projet :
```sh
   cd Simulation-Turing-Machine
```
3. **Compiler le projet**

   Utilisez `make` pour compiler le projet. Cela générera un exécutable nommé `turing` :
```sh
   make
```
## Utilisation du Programme

### Exécution avec un fichier de configuration

Pour lancer la simulation avec un fichier de configuration, utilisez la commande suivante :
```sh
   ./turing 1 <fichier_de_configuration>
```
```sh
- `1` : Mode de simulation avec un fichier de configuration.
- `<fichier_de_configuration>` : Le fichier décrivant la machine de Turing.
```
Exemple :

   ./turing 1 TuringMachine1.txt

### Exécution en Mode Interactif

Pour entrer des données directement dans le terminal, utilisez la commande suivante :
```sh
   ./turing 2
```
Après avoir exécuté cette commande, un prompt vous demandera d'entrer une chaîne d'entrée directement dans le terminal.

## Format du Fichier de Configuration

Le fichier de configuration doit respecter le format suivant :

   init:ÉtatInitial
   accepte:ÉtatFinal
   EtatInitial,LettreLue,EtatFinal,NouvelleLettre,Déplacement/

Exemple (`TuringMachine1.txt`) :
```sh
   init:A
   accepte:S
   B,1,A,1,r
   A,0,A,0,r
   A,1,B,1,r
   A,_,S,_,s
```

