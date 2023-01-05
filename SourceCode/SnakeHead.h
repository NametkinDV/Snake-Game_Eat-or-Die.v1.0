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

  enum GameLossControl { WithoutMenu, WithMenu, GameOver};
  int nHeadControlLosingTheGame;
  
  
  void motionAndViewHead (RenderWindow &window, const double &time); // Функция движения головы
  void controlHead (Event event); // Функция управления головой
  void resetHead(); // Функция сброса параметров головы змейки до начальных
  
};
#endif
