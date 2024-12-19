#pragma once

class MazeConfig {
public:
// Dimensions de la fenêtre
    static constexpr int screen_width = 1600;
    static constexpr int screen_height = 900;
//dimention de la cellule
    static constexpr int cell_size = 60;
    //dimensions du labyrinthe
    static constexpr int grid_width = 20;
    static constexpr int grid_height = 10;
    //dimensions de la lumiere
    static constexpr int light_distance = 1;
    //position du labyrinthe (le centrer)
    static constexpr int maze_offset_x = (screen_width - (grid_width * cell_size)) / 2;
    static constexpr int maze_offset_y = (screen_height - (grid_height * cell_size)) / 2;
};




