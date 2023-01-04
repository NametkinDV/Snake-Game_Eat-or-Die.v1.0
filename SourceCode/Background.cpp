#include "Background.h"


Background::Background(const string &path) : pathOfTexture(path)
{
  textureBackground.loadFromFile(pathOfTexture); // Путь к текстурам фона
  backgroundArea.setTexture(textureBackground);  // Присвоение текстуры спрайту
}

Background::Background(const string &path, const short &sizeX, const short &sizeY) : pathOfTexture(path), sSizeBackgroundX(sizeX), sSizeBackgroundY(sizeY)
{
  textureBackground.loadFromFile(pathOfTexture); // Путь к текстурам фона
  backgroundArea.setTexture(textureBackground);  // Присвоение текстуры спрайту
  sHalfSizeBackgroundX = sSizeBackgroundX / 2;
  sHalfSizeBackgroundY = sSizeBackgroundY / 2;
  backgroundArea.setOrigin(sHalfSizeBackgroundX, sHalfSizeBackgroundY);
}

Texture textureBackground;
Sprite backgroundArea; 
string pathOfTexture;
short sSizeBackgroundX;
short sSizeBackgroundY;
short sHalfSizeBackgroundX;
short sHalfSizeBackgroundY;

void Background::drawBackground(RenderWindow &window) // Отрисовка фона в окне
{
  window.draw(backgroundArea);
}

