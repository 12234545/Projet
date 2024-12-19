#pragma once
#include "raylib.h"



class Chronometre {
public:
    float temps_depart;  // Temps au moment du démarrage du chronomètre
    float temps_actuel;
    float temps_arret;
      // Temps écoulé depuis le démarrage
    bool actif;  
          // État du chronomètre (actif ou non)

    // Constructeur par défaut, initialise les variables
    Chronometre ();
    

    // Démarre le chronomètre en enregistrant l'heure actuelle
    void demarrer();
       

    // Arrête le chronomètre
    void arreter();
    //continuer le chronometre
    void continuer();


    // Met à jour le temps actuel si le chronomètre est actif
    void mettre_a_jour();
        
    // Réinitialise le chronomètre (remet à zéro)
    void reinitialiser();
    //changer la texture du chronometre
    void setTexture(Texture2D texture);

    // Affiche le chronomètre à l'écran
    void afficher();
        
};