#include"chnometre.h"
#include "raylib.h"
#include <iostream>
#include <algorithm>  
#include <cmath> 
#include <cfloat> 

const Color texteTitre = BLACK;                // Couleur du texte des titres (noir)
const Color texteTempsActif = DARKGRAY;        // Couleur du texte pour le temps actif (gris foncé)
const Color texteTempsAlert = DARKGRAY;  

Texture2D textureheur;

    // Constructeur par défaut, initialise les variables

Chronometre::Chronometre() : temps_depart(0), temps_actuel(0), actif(false){}

    // Démarre le chronomètre en enregistrant l'heure actuelle

void Chronometre :: demarrer() {
        temps_depart = GetTime();  // Récupère l'heure actuelle depuis le démarrage du programme
        actif = true;               // Définit le chronomètre comme actif
    }

    // Arrête le chronomètre
 void Chronometre :: arreter() {
        actif = false;
        temps_arret = temps_actuel;
    }

    void Chronometre::continuer()
    {
        actif=true;
        temps_depart=GetTime()-temps_arret;
    }

    // Met à jour le temps actuel si le chronomètre est actif
 void Chronometre ::mettre_a_jour() {
        if (actif) {
            temps_actuel = GetTime() - temps_depart;  // Calcule le temps écoulé depuis le départ
        }
    }

    // Réinitialise le chronomètre (remet à zéro)
 void Chronometre :: reinitialiser() {
        temps_depart = 0;
        temps_actuel = 0;
        actif = false;
    }

    // Affiche le chronomètre à l'écran
 void Chronometre :: afficher() {
        int minutes = static_cast<int>(temps_actuel) / 60;  // Calcul du nombre de minutes
        int secondes = static_cast<int>(temps_actuel) % 60; // Calcul du nombre de secondes
        Color texteTemps = (temps_actuel > 10.0f) ? texteTempsAlert : texteTempsActif;  // Change la couleur du texte si le temps dépasse 10 secondes
        
        
        // Affiche le temps sous le format MM:SS
        DrawText(TextFormat("%02d:%02d", minutes, secondes), 730, 50, 40, texteTemps);

        // Affiche l'abeille dans le chronomètre
        float imagePosX = 830;
        float imagePosY = 40;
        float scaleAbeille = 60.0f /  textureheur.width;  // Calcul du facteur d'échelle pour l'image
        DrawTextureEx( textureheur, {imagePosX, imagePosY}, 0.0f, scaleAbeille, WHITE);
    }

    
    // changer la texture de chrono
    void Chronometre::setTexture(Texture2D texture)
    {
        textureheur=texture;
    }
