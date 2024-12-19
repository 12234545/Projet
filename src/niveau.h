
#include "obstacle.h"
class Niveau {
private:

    // attributs privés
    Maze& maze;
    std::vector<Obstacle> obstacles;
    int currentDifficultyLevel;

    // méthode privée pour générer des obstacles
    void genererObstacles(int nombreObstacles);

public:
    // Constructeur
    Niveau(Maze& m) : maze(m), currentDifficultyLevel(0) { 
        maze.generatemaze(0, 0); 
    }

    // Niveau Facile : 1 obstacle
    void easyNiveau();

    // Niveau Moyen : 3 obstacles
    void mediumNiveau();

    // Niveau Difficile : 5 obstacles
    void difficultNiveau(const Position& position);

    // Méthode pour mettre à jour le niveau
    void miseAJourNiveau() ;

    // Méthode pour obtenir les obstacles du niveau actuel
    std::vector<Obstacle>& getObstacles() {
        return obstacles;
    }
};



