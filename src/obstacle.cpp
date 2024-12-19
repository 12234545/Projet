#include "obstacle.h"

// Méthode privée pour générer un chemin aléatoire
std::vector<Position> Obstacle::generateRandomPath(Maze &maze, int startX, int startY, int pathLength)
{   
    std::vector<Position> newPath;// nouveau chemin
        Position currentPos(startX, startY);
        newPath.push_back(currentPos);
        // générer un chemin aléatoire
        for (int i = 0; i < pathLength; i++) {
            std::vector<Position> possibleMoves;
            
            // vérifier les mouvements possibles sans murs
            Position up(currentPos.x, currentPos.y - 1);
            Position right(currentPos.x + 1, currentPos.y);
            Position down(currentPos.x, currentPos.y + 1);
            Position left(currentPos.x - 1, currentPos.y);

            // vérifier les mouvements selon les murs
            if (currentPos.y > 0 && !maze.maze[currentPos.x][currentPos.y].topwall) 
                possibleMoves.push_back(up);
            
            if (currentPos.x < MazeConfig::grid_width - 1 && !maze.maze[currentPos.x][currentPos.y].rightwall) 
                possibleMoves.push_back(right);
            
            if (currentPos.y < MazeConfig::grid_height - 1 && !maze.maze[currentPos.x][currentPos.y].bottomwall) 
                possibleMoves.push_back(down);
            
            if (currentPos.x > 0 && !maze.maze[currentPos.x][currentPos.y].leftwall) 
                possibleMoves.push_back(left);

            // si aucun mouvement n'est possible, arrêter
            if (possibleMoves.empty()) break;

            // choisir un mouvement aléatoire
            Position nextPos = possibleMoves[GetRandomValue(0, possibleMoves.size() - 1)];
            newPath.push_back(nextPos);
            currentPos = nextPos;
        }

        return newPath;
}

// constructeur modifié pour accepter le nombre d'obstacles
Obstacle::Obstacle(const char *texturePath, int x, int y, float spd, float scl, Maze &maze, int pathLength)
: speed(spd), scale(scl) {
        
        // charger la texture
        texture = LoadTexture(texturePath);
        
        // générer un chemin aléatoire
        path = generateRandomPath(maze, x, y, pathLength);
 }

    // méthode de déplacement mise à jour
 void Obstacle::move(Maze &maze)
 {
    static float moveTimer = 0.0f;// temps de rafraichissement
        moveTimer += GetFrameTime();

        if (moveTimer >= 0.5f) {
            moveTimer = 0.0f;

            // Déterminer le prochain index de chemin
            if (movingForward) {
                currentPathIndex++;
                if (currentPathIndex >= path.size()) {
                    movingForward = false;
                    currentPathIndex = path.size() - 2; // Revenir en arrière
                }
            } else {
                currentPathIndex--;
                if (currentPathIndex == 0) {
                    movingForward = true;
                }
            }
        }
 }
// méthode de dessin
 void Obstacle::draw() const
 {
    if (currentPathIndex < path.size()) {// si le chemin est disponible
            Vector2 position = {
                static_cast<float>(MazeConfig::maze_offset_x + path[currentPathIndex].x * MazeConfig::cell_size),
                static_cast<float>(MazeConfig::maze_offset_y + path[currentPathIndex].y * MazeConfig::cell_size)
            };
            DrawTextureEx(texture, position, 0.0f, scale, WHITE);
        }
 }
// méthode pour obtenir le rectangle de collision
 Rectangle Obstacle::getCollisionRectangle() const
 {
     if (currentPathIndex < path.size()) {// si le chemin est disponible
            Vector2 posOnScreen = {
                static_cast<float>(MazeConfig::maze_offset_x + path[currentPathIndex].x * MazeConfig::cell_size),
                static_cast<float>(MazeConfig::maze_offset_y + path[currentPathIndex].y * MazeConfig::cell_size)
            };
            return {
                posOnScreen.x,
                posOnScreen.y,
                texture.width * scale,
                texture.height * scale
            };
        }
        // Retourner un rectangle vide si aucun chemin n'est disponible
        return {0, 0, 0, 0};
 }
// méthode pour réinitialiser l'obstacle
 void Obstacle::resetPosition(Maze &maze)
 {
    currentPathIndex = 0;// Revenir en arriere
        movingForward = true;// direction de l'obstacle
        
        // Régénérer un nouveau chemin à chaque réinitialisation
        path = generateRandomPath(maze, path[0].x, path[0].y, path.size());
 }


