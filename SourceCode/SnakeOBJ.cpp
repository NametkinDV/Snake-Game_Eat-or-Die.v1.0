#include "SnakeOBJ.h"


SnakeOBJ::SnakeOBJ()
{
  road.push_back(one);
  road.push_back(two);
  road.push_back(three);
  
  // Выделение памяти хвосту
  
  for(int i = 0; i < 100; ++i)
    {
      tail.push_back(new SnakeTail(head));
    }
  
  for(int i = 0; i < 1500 * (SnakeTail::snCount+1); ++i)
    {
      road[X].push_back(0);
      road[Y].push_back(0);
      road[DIR].push_back(0);
    }
  
}


SnakeOBJ::~SnakeOBJ()
{
  // Освобождение выделенной памяти
  
  for(int i = 0; i < 100; ++i)
    {
      delete tail[i];
      tail[i] = nullptr;
    }
  
  tail.clear();
}


void SnakeOBJ::movementAndDisplay (RenderWindow &window, TimeGame &timeGame) // Функция, управляющая работой хвоста
{
  head.motionAndViewHead(window, timeGame.getTime());
  
  saveHeadRoute(); 
  tailDelayCalculation(timeGame);
  deleteRedundantHeadRoute();
  
  //cout << "Delay between objects: " << SnakeTail::delay << endl
  //   << "Time has passed: " << time << endl
  //   << "Tail objects in the game: " << SnakeTail::snCount << endl;
  
  for(short i = 0; i < SnakeTail::snCount; ++i)
    {
      if (SnakeTail::snCount != SnakeTail::snPrevCount && i == SnakeTail::snCount-1)
	{
	  setEndTailTexture(SnakeTail::snCount);
	  ++SnakeTail::snPrevCount;
	}
      setPositionAndDirection(i);
    }
  
  drawTail(window);
}


void SnakeOBJ::saveHeadRoute() // Функция сохранения маршрута головы
{
  road[X].insert(road[X].begin(), head.fSnakeHeadX);    // Сохранение маршрута/координат головы змейки по X
  road[Y].insert(road[Y].begin(), head.fSnakeHeadY);    // Сохранение маршрута/координат головы змейки по Y
  road[DIR].insert(road[DIR].begin(), head.sDirection); // Сохранение направлений головы змейки на маршруте
}


void SnakeOBJ::deleteRedundantHeadRoute() // Функция удаления лишнего маршрута головы
{
  if (SnakeTail::nDelay > SnakeTail::nMaxDelay) SnakeTail::nMaxDelay = SnakeTail::nDelay; // Сохранение самой большой зафиксированной задержки между ячейками
  
  if ((int)road[X].size() > SnakeTail::nMaxDelay * (SnakeTail::snCount+1)) road[X].pop_back();     // Удаление лишних координат маршрута головы по X
  if ((int)road[Y].size() > SnakeTail::nMaxDelay * (SnakeTail::snCount+1)) road[Y].pop_back();     // Удаление лишних координат маршрута головы по Y
  if ((int)road[DIR].size() > SnakeTail::nMaxDelay * (SnakeTail::snCount+1)) road[DIR].pop_back(); // Удаление лишних направлений головы на маршруте
}


void SnakeOBJ::tailDelayCalculation(TimeGame &timeGame) // Функция вычисления задержки ячеек хвоста друг за другом
{
  if (head.sDirection == -1 && timeGame.getCount() < 5 && SnakeTail::bStartWithTime == false) // Первые 4 замера времени в начале игры задержка хвоста без учёта времени
    {
      SnakeTail::nDelay = tail[0]->sSizeTail / head.fSpeed;
      SnakeTail::nHeadDelayDiffer = (head.sHalfSH - tail[0]->sHalfST) / head.fSpeed;
    } 
  
  else // Задержка хвоста с учётом времени
    {
      SnakeTail::bStartWithTime = true;
      SnakeTail::nDelay = (tail[0]->sSizeTail / head.fSpeed) / timeGame.getTime(); // Вычисление задержки хвоста за головой
      SnakeTail::nHeadDelayDiffer = ((head.sHalfSH - tail[0]->sHalfST) / head.fSpeed) / timeGame.getTime(); // Вычисление дополнительной задержки при разнице размеров с головой
    }
}


void SnakeOBJ::setEndTailTexture(short &endPosition) // Установка текстур туловища и первой половины конца хвоста
{
  if (endPosition-3 >= 0) tail[endPosition-3]->snakeTail.setTexture(tail[endPosition-1]->bodyTail);     // Установка текстуры туловища
  if (endPosition-2 >= 0) tail[endPosition-2]->snakeTail.setTexture(tail[endPosition-1]->firstEndTail); // Установка текстуры первой половины конца хвоста
}


void SnakeOBJ::setPositionAndDirection(short &position) // Установка позиции и направления текстуры
{
  if (head.sDirection != -1) // До начала движения хвост стоит на месте
    {
      // Установка позиции объектов хвоста
      
 tail[position]->snakeTail.setPosition(road[X][((position+1) * SnakeTail::nDelay) + SnakeTail::nHeadDelayDiffer], // Позиция с учётом смещения ячейки и размера головы по X
				       road[Y][((position+1) * SnakeTail::nDelay) + SnakeTail::nHeadDelayDiffer]);// Позиция с учётом смещения ячейки и размера головы по Y
      
 
      switch((int)road[DIR][((position+1) * SnakeTail::nDelay) + SnakeTail::nHeadDelayDiffer]) // Установка направления текстуры с учётом смещения ячейки и размера головы
	{
	  
	case UP:
	  {
	    tail[position]->snakeTail.setTextureRect(IntRect(tail[position]->snDirectionTail[UP][0],tail[position]->snDirectionTail[UP][1],
							     tail[position]->sSizeTail, tail[position]->sSizeTail)); 
	  };
	  break;
	  
	case DOWN:
	  {
	    tail[position]->snakeTail.setTextureRect(IntRect(tail[position]->snDirectionTail[DOWN][0], tail[position]->snDirectionTail[DOWN][1],
							     tail[position]->sSizeTail, tail[position]->sSizeTail));
	  };
	  break;
	  
	case LEFT:
	  {
	    tail[position]->snakeTail.setTextureRect(IntRect(tail[position]->snDirectionTail[LEFT][0],tail[position]->snDirectionTail[LEFT][1],
							     tail[position]->sSizeTail, tail[position]->sSizeTail));
	  };
	  break;
	  
	case RIGHT:
	  {
	    tail[position]->snakeTail.setTextureRect(IntRect(tail[position]->snDirectionTail[RIGHT][0], tail[position]->snDirectionTail[RIGHT][1],
							     tail[position]->sSizeTail, tail[position]->sSizeTail));
	  };
	  break;
	  
	}
    }
}


void SnakeOBJ::drawTail(RenderWindow &window) // Отрисовка хвоста на экране
{
  for (short i = 0; i < SnakeTail::snCount; ++i) // Отрисовка хвоста на экране
    {
      window.draw(tail[i]->snakeTail);
    }
}


void SnakeOBJ::resetTail(vector <SnakeTail*> &tail) // Функция сброса параметров хвоста змейки до начальных
{
  tail[0]->resetStaticDataTail();
  
  for (unsigned int i = 0; i < tail.size(); ++i)
    {
      tail[i]->snakeTail.setTexture(tail[i]->secondEndTail);
    }
  
  setEndTailTexture(SnakeTail::snCount);
  
  tail[0]->snakeTail.setPosition(head.fSnakeHeadX, head.fSnakeHeadY + head.sHalfSH + tail[0]->sHalfST);
  tail[0]->snakeTail.setTextureRect(IntRect(tail[0]->snDirectionTail[UP][0], tail[0]->snDirectionTail[UP][1], tail[0]->sSizeTail, tail[0]->sSizeTail));
  tail[1]->snakeTail.setPosition(head.fSnakeHeadX, head.fSnakeHeadY + head.sHalfSH + tail[1]->sSizeTail + tail[1]->sHalfST);
  tail[1]->snakeTail.setTextureRect(IntRect(tail[1]->snDirectionTail[UP][0], tail[1]->snDirectionTail[UP][1], tail[1]->sSizeTail, tail[1]->sSizeTail));
}
