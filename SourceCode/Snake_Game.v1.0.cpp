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


class TextGame final // Текст в игре
{
public:
  TextGame()
  {
    gameFont.loadFromFile("./PeaceSans/PeaceSansWebfont.ttf");
    text.setFont(gameFont);
  }

  Font gameFont;
  Text text;
};


class Background // Фон
{
public:
  Background(const string &path) : pathOfTexture(path)
  {
    textureBackground.loadFromFile(pathOfTexture); // Путь к текстурам фона
    backgroundArea.setTexture(textureBackground);  // Присвоение текстуры спрайту
  }

  Background(const string &path, const short &sizeX, const short &sizeY) : pathOfTexture(path), sSizeBackgroundX(sizeX), sSizeBackgroundY(sizeY)
  {
    textureBackground.loadFromFile(pathOfTexture); // Путь к текстурам фона
    backgroundArea.setTexture(textureBackground);  // Присвоение текстуры спрайту
    sHalfSizeBackgroundX = sSizeBackgroundX / 2;
    sHalfSizeBackgroundY = sSizeBackgroundY / 2;
    backgroundArea.setOrigin(sHalfSizeBackgroundX, sHalfSizeBackgroundY);
  }
  
  Texture textureBackground;
  Sprite backgroundArea; 
  string pathOfTexture;
  short sSizeBackgroundX;
  short sSizeBackgroundY;
  short sHalfSizeBackgroundX;
  short sHalfSizeBackgroundY;
  
  void drawBackground(RenderWindow &window)
  {
    window.draw(backgroundArea);
  }
  
};


class BackgroundLevel : public Background // Фон уровня
{
public:
  BackgroundLevel(const string &pathOfTexture) : Background{pathOfTexture}
  {
    textScore.text.setCharacterSize(25);
    textScore.text.setString(szStringText + szStringNumber);
    textScore.text.setPosition(260, 0);

    textInfo.text.setCharacterSize(15);
    textInfo.text.setString("Press  Space  for  pause");
    textInfo.text.setPosition(0, 7);

    rectangle.setSize(Vector2f(fWidthWindow, snSizeRectangle));
    rectangle.setFillColor(Color::Black);
  }
  
  TextGame textScore;
  TextGame textInfo;
  RectangleShape rectangle;
  short snSizeRectangle = 30;

  int num = 0; 
  string szStringText = "Score: ", szStringNumber = "00000";
  
  
  void drawBackground(RenderWindow &window)
  {
    window.draw(backgroundArea);
    window.draw(rectangle);
    window.draw(textScore.text);
    window.draw(textInfo.text);
  }
  
  
  void increasePoints()
  {
    num += 10;
    szStringNumber = to_string(num);

    if (num >= 10000) textScore.text.setString(szStringText + szStringNumber);
    else if (num >= 1000) textScore.text.setString(szStringText + "0" + szStringNumber);
    else if (num >= 100) textScore.text.setString(szStringText + "00" + szStringNumber);
    else textScore.text.setString(szStringText + "000" + szStringNumber);
  }
};


class Menu final
{
  //protected:
public:

  Menu(SnakeHead &head,
       const string &pathTextureBackgroundGame, const string &pathTextureBackgroundStartMenu,
       const string &pathTextureBackgroundPause, const string &pathTextureLosingTheGame) :
    backgroundGame(pathTextureBackgroundGame), backgroundStartMenu(pathTextureBackgroundStartMenu, 535, 315),
    backgroundPause(pathTextureBackgroundPause, 535, 315), backgroundLossTheGame(pathTextureLosingTheGame, 535, 315)
  {
    head.nHeadControlLosingTheGame = head.WithMenu;
    backgroundStartMenu.backgroundArea.setPosition(fWidthField / 2, fHeigthField / 2);
    backgroundPause.backgroundArea.setPosition(fWidthField / 2, fHeigthField / 2);
    backgroundLossTheGame.backgroundArea.setPosition(fWidthField / 2, fHeigthField / 2);
  }
  
  enum MenuMode {ContinueGame, StartMenu, Pause, LosingTheGame};
  int nMenuMode = StartMenu; // Выбор режима меню

  BackgroundLevel backgroundGame;
  Background backgroundStartMenu;
  Background backgroundPause;
  Background backgroundLossTheGame;
  
public:
  void work(Event &event, RenderWindow &window, TimeGame &timeGame, SnakeHead &head)
  {
    switch(nMenuMode)
      {

      case ContinueGame:
	{
	  if (head.nHeadControlLosingTheGame == head.GameOver) nMenuMode = LosingTheGame;
	  controlContinue(event, window, head);
	  backgroundGame.drawBackground(window);
	} break;
	
      case StartMenu:
	{
	  cout << "Start" << endl;
	  backgroundStartMenu.drawBackground(window);
	  window.display();
	  timeGame.skipCounting();
	  while (nMenuMode == StartMenu)
	    {
	      controlStartMenu(event, window);
	    }
	} break;

      case Pause:
	{
	  cout << "Pause" << endl;
	  backgroundPause.drawBackground(window);
	  window.display();
	  timeGame.skipCounting();
	  while (nMenuMode == Pause)
	    {
	      controlPause(event, window);
	    }
	} break;

      case LosingTheGame:
	{
	  cout << "Game Over" << endl;
	  backgroundLossTheGame.drawBackground(window);
	  window.display();
	  timeGame.skipCounting();
	  while (nMenuMode == LosingTheGame)
	    {
	      controlLosingTheGame(event, window);
	    }
	} break;
		
      }
  }

  
  void closeWindow(Event &event, RenderWindow &window)
  {
    if (event.type == Event::Closed)
      {
	window.close();
	nMenuMode = ContinueGame;
      }
  }

  
  void controlContinue(Event &event, RenderWindow &window, SnakeHead &head) // Функция управления игрой
  {
    while (window.pollEvent(event))
      {
	closeWindow(event, window);
	head.controlHead(event);
	
	if (event.type == Event::KeyPressed)
	  {   
	    if (Keyboard::isKeyPressed(Keyboard::Space))
	      {
		nMenuMode = Pause;
	      }
	  }
	
      }
    
  }

  
  void controlStartMenu(Event &event, RenderWindow &window)
  {
    while (window.pollEvent(event))
      {
	closeWindow(event, window);

	if (event.type == Event::KeyPressed)
	  {
	    
	    if (Keyboard::isKeyPressed(Keyboard::Space))
	      {
		nMenuMode = ContinueGame;
	      }

	    if (Keyboard::isKeyPressed(Keyboard::Escape))
	      {
		window.close();
		nMenuMode = ContinueGame;
	      }
	  }
      }
  }

  
  void controlPause(Event &event, RenderWindow &window)
  {
    while (window.pollEvent(event))
      {
	closeWindow(event, window);

	if (event.type == Event::KeyPressed)
	  {
	    
	    if (Keyboard::isKeyPressed(Keyboard::Space))
	      {
		cout << "Play" << endl;
		nMenuMode = ContinueGame;
	      }

	    if (Keyboard::isKeyPressed(Keyboard::Escape))
	      {
		window.close();
		nMenuMode = ContinueGame;
	      }
	    
	  }
      }
  }

  
  void controlLosingTheGame(Event &event, RenderWindow &window)
  {
    while(window.pollEvent(event))
      {
	closeWindow(event, window);

	if (event.type == Event::KeyPressed)
	  {

	    if (Keyboard::isKeyPressed(Keyboard::Space))
	      {
		nMenuMode = ContinueGame;
	      }

	    if (Keyboard::isKeyPressed(Keyboard::Escape))
	      {
		window.close();
		nMenuMode = ContinueGame;
	      }
	    
	  }
      }
  }
  
};


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
  explicit Food(BackgroundLevel &background)
  {
    textureApple.loadFromFile("./Textures.1.0/Apple.png");                                                // Путь к текстурам яблока
    food.setTexture(textureApple);                                                                        // Присвоение текстуры спрайту
    sSizeFood = 26;                                                                                       // Размер спрайта еды
    food.setTextureRect(IntRect(0, 0, sSizeFood, sSizeFood));                                             // Область текстуры для отрисовки
    fHalfFood = sSizeFood / 2;                                                                            // Размер спрайта от края до центра
    food.setOrigin(fHalfFood, fHalfFood);                                                                 // Центр спрайта, от верхнего лев. угла

    srand(time(0));
    fPositionFoodX = rand() % ((int)fWidthField - sSizeFood);                                          // Координаты еды по ширине в начале игры
    if (fPositionFoodX < sSizeFood) fPositionFoodX += sSizeFood;
    fPositionFoodY = rand() % ((int)fHeigthField - sSizeFood + background.snSizeRectangle);            // Координаты еды по высоте в начале игры
    if (fPositionFoodY < sSizeFood + background.snSizeRectangle) fPositionFoodY += sSizeFood + background.snSizeRectangle;
    food.setPosition(fPositionFoodX, fPositionFoodY);                                                     // Позиция еды в начале игры
    //cout << "Food created" << endl;
  }

  Texture textureApple;
  Sprite food;

  short sSizeFood;
  short fHalfFood;
  float fPositionFoodX;
  float fPositionFoodY;


  void eatFood(RenderWindow &window, SnakeHead &head, BackgroundLevel &background)
  { // Диапазон съедания еды
    if ((head.fSnakeHeadX + head.sHalfSH >= fPositionFoodX - fHalfFood && head.fSnakeHeadX - head.sHalfSH <= fPositionFoodX + fHalfFood) &&
	(head.fSnakeHeadY + head.sHalfSH >= fPositionFoodY - fHalfFood && head.fSnakeHeadY - head.sHalfSH <= fPositionFoodY + fHalfFood))
      {
	// Пересчёт координат еды
	
	fPositionFoodX = rand() % ((int)fWidthField  - sSizeFood);
	if (fPositionFoodX < sSizeFood) fPositionFoodX += sSizeFood;
	fPositionFoodY = rand() % ((int)fHeigthField - sSizeFood + background.snSizeRectangle);
	if (fPositionFoodY < sSizeFood + background.snSizeRectangle) fPositionFoodY += sSizeFood + background.snSizeRectangle;
	food.setPosition(fPositionFoodX, fPositionFoodY);
	
	++SnakeTail::snCount;
	//cout << "Tail objects in the game: " << SnakeTail::snCount << endl;

	background.increasePoints();
      }

    window.draw(food); // Отрисовка еды на экране
  }
  
};


int main()
{  
  // Объекты игры

  TimeGame timeGame;
  SnakeOBJ snake;
  Menu menu(snake.head, "./Textures.1.0/Wall.png", "./Textures.1.0/MenuWindow.png", "./Textures.1.0/MenuWindow.png", "./Textures.1.0/MenuWindow.png");
  Food someFood(menu.backgroundGame);
  Event event;
  
  RenderWindow window(VideoMode(fWidthWindow, fHeigthWindow), "Snake: Eat or Die! V.1.0");

  while (window.isOpen())
    {
      // Работа игры

      menu.work(event, window, timeGame, snake.head);
      timeGame.averageTime();
      snake.motionAndViewTail(window, timeGame);
      someFood.eatFood(window, snake.head, menu.backgroundGame);

      // Отрисовка
      
      window.display();
    }

  return 0;  
}
