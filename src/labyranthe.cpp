#include "labyranthe.h"

//initialiser le labyrinthe
void Maze::initializeMaze()
{
    // Remplir le labyrinthe avec des cellules vides
        for (int x = 0; x < MazeConfig::grid_width; x++) {
            for (int y = 0; y < MazeConfig::grid_height; y++) {
                maze[x][y] = Cell();
            }
        }
}

//generer le labyrinthe
void Maze::generatemaze(int x, int y)
{
    maze[x][y].visited = true;
    //choisir une direction aléatoire
        int directions[] = {0, 1, 2, 3};
        for (int i = 0; i < 4; i++) {
            //choisir une direction aléatoire
            int j = GetRandomValue(i, 3);
            int temp = directions[i];
            directions[i] = directions[j];
            directions[j] = temp;
        }

        //parcourir les directions
        for (int i = 0; i < 4; i++) {
            int nx = x, ny = y;
            if (directions[i] == 0) ny -= 1;
            else if (directions[i] == 1) nx += 1;
            else if (directions[i] == 2) ny += 1;
            else if (directions[i] == 3) nx -= 1;
          //si les coordonnées sont valides et que la cellule n'a pas encore ete visitee
            if (nx >= 0 && nx < MazeConfig::grid_width && ny >= 0 && ny < MazeConfig::grid_height && !maze[nx][ny].visited) {
                //supprimer le mur
                if (directions[i] == 0) {
                    maze[x][y].topwall = false;
                    maze[nx][ny].bottomwall = false;
                } else if (directions[i] == 1) {
                    maze[x][y].rightwall = false;
                    maze[nx][ny].leftwall = false;
                } else if (directions[i] == 2) {
                    maze[x][y].bottomwall = false;
                    maze[nx][ny].topwall = false;
                } else if (directions[i] == 3) {
                    maze[x][y].leftwall = false;
                    maze[nx][ny].rightwall = false;
                }
                generatemaze(nx, ny);
            }
        }
}

//ajouter des cycles
void Maze::addCycles(int count)
{
    //ajouter le nombre de cycles souhaité
    for (int i = 0; i < count; i++) {
        //choisir une cellule aléatoire
        int x = GetRandomValue(0, MazeConfig::grid_width - 2);
        int y = GetRandomValue(0, MazeConfig::grid_height - 2);
        if (!maze[x][y].visited) continue;
       //supprimer un mur aléatoire
        if (GetRandomValue(0, 1)) maze[x][y].rightwall = false;
        else maze[x][y].bottomwall = false;
    }
}

//dessiner le labyrinthe complet
void Maze::drawCompleteMaze()
{
    
     for (int x = 0; x < MazeConfig::grid_width; x++) {
        for (int y = 0; y < MazeConfig::grid_height; y++) {
            Vector2 topLeft = {MazeConfig::maze_offset_x + x * MazeConfig::cell_size, 
                               MazeConfig::maze_offset_y + y * MazeConfig::cell_size};
            // Dessiner les murs avec des textures
            if (maze[x][y].topwall) {
                Rectangle destRect = {topLeft.x, topLeft.y, MazeConfig::cell_size, 5}; // Mur horizontal
                DrawTexturePro(wallTexture, {0, 0, (float)wallTexture.width, (float)wallTexture.height}, destRect, {0, 0}, 0.0f, WHITE);
            }
            if (maze[x][y].bottomwall) {
                Rectangle destRect = {topLeft.x, topLeft.y + MazeConfig::cell_size - 5, MazeConfig::cell_size, 5}; // Mur horizontal
                DrawTexturePro(wallTexture, {0, 0, (float)wallTexture.width, (float)wallTexture.height}, destRect, {0, 0}, 0.0f, WHITE);
            }
            if (maze[x][y].leftwall) {
                Rectangle destRect = {topLeft.x, topLeft.y, 5, MazeConfig::cell_size}; // Mur vertical
                DrawTexturePro(wallTexture, {0, 0, (float)wallTexture.width, (float)wallTexture.height}, destRect, {0, 0}, 0.0f, WHITE);
            }
            if (maze[x][y].rightwall) {
                Rectangle destRect = {topLeft.x + MazeConfig::cell_size - 5, topLeft.y, 5, MazeConfig::cell_size}; // Mur vertical
                DrawTexturePro(wallTexture, {0, 0, (float)wallTexture.width, (float)wallTexture.height}, destRect, {0, 0}, 0.0f, WHITE);
            }
        }
    }
}

//dessiner une portion du labyrinthe autour du joueur
void Maze::drawNearMaze(const Position &position)
{
    // Effacer l'écran
    DrawRectangle(0,0,GetScreenWidth(),GetScreenHeight(),BLACK);
    for (int x = position.getX() - MazeConfig::light_distance; x <= position.getX() + MazeConfig::light_distance; x++) {
        for (int y = position.getY() - MazeConfig::light_distance; y <= position.getY() + MazeConfig::light_distance; y++) {
            // Vérifiez si les coordonnées sont dans les limites du labyrinthe
            if (x >= 0 && x < MazeConfig::grid_width && y >= 0 && y < MazeConfig::grid_height) {
                Rectangle desRect1 = {
                    MazeConfig::maze_offset_x + x * MazeConfig::cell_size,
                    MazeConfig::maze_offset_y + y * MazeConfig::cell_size,
                    MazeConfig::cell_size,
                    MazeConfig::cell_size

                };
                // Dessiner le fond
                Rectangle sourceRect ={0.0f,0.0f, BackgroundTexture.width, BackgroundTexture.height};
                DrawTexturePro(BackgroundTexture, sourceRect, desRect1, {0, 0}, 0.0f, WHITE);
                Vector2 topLeft = {MazeConfig::maze_offset_x + x * MazeConfig::cell_size, 
                                   MazeConfig::maze_offset_y + y * MazeConfig::cell_size};
                // Dessiner les murs avec des textures
                if (maze[x][y].topwall) {
                    Rectangle destRect = {topLeft.x, topLeft.y, MazeConfig::cell_size, 5}; // Mur horizontal
                    DrawTexturePro(wallTexture, {0, 0, (float)wallTexture.width, (float)wallTexture.height}, destRect, {0, 0}, 0.0f, WHITE);
                }
                if (maze[x][y].bottomwall) {
                    Rectangle destRect = {topLeft.x, topLeft.y + MazeConfig::cell_size - 5, MazeConfig::cell_size, 5}; // Mur horizontal
                    DrawTexturePro(wallTexture, {0, 0, (float)wallTexture.width, (float)wallTexture.height}, destRect, {0, 0}, 0.0f, WHITE);
                }
                if (maze[x][y].leftwall) {
                    Rectangle destRect = {topLeft.x, topLeft.y, 5, MazeConfig::cell_size}; // Mur vertical
                    DrawTexturePro(wallTexture, {0, 0, (float)wallTexture.width, (float)wallTexture.height}, destRect, {0, 0}, 0.0f, WHITE);
                }
                if (maze[x][y].rightwall) {
                    Rectangle destRect = {topLeft.x + MazeConfig::cell_size - 5, topLeft.y, 5, MazeConfig::cell_size}; // Mur vertical
                    DrawTexturePro(wallTexture, {0, 0, (float)wallTexture.width, (float)wallTexture.height}, destRect, {0, 0}, 0.0f, WHITE);
                }
            }
        }
    }
}

//mise a jour du labyrinthe
void Maze::miseajour()
{
    // Réinitialiser l'état du labyrinthe
    initializeMaze();

    // Générer un nouveau labyrinthe
    generatemaze(0, 0);

    // Ajouter des cycles pour augmenter la complexité (optionnel)
    addCycles(5);

    // Exemple de modification : supprimer un mur spécifique (peut être utilisé pour des niveaux)
    maze[MazeConfig::grid_width - 1][0].bottomwall = false;
    maze[MazeConfig::grid_width - 1][0].topwall = false;
}

//ajouter des chemins trompeurs
void Maze::addDeceptivePaths(int count, int maxLength)
{
    //ajouter le nombre de chemins souhaité
    for (int i = 0; i < count; i++) {
        //choisir une cellule aléatoire
        int x = GetRandomValue(0, MazeConfig::grid_width - 1);
        int y = GetRandomValue(0, MazeConfig::grid_height - 1);

        if (!maze[x][y].visited) continue;

    //la longueur du chemin aléatoire entre 1 et maxLength
        int pathLength = GetRandomValue(1, maxLength);
        int currentX = x, currentY = y;

        for (int j = 0; j < pathLength; j++) {
            int direction = GetRandomValue(0, 3);
            int nx = currentX, ny = currentY;

            //choisir une direction aléatoire
            if (direction == 0 && currentY > 0) ny -= 1;            
            else if (direction == 1 && currentX < MazeConfig::grid_width - 1) nx += 1;  
            else if (direction == 2 && currentY < MazeConfig::grid_height - 1) ny += 1; 
            else if (direction == 3 && currentX > 0) nx -= 1;      
            else continue;

            //si les coordonnées sont valides et que la cellule n'a pas encore ete visitee
            if (!maze[nx][ny].visited) {
                
                if (direction == 0) {
                    maze[currentX][currentY].topwall = false;
                    maze[nx][ny].bottomwall = false;
                } else if (direction == 1) {
                    maze[currentX][currentY].rightwall = false;
                    maze[nx][ny].leftwall = false;
                } else if (direction == 2) {
                    maze[currentX][currentY].bottomwall = false;
                    maze[nx][ny].topwall = false;
                } else if (direction == 3) {
                    maze[currentX][currentY].leftwall = false;
                    maze[nx][ny].rightwall = false;
                }

            
                maze[nx][ny].visited = true;
                currentX = nx;
                currentY = ny;
            } else {
                break;
            }
        }
    }
}
//destructeur
Maze::~Maze()
{
    UnloadTexture(wallTexture); 
    UnloadTexture(BackgroundTexture);
}
