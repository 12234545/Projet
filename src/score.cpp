#include "score.h"
#include "chnometre.h"
#include "raylib.h"
#include <iostream>
#include <algorithm> 
#include <cmath> 
#include <cfloat> 

void TableauScores :: afficher(float meilleurScore, float scoreFinal, int x, int y, Texture2D img , float scale) {
       // affiche une image associée au tableau des scores
        DrawTexture(img, 200, 80, WHITE);
          // conversion du meilleur score en secondes (en le modifiant pour l'échelle souhaitée)
        int secondesMeilleur = (static_cast<int>(meilleurScore) % 60)*20 ;
         // affichage du meilleur score à la position spécifiée (x, y) avec un décalage
        DrawText( TextFormat("%2d", secondesMeilleur), x + 170, y + 12, 30, BROWN);
         // conversion du score final en secondes (en le modifiant pour l'échelle souhaitée)
        int secondesDernier = (static_cast<int>(scoreFinal) % 60)*20;
        // affichage du score final à une position différente (décalée verticalement)
        DrawText(TextFormat("%2d", secondesDernier), x + 170, y + 160, 30, BROWN);

          
    }
