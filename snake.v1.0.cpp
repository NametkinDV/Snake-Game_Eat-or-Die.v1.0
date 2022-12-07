// Версия игры Snake: Eat or Die v1.0
// Игра создана на базе библиотеки SFML
// Содержит 4 класса: Время, Голова, Хвост\Туловище, Еда
// и функцию управления игрой
// Автор: Намёткин Дмитрий

#include <iostream>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;
using namespace sf;

const float fWidthField = 700.0F;  // Размер игрового поля по ширине
const float fHeigthField = 500.0F; // Размер игрового поля по высоте

enum direction {UP, DOWN, LEFT, RIGHT};
enum pos {X, Y, DIR};

int nCount = 0;
class TimeGame final // Работа со временем
{
private:
  double dTimeStartGame = 0;
  double dMicroSec = 0;
  double dSumTime = 0;
  
  bool bSwitchStart = false;
public:
  TimeGame()
  {
    dTimeStartGame = chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now().time_since_epoch()).count(); // Фиксация времени при запуске
  }
  
  double timeHasPassed()                                                                                 // Подсчёт времени (в миллисекундах) / Ритм игры
  {
    dMicroSec = chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now().time_since_epoch()).count(); //Получение времени(микросекунды)
    dMicroSec -= dTimeStartGame;

    return dMicroSec;
  }

  void resetTime()
  {
    dTimeStartGame = chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now().time_since_epoch()).count();
  }

  void middleTime(double &time)
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
    fSpeed = 0.04F;                                                                                       // Скорость передвижения
    sDirection = -1;                                                                                      // Направление головы
    cout << "Создание головы" << endl;
  }

  
  Texture textureHead;
  Sprite snakeHead;

  short sSizeHead;
  short sHalfSH;
  double fSnakeHeadX;
  double fSnakeHeadY;
  double fSpeed;
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
	fSnakeTailX = head.fSnakeHeadX;                                                                   // Координаты хвоста по ширине
	fSnakeTailY = head.fSnakeHeadY + head.sHalfSH + sHalfST;                                          // Координаты хвоста по высоте 
	snakeTail.setPosition(fSnakeTailX, fSnakeTailY);                                               // Начальная позиция хвоста
      }
  }
  
  static short snCount;
  static int delay;
  static int nSizeTail;
  
  Texture endTail;
  Texture bodyTail;
  Sprite snakeTail;

  short sSizeTail;
  short sHalfST;
  float fSnakeTailX;
  float fSnakeTailY;

  short snDirectionTail[4][2] = // Координаты отрисовки текстур хвоста и туловища
    {
     {0, 0},   // Вверх
     {0, 60},  // Вниз
     {60, 0},  // Влево
     {60, 60}  // Вправо
    };

};


bool bStart = false;
void motionAndViewTail (SnakeHead &head,vector<SnakeTail*> &tail, double &time, vector <vector<double>> &road)
{
    road[X].insert(road[X].begin(), head.fSnakeHeadX);
    road[Y].insert(road[Y].begin(), head.fSnakeHeadY);
    road[DIR].insert(road[DIR].begin(), head.sDirection);
    
    if (head.sDirection == -1 && nCount < 5 && bStart == false) { SnakeTail::delay = head.sSizeHead / head.fSpeed; } // До начала игры задержка хвоста без учёта времени
    else                                                                          // Задержка хвоста с учётом времени
      {
	bStart = true;
	
	SnakeTail::delay = (head.sSizeHead  / head.fSpeed) / time; // Вычисление задержки хвоста за головой
	
	cout << "Смещение: " << SnakeTail::delay << endl
	     << "Время: " << time << endl
	     << "Объектов хвоста в игре: " << SnakeTail::snCount << endl;	  
      }

    if (SnakeTail::delay > SnakeTail::nSizeTail) SnakeTail::nSizeTail = SnakeTail::delay;
    
    if ((int)road[X].size() > SnakeTail::nSizeTail * (SnakeTail::snCount+1)) road[X].pop_back();
    if ((int)road[Y].size() > SnakeTail::nSizeTail * (SnakeTail::snCount+1)) road[Y].pop_back();
    if ((int)road[DIR].size() > SnakeTail::nSizeTail * (SnakeTail::snCount+1)) road[DIR].pop_back();
    
    for(short i = 0; i <= SnakeTail::snCount; ++i)
      {
	if (i < SnakeTail::snCount-1) // Замена текстур хвоста на туловище
	  tail[i]->snakeTail.setTexture(tail[i]->bodyTail);

	if (head.sDirection != -1) tail[i]->snakeTail.setPosition(road[X][(i+1) * SnakeTail::delay], road[Y][(i+1) * SnakeTail::delay]);
	
	switch((int)road[DIR][(i+1) * SnakeTail::delay])
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


short SnakeTail::snCount = 1;
int SnakeTail::delay = 0;
int SnakeTail::nSizeTail = 1500;


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
  Background background;
  SnakeHead head;
  Food someFood;
  Event event;

  vector <vector<double>> road;
  vector <SnakeTail*> tail;
  double time = 0;

  vector<double> one;
  vector<double> two;
  vector<double> three;
  road.push_back(one);
  road.push_back(two);
  road.push_back(three);

  for(int i = 0; i < 100; ++i)
    {
      tail.push_back(new SnakeTail(head));
    }
  
  for(int i = 0; i < 3000; ++i)
    {
      road[X].push_back(0);
      road[Y].push_back(0);
      road[DIR].push_back(0);
    }
  
  RenderWindow window(VideoMode(fWidthField, fHeigthField), "Snake: Eat or Die! V.1.0");

  while (window.isOpen())
    {
      // Управление игрой
      
      control(event, window, head);
      timeGame.middleTime(time);
      head.motionAndViewHead(window, time);
      motionAndViewTail(head, tail, time, road);
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
