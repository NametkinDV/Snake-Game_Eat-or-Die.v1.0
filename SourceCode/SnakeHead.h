#ifndef SnakeHead_h
#define SnakeHead_h

#include <SFML/Graphics.hpp>

using namespace sf;

class SnakeHead // Голова змейки
{
public:
  explicit SnakeHead();
  
  Texture textureHead;
  Sprite snakeHead;
  
  short sSizeHead;
  short sHalfSH;
  double fSnakeHeadX;
  double fSnakeHeadY;
  double fSpeed;
  short sDirection;
  short sDirectionHead[4][2] = // Координаты отрисовки текстур головы
    {
     {0, 0},   // Вверх
     {0, 60},  // Вниз
     {60, 0},  // Влево
     {60, 60}  // Вправо
    };
  
  
  void motionAndViewHead (RenderWindow &window, const double &time); // Функция движения головы
    
};
#endif
