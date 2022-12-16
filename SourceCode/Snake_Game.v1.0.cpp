// Версия игры Snake: Eat or Die v1.0.
// Игра создана на базе библиотеки SFML.
// Файл содержит 3 класса: Фон, Змейка, Еда
// и функцию управления игрой.
// Дополнительно подключаются собственные библиотеки: Общие настройки, Игровое время, Голова змейки, Хвост змейки.
// Автор: Намёткин Дмитрий.

#include <iostream>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <vector>
#include "CommonSettings.h"
#include "TimeGame.h"
#include "SnakeHead.h"
#include "SnakeTail.h"

using namespace std;
using namespace sf;


class Background // Фон игры
{
public:
  Background()
  {
    textureBackground.loadFromFile("./Textures.1.0/Wall.png"); // Путь к текстурам фона
    backgroundArea.setTexture(textureBackground);              // Присвоение текстуры спрайту
  }
  
  Texture textureBackground;
  Sprite backgroundArea;
  
};


class SnakeOBJ
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
  SnakeOBJ()
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

  
  ~SnakeOBJ()
  {
  // Освобождение выделенной памяти
  
  for(int i = 0; i < 100; ++i)
    {
      delete tail[i];
      tail[i] = nullptr;
    }
  
  tail.clear();
  }


  void motionAndViewTail (RenderWindow &window, TimeGame &timeGame)
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

};


class Food final
{
public:
  explicit Food()
  {
    textureApple.loadFromFile("./Textures.1.0/Apple.png");                                                // Путь к текстурам яблока
    food.setTexture(textureApple);                                                                        // Присвоение текстуры спрайту
    sSizeFood = 26;                                                                                       // Размер спрайта еды
    food.setTextureRect(IntRect(0, 0, sSizeFood, sSizeFood));                                             // Область текстуры для отрисовки
    fHalfFood = sSizeFood / 2;                                                                            // Размер спрайта от края до центра
    food.setOrigin(fHalfFood, fHalfFood);                                                                 // Центр спрайта, от верхнего лев. угла

    srand(time(0));
    fPositionFoodX = rand() % ((int)fWidthField-1  - sSizeFood);                                          // Координаты еды по ширине в начале игры
    if (fPositionFoodX < sSizeFood) fPositionFoodX += sSizeFood;
    fPositionFoodY = rand() % ((int)fHeigthField-1 - sSizeFood);                                          // Координаты еды по высоте в начале игры
    if (fPositionFoodY < sSizeFood) fPositionFoodY += sSizeFood;
    food.setPosition(fPositionFoodX, fPositionFoodY);                                                     // Позиция еды в начале игры
    cout << "Food created" << endl;
  }

  Texture textureApple;
  Sprite food;

  short sSizeFood;
  short fHalfFood;
  float fPositionFoodX;
  float fPositionFoodY;


  void eatFood(RenderWindow &window, SnakeHead &head)
  { // Диапазон съедания еды
    if ((head.fSnakeHeadX + head.sHalfSH >= fPositionFoodX - fHalfFood && head.fSnakeHeadX - head.sHalfSH <= fPositionFoodX + fHalfFood) &&
	(head.fSnakeHeadY + head.sHalfSH >= fPositionFoodY - fHalfFood && head.fSnakeHeadY - head.sHalfSH <= fPositionFoodY + fHalfFood))
      {
	// Пересчёт координат еды
	
	fPositionFoodX = rand() % ((int)fWidthField-1  - sSizeFood);
	if (fPositionFoodX < sSizeFood) fPositionFoodX += sSizeFood;
	fPositionFoodY = rand() % ((int)fHeigthField-1 - sSizeFood);
	if (fPositionFoodY < sSizeFood) fPositionFoodY += sSizeFood;
	food.setPosition(fPositionFoodX, fPositionFoodY);
	
	++SnakeTail::snCount;
	cout << "Tail objects in the game: " << SnakeTail::snCount << endl;
      }

    window.draw(food); // Отрисовка еды на экране
  }
  
};


void control(Event &event, RenderWindow &window, SnakeHead &head) // Функция управления игрой
{
  while (window.pollEvent(event))
    {

      if (event.type == Event::Closed)
	{
	  window.close();
	}


      if (event.type == Event::KeyPressed)
	{
	  if ((Keyboard::isKeyPressed(Keyboard::Up)    || Keyboard::isKeyPressed(Keyboard::W)) && head.sDirection != DOWN)
	    {
	      head.sDirection = UP;
	    }

	  if ((Keyboard::isKeyPressed(Keyboard::Down)  || Keyboard::isKeyPressed(Keyboard::S)) && head.sDirection != UP)
	    {
	      head.sDirection = DOWN;
	    }

	  if ((Keyboard::isKeyPressed(Keyboard::Left)  || Keyboard::isKeyPressed(Keyboard::A)) && head.sDirection != RIGHT)
	    {
	      head.sDirection = LEFT;
	    }
	  
	  if ((Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) && head.sDirection != LEFT)
	    {
	      head.sDirection = RIGHT;
	    } 
	}
      
    }

};


int main()
{  
  // Объекты игры

  TimeGame timeGame;
  Background background;
  SnakeOBJ snake;
  Food someFood;
  Event event;
  
  RenderWindow window(VideoMode(fWidthField, fHeigthField), "Snake: Eat or Die! V.1.0");

  while (window.isOpen())
    {
      // Работа игры
      
      control(event, window, snake.head);
      timeGame.averageTime();
      snake.motionAndViewTail(window, timeGame);
      someFood.eatFood(window, snake.head);
      
      // Отрисовка
      
      window.display();
      window.draw(background.backgroundArea);  
    }

  return 0;  
}
