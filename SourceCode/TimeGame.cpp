#include "TimeGame.h"
#include <iostream>
#include <chrono>

using namespace std;

TimeGame::TimeGame()
  {
    dTimeStartGame = chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now().time_since_epoch()).count(); // Фиксация времени при запуске
  }
  
  
double TimeGame::timeHasPassed() // Подсчёт времени (в миллисекундах) / Ритм игры
  {
    dMicroSec = chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now().time_since_epoch()).count(); //Получение времени(микросекунды)
    dMicroSec -= dTimeStartGame;

    return dMicroSec;
  }
  
  
void TimeGame::resetTime() // Обнуление подсчёта времени
  {
    dTimeStartGame = chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now().time_since_epoch()).count();
  }
  
  
void TimeGame::averageTime() // Подсчёт среднего времени прохождения цикла игры
  {
    time = timeHasPassed();
    time /= 100;
    resetTime();

    dSumTime += time;
    ++nCount;
	
    time = (dSumTime / nCount);
	
    if (nCount > 100000)
      {
	dSumTime /= 2;
	nCount /= 2;
      }
    //cout << time << endl; // Вывод полученного времени
  }
  
  
double TimeGame::getTime() // Получение текущего среднего времени прохождения цикла игры
  {
    return time;
  }
  
  
int TimeGame::getCount() // Получение количества замеров времени
  {
    return nCount;
  }
