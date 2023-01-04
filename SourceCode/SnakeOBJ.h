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


  void motionAndViewTail (RenderWindow &window, TimeGame &timeGame); // Функция, управляющая работой хвоста

};


#endif
