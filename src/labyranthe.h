
#pragma once 
#include <raylib.h>
#include "cell.h"
#include "position.h"
#include "config.h"

class Maze {
public:
    
    //declaration des attributs
    Cell maze[MazeConfig::grid_width][MazeConfig::grid_height];//labyrinthe
    Texture2D wallTexture;//texture des murs
    Texture2D BackgroundTexture;//texture de fond


    //constructeur
    Maze() { initializeMaze(); 
    wallTexture = LoadTexture("Graphique/mur7.png"); 
    BackgroundTexture = LoadTexture("Graphique/gaz.png");
    }
    //----------les methodes------------------

    //initialiser le labyrinthe
    void initializeMaze();
   
   //generer le labyrinthe
    void generatemaze(int x, int y);

   //ajouter des cycles
   void addCycles(int count);

  //dessiner le labyrinthe complet
  void drawCompleteMaze() ;
   
  //dessiner une portion du labyrinthe autour du joueur
   void drawNearMaze(const Position& position);

  //mise a jour du labyrinthe
  void miseajour() ;

  //ajouter des chemins trompeurs
    void addDeceptivePaths(int count, int maxLength);

   //destructeur
    ~Maze();
};



