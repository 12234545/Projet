#pragma once
#include<raylib.h>

class Button
{
  public :
  //declaration des attributs
    Texture2D texture;//texture du bouton
    Vector2 position;//position du bouton
    Rectangle rect;//rectangle de collision du bouton avec la souris
    bool isClick;//si le bouton est cliquer
    //declaration des méthodes
    Button();//constructeur
    Button(const char* imagePath, Vector2 butposition,float sizeScale);//constructeur
    bool isClicked();//verifier si le bouton est cliquer
    void Draw() const;//dessiner le bouton
    void deletTexture();//destructeur
};