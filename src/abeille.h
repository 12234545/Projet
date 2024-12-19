#pragma once
#include "config.h"
#include "position.h"
#include "labyranthe.h"
class Player
{

private:
//declaration des attributs
    Position position;//position de l'abille
    Position goal;//position de l'objectif
    Maze& maze; //labyrinthe
    Texture2D texture;//texture de l'abeille
    float scale;//echelle de l'abeille

 

public:

    bool hasWon;//si l'abeille a gagné
   
     // Constructeur
      Player(int x, int y, Maze& m, const char* imagePath);
        
    //constructeur par defaut
    Player();
   
    //la methode pour le mouvement de l'abeille
    void moveplayer(int dx, int dy);

    //methode pour afficher l'abeille
     void draw();

    //methode pour afficher l'objectif sur l'ecran
    void drawGoal();

    //methode pour remettre l'abeille au debut
    void possistionabb();

    //methode pour obtenir la position(acceseur)
    Position getPosition() { return position; }

    //methode pour obtenir le rectangle de collision
    Rectangle getCollisionRectangle() const ;

    //methode pour obtenir la texture (getter)
    Texture2D getTexture() {
      return texture;
    }

    //methode pour obtenir le scale (getter)
    float getScale() {
      return scale;
    }
     //methode pour detruire l'abeille (destructeur)
     ~Player() {
        UnloadTexture(texture);
    }
   
};