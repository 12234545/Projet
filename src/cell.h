#pragma once
//class pour les cellules du labyrinthe
class Cell {
public:
    //declaration des attributes
    bool visited;//si la cellule est visité
    bool topwall, bottomwall, leftwall, rightwall;//les murs de la cellule
   //declarection des methodes
    //constructeur
    Cell() : visited(false), topwall(true), bottomwall(true), leftwall(true), rightwall(true) {}

     
    bool hasTopWall() const { return topwall; }//verifier si la cellule a un mur en haut
    bool hasBottomWall() const { return bottomwall; }//verifier si la cellule a un mur en bas
    bool hasLeftWall() const { return leftwall; }//verifier si la cellule a un mur a gauche
    bool hasRightWall() const { return rightwall; }//verifier si la cellule a un mur a droite
};