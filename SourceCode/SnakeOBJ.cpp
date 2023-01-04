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
  
  for(int i = 0; i < 3000 * SnakeTail::snCount; ++i)
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


void SnakeOBJ::motionAndViewTail (RenderWindow &window, TimeGame &timeGame) // Функция, управляющая работой хвоста
{
  head.motionAndViewHead(window, timeGame.getTime());
  
  road[X].insert(road[X].begin(), head.fSnakeHeadX);    // Сохранение маршрута/координат головы змейки по X
  road[Y].insert(road[Y].begin(), head.fSnakeHeadY);    // Сохранение маршрута/координат головы змейки по Y
  road[DIR].insert(road[DIR].begin(), head.sDirection); // Сохранение направлений головы змейки на маршруте
  
  
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
      
      //cout << "Delay between objects: " << SnakeTail::delay << endl
      //   << "Time has passed: " << time << endl
      //   << "Tail objects in the game: " << SnakeTail::snCount << endl;	  
    }
  
  
  if (SnakeTail::nDelay > SnakeTail::nSizeTail) SnakeTail::nSizeTail = SnakeTail::nDelay; // Сохранение самой большой зафиксированной задержки между ячейками
  
  if ((int)road[X].size() > SnakeTail::nSizeTail * (SnakeTail::snCount+1)) road[X].pop_back();     // Удаление лишних координат маршрута головы по X
  if ((int)road[Y].size() > SnakeTail::nSizeTail * (SnakeTail::snCount+1)) road[Y].pop_back();     // Удаление лишних координат маршрута головы по Y
  if ((int)road[DIR].size() > SnakeTail::nSizeTail * (SnakeTail::snCount+1)) road[DIR].pop_back(); // Удаление лишних направлений головы на маршруте
  
  
  for(short i = 0; i < SnakeTail::snCount; ++i)
    {
      if (SnakeTail::snPrevCount != SnakeTail::snCount && i == SnakeTail::snCount-1) // Замена текстуры хвоста на туловище у предпоследнего объекта
	{
	  ++SnakeTail::snPrevCount;
	  tail[i-2]->snakeTail.setTexture(tail[i]->bodyTail);
	  tail[i-1]->snakeTail.setTexture(tail[i]->firstEndTail);
	}
      
      if (head.sDirection != -1) // До начала движения хвост стоит на месте
	{
	  // Установка позиции объектов хвоста
	  
	  tail[i]->snakeTail.setPosition(road[X][((i+1) * SnakeTail::nDelay) + SnakeTail::nHeadDelayDiffer],  // Позиция с учётом смещения ячейки и размера головы по X
					 road[Y][((i+1) * SnakeTail::nDelay) + SnakeTail::nHeadDelayDiffer]); // Позиция с учётом смещения ячейки и размера головы по Y
	  
	  
	  switch((int)road[DIR][((i+1) * SnakeTail::nDelay) + SnakeTail::nHeadDelayDiffer]) // Установка направления текстуры с учётом смещения ячейки и размера головы
	    {
	      
	    case UP:
	      {
		tail[i]->snakeTail.setTextureRect(IntRect(tail[i]->snDirectionTail[UP][0],tail[i]->snDirectionTail[UP][1],
							  tail[i]->sSizeTail, tail[i]->sSizeTail)); 
	      };
	      break;
	      
	    case DOWN:
	      {
		tail[i]->snakeTail.setTextureRect(IntRect(tail[i]->snDirectionTail[DOWN][0], tail[i]->snDirectionTail[DOWN][1],
							  tail[i]->sSizeTail, tail[i]->sSizeTail));
	      };
	      break;
	      
	    case LEFT:
	      {
		tail[i]->snakeTail.setTextureRect(IntRect(tail[i]->snDirectionTail[LEFT][0],tail[i]->snDirectionTail[LEFT][1],
							  tail[i]->sSizeTail, tail[i]->sSizeTail));
	      };
	      break;
	      
	    case RIGHT:
	      {
		  tail[i]->snakeTail.setTextureRect(IntRect(tail[i]->snDirectionTail[RIGHT][0], tail[i]->snDirectionTail[RIGHT][1],
							    tail[i]->sSizeTail, tail[i]->sSizeTail));
	      };
	      break;
	      
	    }
	}
    }
  
  for (short i = 0; i < SnakeTail::snCount; ++i) // Отрисовка хвоста на экране
    {window.draw(tail[i]->snakeTail);}
}

