#ifndef SnakeTail_h
#define SnakeTail_h

#include "SnakeHead.h"

class SnakeTail final
{
public:
  explicit SnakeTail(SnakeHead &head);
  
  static short snCount;        // Количество ячеек хвоста на поле
  static short snPrevCount;    // Предыдущее количество ячеек хвоста на поле
  static int nDelay;           // Задержка между ячейками хвоста
  static int nHeadDelayDiffer; // Различие в размерах между ячейкой головы и первой ячейкой хвоста
  static int nMaxDelay;        // Самая большая зафиксированная задержка между ячейками хвоста
  static bool bStartWithTime;  // Переключатель для вычислений задержки с учётом времени и без него
  
  Texture bodyTail;
  Texture firstEndTail;
  Texture secondEndTail;
  Sprite snakeTail;

  short sSizeTail; // Размер ячейки хвоста
  short sHalfST;   // Размер половины ячейки хвоста
  
  short snDirectionTail[4][2] = // Координаты отрисовки текстур хвоста и туловища
    {
      {0, 0},   // Вверх
      {0, 26},  // Вниз
      {26, 0},  // Влево
      {26, 26}  // Вправо
    };

  
  void resetStaticDataTail(); // Функция сброса параметров хвоста змейки до начальных
  
};

#endif
