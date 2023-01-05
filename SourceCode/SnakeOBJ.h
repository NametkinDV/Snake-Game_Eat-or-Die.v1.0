#ifndef SnakeOBJ_h
#define SnakeOBJ_h

#include <vector>
#include "CommonSettings.h"
#include "TimeGame.h"
#include "SnakeHead.h"
#include "SnakeTail.h"

using namespace std;

class SnakeOBJ final
{
  //protected:
public:
  SnakeHead head;               // Голова змейки
  vector <vector<double>> road; // Путь головы змейки
  vector <SnakeTail*> tail;     // Хвост змейки

  vector<double> one;
  vector<double> two;
  vector<double> three;
  
public:
  SnakeOBJ();
  ~SnakeOBJ();


  void movementAndDisplay (RenderWindow &window, TimeGame &timeGame); // Функция, управляющая работой хвоста
  void saveHeadRoute();                                               // Функция сохранения маршрута головы
  void deleteRedundantHeadRoute();                                    // Функция удаления лишнего маршрута головы
  void tailDelayCalculation(TimeGame &timeGame);                      // Функция вычисления задержки ячеек хвоста друг за другом
  void setEndTailTexture(short &endPosition);                         // Установка текстур туловища и первой половины конца хвоста
  void setPositionAndDirection(short &position);                      // Установка позиции и направления текстуры
  void drawTail(RenderWindow &window);                                // Отрисовка хвоста на экране
  void resetTail(vector <SnakeTail*> &tail);                          // Функция сброса параметров хвоста змейки до начальных
  
};

#endif
