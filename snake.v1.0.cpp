// Версия игры Snake: Eat or Die v1.0
// Игра создана на базе библиотеки SFML
// Содержит 3 класса: Голова, Хвост\Туловище, Еда
// и функцию управления игрой
// Автор: Намёткин Дмитрий

#include <iostream>
#include <cstdlib>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;
using namespace sf;

const float fWidthField = 700.0F;  // Размер игрового поля по ширине
const float fHeigthField = 500.0F; // Размер игрового поля по высоте

enum direction {UP, DOWN, LEFT, RIGHT};


class TimeGame final // Работа со временем
{
private:
  double timeStartGame;
  double microSec;

public:

  TimeGame()
  {
    timeStartGame = chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now().time_since_epoch()).count(); // Фиксация времени при запуске
  }
  
  double timeHasPassed()                                                                                 // Подсчёт времени (в миллисекундах) / Ритм игры
  {
    microSec = chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now().time_since_epoch()).count(); //Получение времени(микросекунды)
    microSec -= timeStartGame;

    return microSec;
  }

  void resetTime()
  {
    timeStartGame = chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now().time_since_epoch()).count();
  }
  
};


class Background // Фон игры
{
public:
  Background()
  {
    textureBackground.loadFromFile("./Textures.1.0/Wall.png");                                            // Путь к текстурам фона
    backgroundArea.setTexture(textureBackground);                                                         // Присвоение текстуры спрайту
  }
  
  Texture textureBackground;
  Sprite backgroundArea;
  
};


class SnakeHead final // Голова змейки
{
public:
 explicit SnakeHead()
  {
    textureHead.loadFromFile("./Textures.1.0/TexturesSnake.png");                                         // Путь к текстурам головы
    snakeHead.setTexture(textureHead);                                                                    // Присвоение текстуры спрайту
    sSizeHead = 60;                                                                                       // Размер спрайта головы
    snakeHead.setTextureRect(IntRect(sDirectionHead[UP][0],sDirectionHead[UP][1], sSizeHead, sSizeHead)); // Область текстуры для отрисовки
    sHalfSH = sSizeHead / 2;                                                                              // Размер спрайта от края до центра
    snakeHead.setOrigin(sHalfSH, sHalfSH);                                                                // Центр спрайта, от верхнего лев. угла

    fSnakeHeadX = (fWidthField / 2);                                                                      // Координаты головы по ширине
    fSnakeHeadY = (fHeigthField / 2);                                                                     // Координаты головы по высоте
    snakeHead.setPosition(fSnakeHeadX, fSnakeHeadY);                                                      // Начальная позиция головы
    fSpeed = 0.20F;                                                                                       // Скорость передвижения
    sDirection = -1;                                                                                      // Направление головы
    cout << "Создание головы" << endl;
  }

  
  Texture textureHead;
  Sprite snakeHead;

  short sSizeHead;
  short sHalfSH;
  float fSnakeHeadX;
  float fSnakeHeadY;
  float fSpeed;
  short sDirection;
  short sDirectionHead[4][2] = // Координаты отрисовки текстур головы
    {
     {0, 0},   // Вверх
     {0, 60},  // Вниз
     {60, 0},  // Влево
     {60, 60}  // Вправо
    };
  
  
  void motionAndViewHead (RenderWindow &window, double &time) // Функция движения головы
  {
    // Функция проигрыша при встрече со стеной
    
    if(fSnakeHeadX <= sHalfSH || fSnakeHeadX >= fWidthField - sHalfSH || fSnakeHeadY <= sHalfSH || fSnakeHeadY >= fHeigthField - sHalfSH)
      {
	window.close();
      }
    
    /* // Функция переноса змейки на противоположную сторону

    if      (fSnakeHeadX <= -fHalfSH)    {fSnakeHeadX = fWidthField + fHalfSH;} 
    else if (fSnakeHeadX >= fWidthField + fHalfSH) {fSnakeHeadX = -fHalfSH;}
    if      (fSnakeHeadY <= -fHalfSH)    {fSnakeHeadY = fHeigthField + fHalfSH;}
    else if (fSnakeHeadY >= fHeigthField + fHalfSH){fSnakeHeadY = -fHalfSH;}
    */

    switch (sDirection)
      {
	
      case UP: // Направление вверх
	{
	  fSnakeHeadY -= fSpeed * time; 
	  snakeHead.setPosition(fSnakeHeadX, fSnakeHeadY);
	  snakeHead.setTextureRect(IntRect(sDirectionHead[UP][0],sDirectionHead[UP][1], sSizeHead, sSizeHead));
	};
	break;
	
      case DOWN: // Направление вниз
	{
	  fSnakeHeadY += fSpeed * time;
	  snakeHead.setPosition(fSnakeHeadX, fSnakeHeadY);
	  snakeHead.setTextureRect(IntRect(sDirectionHead[DOWN][0], sDirectionHead[DOWN][1], sSizeHead, sSizeHead));
	};
	break;
	
      case LEFT: // Направление влево
	{
	  fSnakeHeadX -= fSpeed * time;
	  snakeHead.setPosition(fSnakeHeadX, fSnakeHeadY);
	  snakeHead.setTextureRect(IntRect(sDirectionHead[LEFT][0],sDirectionHead[LEFT][1], sSizeHead, sSizeHead));
	};
	break;
	
      case RIGHT: // Направление вправо
	{
	  fSnakeHeadX += fSpeed * time;
	  snakeHead.setPosition(fSnakeHeadX, fSnakeHeadY);
	  snakeHead.setTextureRect(IntRect(sDirectionHead[RIGHT][0],sDirectionHead[RIGHT][1], sSizeHead, sSizeHead));
	}
	
      }
 
  }
  
};


class SnakeTail final
{
public:
  explicit SnakeTail(SnakeHead &head)
  {  
    bodyTail.loadFromFile("./Textures.1.0/Body.png");                                                        // Путь к текстурам туловища
    endTail.loadFromFile("./Textures.1.0/TexturesTail.png");                                                 // Путь к текстурам хвоста
    snakeTail.setTexture(endTail);
    
    sSizeTail = 60;                                                                                          // Размер спрайта хвоста и туловища
    snakeTail.setTextureRect(IntRect(snDirectionTail[UP][0], snDirectionTail[UP][1], sSizeTail, sSizeTail)); // Область текстуры для отрисовки
    sHalfST = sSizeTail / 2;                                                                                 // Размер спрайта от края до центра
    snakeTail.setOrigin(sHalfST, sHalfST);                                                                   // Центр спрайта, от верхнего лев. угла

    if (snCount == 1)                                                                                        
      {
	fSnakeTailX[0] = head.fSnakeHeadX;                                                                   // Координаты хвоста по ширине
	fSnakeTailY[0] = head.fSnakeHeadY + head.sHalfSH + sHalfST;                                          // Координаты хвоста по высоте 
	snakeTail.setPosition(fSnakeTailX[0], fSnakeTailY[0]);                                               // Начальная позиция хвоста
      }
  }
  
  static short snCount;
  static short snPrevCount;
  static short delay;
  static double dOldTime;
  
  Texture endTail;
  Texture bodyTail;
  Sprite snakeTail;

  short sSizeTail;
  short sHalfST;
  float fSnakeTailX[1300];
  float fSnakeTailY[1300];

  float fOldPositionTailX;
  float fOldPositionTailY;
  float fNewPositionTailX;
  float fNewPositionTailY;

  short snDirection[1300];
  short snNewDirection;
  short snOldDirection;

  short snDirectionTail[4][2] = // Координаты отрисовки текстур хвоста и туловища
    {
     {0, 0},   // Вверх
     {0, 60},  // Вниз
     {60, 0},  // Влево
     {60, 60}  // Вправо
    };

};

void motionAndViewTail (SnakeHead &head,vector<SnakeTail*> &tail, double &time)
{
  if (head.sDirection != -1)
    {
      for(short i = 0; i <= SnakeTail::snCount; ++i)
	{
	  tail[0]->fNewPositionTailX = head.fSnakeHeadX;                 // Передача хвосту координат змейки по ширине
	  tail[0]->fNewPositionTailY = head.fSnakeHeadY;                 // Передача хвосту координат змейки по высоте
	  tail[0]->snNewDirection = head.sDirection;
	  
	  if(SnakeTail::snCount != SnakeTail::snPrevCount)               // Вычисление задержки хвоста за головой
	    {
	      SnakeTail::snPrevCount = SnakeTail::snCount;
	      if (time > SnakeTail::dOldTime)
		{
		  // SnakeTail::delay = (60 / 0.20) / time;
		  SnakeTail::dOldTime = time;

		  cout << "++++++++++++" << endl << "Смещение: " << SnakeTail::delay << endl
		       << "Время: " << time << endl;
		}
	      else{}
	      double dTempTime = 0;
	      dTempTime = SnakeTail::dOldTime / SnakeTail::delay ;
	      SnakeTail::delay = (head.sSizeHead / head.fSpeed) / (SnakeTail::dOldTime + dTempTime);

	      cout << "___________" << endl
		   << "Смещение: " << SnakeTail::delay << endl
		   << "Время: " << time << endl
		   << "Прошлое время: " << SnakeTail::dOldTime << endl
		   << "Получено время: " << SnakeTail::dOldTime + dTempTime << endl
		   << "Время на ячейку: " << SnakeTail::dOldTime / SnakeTail::delay << endl;

	      SnakeTail::dOldTime = SnakeTail::dOldTime + dTempTime;
	    }
	    
	  if (i < SnakeTail::snCount-1) // Замена текстур хвоста на туловище
	    tail[i]->snakeTail.setTexture(tail[i]->bodyTail);

	  for (short j = 1; j <= SnakeTail::delay; ++j) 
	    {
	      tail[i + 1]->fNewPositionTailX = tail[i]->fNewPositionTailX;         // Передача координат следующим ячейкам хвоста
	      tail[i + 1]->fNewPositionTailY = tail[i]->fNewPositionTailY;         // Передача координат следующим ячейкам хвоста
	      tail[i + 1]->snNewDirection = tail[i]->snNewDirection;
	     
	      
	      tail[i]->fOldPositionTailX = tail[i]->fSnakeTailX[j];
	      tail[i]->fOldPositionTailY = tail[i]->fSnakeTailY[j];
	      tail[i]->snOldDirection = tail[i]->snDirection[j];
	      
	      tail[i]->fSnakeTailX[j] = tail[i]->fNewPositionTailX;
	      tail[i]->fSnakeTailY[j] = tail[i]->fNewPositionTailY;
	      tail[i]->snDirection[j] = tail[i]->snNewDirection;
	      
	      tail[i]->fNewPositionTailX = tail[i]->fOldPositionTailX;
	      tail[i]->fNewPositionTailY = tail[i]->fOldPositionTailY;
	      tail[i]->snNewDirection = tail[i]->snOldDirection;
	      
	      tail[i]->snakeTail.setPosition(tail[i]->fSnakeTailX[j], tail[i]->fSnakeTailY[j]);
	      
	      
	      switch(tail[i]->snDirection[j])
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
    }
}

short SnakeTail::snCount = 1;
short SnakeTail::snPrevCount = SnakeTail::snCount;
short SnakeTail::delay = 1100;
double SnakeTail::dOldTime = 0;


class Food final
{
public:
  explicit Food()
  {
    textureApple.loadFromFile("./Textures.1.0/Apple.png");                                                // Путь к текстурам яблока
    food.setTexture(textureApple);                                                                        // Присвоение текстуры спрайту
    sSizeFood = 26;                                                                                       // Размер спрайта еды
    food.setTextureRect(IntRect(0, 0, sSizeFood, sSizeFood));                                             // Область текстуры для отрисовки
    fHalfFood = 13;                                                                                       // Размер спрайта от края до центра
    food.setOrigin(fHalfFood, fHalfFood);                                                                 // Центр спрайта, от верхнего лев. угла

    srand(time(0));
    fPositionFoodX = sSizeFood + rand() % (((int)fWidthField - sSizeFood)  - sSizeFood + 1);              // Координаты еды по ширине
    fPositionFoodY = sSizeFood + rand() % (((int)fHeigthField - sSizeFood) - sSizeFood + 1);              // Координаты еды по высоте
    food.setPosition(fPositionFoodX, fPositionFoodY);                                                     // Начальная позиция еды
    cout << "Создание еды" << endl;
  }

  Texture textureApple;
  Sprite food;

  short sSizeFood;
  short fHalfFood;
  float fPositionFoodX;
  float fPositionFoodY;


  void eatFood(SnakeHead &head)
    {
      if ((head.fSnakeHeadX + head.sHalfSH >= fPositionFoodX - fHalfFood && head.fSnakeHeadX - head.sHalfSH <= fPositionFoodX + fHalfFood) &&
	  (head.fSnakeHeadY + head.sHalfSH >= fPositionFoodY - fHalfFood && head.fSnakeHeadY - head.sHalfSH <= fPositionFoodY + fHalfFood))
	{
	  fPositionFoodX = rand() % ((int)fWidthField  - sSizeFood);
	  fPositionFoodY = rand() % ((int)fHeigthField - sSizeFood);
	  food.setPosition(fPositionFoodX, fPositionFoodY);

	  ++SnakeTail::snCount;
	  cout << "Объектов хвоста в игре: " << SnakeTail::snCount << endl;
	}
    }
  
};


void control(Event &event, RenderWindow &window, SnakeHead &head)                                        // Функция управления игрой
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
  setlocale(LC_ALL, "rus");
  
  // Объекты игры

  TimeGame timeGame;
  double time = 0;
  Background background;
  SnakeHead head;
  Food someFood;
  Event event;
  vector <SnakeTail*> tail;
  
  for(int i = 0; i < 100; ++i)
    {
      tail.push_back(new SnakeTail(head));
    }

  
  RenderWindow window(VideoMode(fWidthField, fHeigthField), "Snake: Eat or Die! V.1.0");
  
  while (window.isOpen())
    {
      // Игровое время

      time = timeGame.timeHasPassed();
      timeGame.resetTime();
      time /= 700;
      
      // Управление игрой
      
      control(event, window, head);
      head.motionAndViewHead(window, time);
      motionAndViewTail(head, tail, time);
      someFood.eatFood(head);
      
      // Отрисовка
      
      window.display();
      window.draw(background.backgroundArea);
      window.draw(someFood.food);
      window.draw(head.snakeHead);
      for (short i = 0; i < SnakeTail::snCount; ++i)
	{window.draw(tail[i]->snakeTail);}
    }
  
  // Освобождение выделенной памяти
  
  for(int i = 0; i < 100; ++i)
    {
      delete tail[i];
      tail[i] = nullptr;
    }
  
  tail.clear();
  
  return 0;  
}
