#ifndef TimeGame_h
#define TimeGame_h

class TimeGame final
{ 
private:
  double time = 0;
  double dTimeStartGame = 0;
  double dMicroSec = 0;
  double dSumTime = 0;
  int nCount = 0;
  
public:
  TimeGame();
   
  double timeHasPassed(); // Подсчёт времени (в миллисекундах) / Ритм игры
  void resetTime(); // Обнуление подсчёта времени
  void averageTime(); // Подсчёт среднего времени прохождения цикла игры
  double getTime(); // Получение текущего среднего времени прохождения цикла игры
  int getCount(); // Получение количества замеров времени
   
};
#endif
