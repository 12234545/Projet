
#pragma once
#include <raylib.h>
#include <vector>
#include <algorithm>
#include "position.h"
#include "config.h"
#include "labyranthe.h"

class Obstacle {
private:
    //declaration des attributs
    std::vector<Position> path; // chemin complet de l'obstacle
    size_t currentPathIndex = 0;// index actuel du chemin
    Texture2D texture;// texture de l'obstacle
    float speed;// vitesse de l'obstacle
    float scale;// échelle de l'obstacle
    bool movingForward = true;// direction de l'obstacle

    // Méthode privée pour générer un chemin aléatoire
    std::vector<Position> generateRandomPath(Maze& maze, int startX, int startY, int pathLength);

public:

    // Constructeur modifié pour accepter le nombre d'obstacles
    Obstacle(const char *texturePath, int x, int y, float spd, float scl, Maze& maze, int pathLength = 10) ;
        
    // Méthode de déplacement mise à jour
    void move(Maze& maze) ;

   // Méthode de dessin
    void draw() const ;

   // Méthode pour obtenir le rectangle de collision
    Rectangle getCollisionRectangle() const ;

    // Méthode pour réinitialiser l'obstacle
    void resetPosition(Maze& maze);
    
    //destructeur
    ~Obstacle() {
        UnloadTexture(texture);
    }
};



