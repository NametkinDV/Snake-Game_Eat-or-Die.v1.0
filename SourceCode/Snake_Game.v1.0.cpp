// Версия игры Snake: Eat or Die v1.0.
// Игра создана на базе библиотеки SFML.
// Файл содержит 4 класса: Игровое время(TimeGame), Меню(Menu), Змейка(SnakeOBJ), Еда(Food)
// и заголовочный файл CommonSettings с общеигровыми настройками.
// Так же подключаются библиотеки: iostream и SFML/Graphics.
// Автор: Намёткин Дмитрий.

#include <iostream>
#include <SFML/Graphics.hpp>

#include "CommonSettings.h"
#include "TimeGame.h"
#include "SnakeOBJ.h"
#include "Menu.h"
#include "Food.h"

using namespace std;
using namespace sf;


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

      menu.work(event, window, timeGame, snake);
      timeGame.averageTime();
      snake.motionAndViewTail(window, timeGame);
      someFood.eatFood(window, snake.head, menu.backgroundGame);

      // Отрисовка
      
      window.display();
    }

  return 0;  
}
