#ifndef Background_h
#define Background_h

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "TextGame.h"

using namespace std;
using namespace sf;

class Background // Фон
{
public:
  Background(const string &path);
  Background(const string &path, const short &sizeX, const short &sizeY);
  Background(const string &path, const short &sizeX, const short &sizeY, const short &numOfTextLines);
  
  Texture textureBackground;
  Sprite backgroundArea; 
  string pathOfTexture;
  short sSizeBackgroundX;
  short sSizeBackgroundY;
  short sHalfSizeBackgroundX;
  short sHalfSizeBackgroundY;

  vector <TextGame> textLine;
  
  
  void drawBackground(RenderWindow &window); // Отрисовка фона в окне
  
};

#endif
