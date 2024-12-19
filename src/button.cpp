#include "button.h"
#include "abeille.h"
#include <raylib.h>
#include <iostream>
//constructeur
Button::Button(const char *imagePath,Vector2 butposition, float sizeScale)
{
  
    Image image = LoadImage(imagePath); //image de bouton
    int originalWidth = image.width;
    int originalHeight = image.height;

    int newWidth = static_cast<int>(originalWidth * sizeScale); //nouvelle largeur
    int newHeight = static_cast<int>(originalHeight * sizeScale);//nouvelle hauteur
    ImageResize(&image, newWidth, newHeight);//redimensionner l'image
    texture = LoadTextureFromImage(image);//charger la texture
    UnloadImage(image);
    position = butposition;//position du bouton
    //rectangle de collision du bouton avec la souris
    rect = {position.x, position.y, static_cast<float>(newWidth), static_cast<float>(newHeight)};
}
//verifier si le bouton est cliquer
bool Button::isClicked()
{
   if(CheckCollisionPointRec(GetMousePosition(),rect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
      isClick= true;
   }else {
      isClick= false;
   }
   return isClick;

}
//methode de dessin (affichage)
void Button::Draw() const
{
    DrawTextureV(texture,position, WHITE);
}
//destructeur
void Button::deletTexture()
{
      UnloadTexture(texture);
}
