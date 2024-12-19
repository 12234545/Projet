#include "niveau.h"

// Générer des obstacles pour le niveau actuel
void Niveau::genererObstacles(int nombreObstacles)
{
    obstacles.clear();

        for (int i = 0; i < nombreObstacles; i++) {
            // Génération de positions aléatoires dans le labyrinthe
            int x = GetRandomValue(0, MazeConfig::grid_width - 1);
            int y = GetRandomValue(0, MazeConfig::grid_height - 1);
            
            // Créer un obstacle avec une position aléatoire
            // Le dernier paramètre définit la longueur du chemin de l'obstacle
            Obstacle nouvelObstacle("Graphique/obstacle.png", x, y, 0.05f, 0.15f, maze, 10 + i * 2);
            obstacles.push_back(nouvelObstacle);
        }
}
// Niveau Facile : 1 obstacle
void Niveau::easyNiveau()
{
     if (currentDifficultyLevel != 1) {
            currentDifficultyLevel = 1;
            maze.miseajour();
            genererObstacles(1); // 1 obstacle
        }
        
        // Dessiner le labyrinthe complet
        maze.drawCompleteMaze();
    
}
// Niveau Moyen : 2 obstacles
void Niveau::mediumNiveau()
{
    if (currentDifficultyLevel != 2) {
            currentDifficultyLevel = 2;
            maze.miseajour();
            maze.addCycles(10);
            genererObstacles(2); // 2obstacles
        }
        
        // Dessiner le labyrinthe et déplacer les obstacles
        maze.drawCompleteMaze();
}
// Niveau Difficile : 4 obstacles
void Niveau::difficultNiveau(const Position &position)
{
    if (currentDifficultyLevel != 3) {
            currentDifficultyLevel = 3;
            maze.miseajour();
            maze.addDeceptivePaths(10, 5);
            genererObstacles(4); // 4 obstacles
        }
        
        // Afficher une portion du labyrinthe autour du joueur
        maze.drawNearMaze(position);
}
// Mettre à jour le niveau
void Niveau::miseAJourNiveau()
{
    maze.miseajour();
    currentDifficultyLevel = 0; // Réinitialiser le niveau de difficulté
}