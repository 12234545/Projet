#include "abeille.h"


//initialiser l'abeille
Player::Player(int x, int y, Maze &m, const char *imagePath)
 : position(x, y), goal(MazeConfig::grid_width - 1, 0), maze(m), hasWon(false) {
        texture = LoadTexture(imagePath); 
    
}

void Player::moveplayer(int dx, int dy)
{
     
    int newx = position.x + dx;
    int newy = position.y + dy;

    // Vérification des limites de la grille
    if (newx < 0 || newx >= MazeConfig::grid_width || newy < 0 || newy >= MazeConfig::grid_height) return;

    // Vérification des murs en fonction de la direction
    if (dx == -1 && (maze.maze[position.x][position.y].leftwall || maze.maze[newx][newy].rightwall)) return; // Mouvement à gauche
    if (dx == 1 && (maze.maze[position.x][position.y].rightwall || maze.maze[newx][newy].leftwall)) return; // Mouvement à droite
    if (dy == -1 && (maze.maze[position.x][position.y].topwall || maze.maze[newx][newy].bottomwall)) return; // Mouvement en haut
    if (dy == 1 && (maze.maze[position.x][position.y].bottomwall || maze.maze[newx][newy].topwall)) return; // Mouvement en bas

    
    position.x = newx;
    position.y = newy;

    //condition pour gagner(si l'abielle atteint l'objectif)
    if (position.x == goal.x && position.y == goal.y) hasWon = true;

}

void Player::draw()
{
    //position de l'abeille sur l'ecran
   Vector2 positionOnScreen = {
        static_cast<float>(MazeConfig::maze_offset_x) + static_cast<float>(position.x) * static_cast<float>(MazeConfig::cell_size),
        static_cast<float>(MazeConfig::maze_offset_y) + static_cast<float>(position.y) * static_cast<float>(MazeConfig::cell_size)
    }; 
    float scale = 0.10f; 
    DrawTextureEx(texture, positionOnScreen, 0.0f, scale, WHITE);
}

void Player::drawGoal()
{
    Vector2 positionOnScreen = {
           static_cast<float>(MazeConfig::maze_offset_x) + static_cast<float>(goal.x) * static_cast<float>(MazeConfig::cell_size),
           static_cast<float>(MazeConfig::maze_offset_y) + static_cast<float>(goal.y) * static_cast<float>(MazeConfig::cell_size)
       };
       float scale = 0.24f; 
       DrawTextureEx(texture, positionOnScreen, 0.0f, scale, WHITE);
}

void Player::possistionabb()
{
    position = {0, MazeConfig::grid_height - 1};
    hasWon = false;
}

Rectangle Player::getCollisionRectangle() const
{
    Vector2 positionOnScreen = {
        static_cast<float>(MazeConfig::maze_offset_x) + static_cast<float>(position.x) * static_cast<float>(MazeConfig::cell_size),
        static_cast<float>(MazeConfig::maze_offset_y) + static_cast<float>(position.y) * static_cast<float>(MazeConfig::cell_size)
    };
    float scale = 0.10f; // Échelle définie lors du dessin
    return {
        positionOnScreen.x,
        positionOnScreen.y,
        texture.width * scale,
        texture.height * scale
    };
    return Rectangle();
}


