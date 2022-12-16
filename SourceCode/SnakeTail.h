#ifndef SnakeTail_h
#define SnakeTail_h

#include "SnakeHead.h"

class SnakeTail final
{
public:
  explicit SnakeTail(SnakeHead &head);
  
  static short snCount;
  static short snPrevCount;
  static int nDelay;
  static int nHeadDelayDiffer;
  static int nSizeTail;
  static bool bStartWithTime;
  
  Texture bodyTail;
  Texture firstEndTail;
  Texture secondEndTail;
  Sprite snakeTail;

  short sSizeTail;
  short sHalfST;
  float fSnakeTailX;
  float fSnakeTailY;
  
  short snDirectionTail[4][2] = // Координаты отрисовки текстур хвоста и туловища
    {
     {0, 0},   // Вверх
     {0, 26},  // Вниз
     {26, 0},  // Влево
     {26, 26}  // Вправо
    };

};
#endif
