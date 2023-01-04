#ifndef Food_h
#define Food_h

#include <SFML/Graphics.hpp>
#include "CommonSettings.h"
#include "SnakeHead.h"
#include "SnakeTail.h"
#include "BackgroundLevel.h"


using namespace sf;

class Food final
{
public:
  explicit Food(BackgroundLevel &background);

  Texture textureApple;
  Sprite food;

  short sSizeFood;
  short fHalfFood;
  float fPositionFoodX;
  float fPositionFoodY;


  void eatFood(RenderWindow &window, SnakeHead &head, BackgroundLevel &background); // Функция съедания еды змейкой
  
};


#endif
