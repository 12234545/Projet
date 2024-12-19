#pragma once
#include "raylib.h"


class TableauScores {
public:
    // Affiche le meilleur score et le dernier score dans un cadre arrondi
    void afficher(float meilleurScore, float scoreFinal, int x, int y, Texture2D img , float scale);
        
};
