#ifndef SnakeTail_h
#define SnakeTail_h

#include "SnakeHead.h"

class SnakeTail final
{
public:
  explicit SnakeTail(SnakeHead &head);
  
  static short snCount;
  static short snPrevCount;
  static int delay;
  static int nSizeTail;
  static bool bStartWithTime;
  
  Texture endTail;
  Texture bodyTail;
  Sprite snakeTail;

  short sSizeTail;
  short sHalfST;
  float fSnakeTailX;
  float fSnakeTailY;
  
  short snDirectionTail[4][2] = // Координаты отрисовки текстур хвоста и туловища
    {
     {0, 0},   // Вверх
     {0, 60},  // Вниз
     {60, 0},  // Влево
     {60, 60}  // Вправо
    };

};
#endif
