#ifndef Menu_h
#define Menu_h

#include <iostream>
#include <SFML/Graphics.hpp>
#include "CommonSettings.h"
#include "TimeGame.h"
#include "SnakeHead.h"
#include "Background.h"
#include "BackgroundLevel.h"

using namespace std;
using namespace sf;

class Menu final
{
  //protected:
public:

  Menu(SnakeHead &head,
       const string &pathTextureBackgroundGame, const string &pathTextureBackgroundStartMenu,
       const string &pathTextureBackgroundPause, const string &pathTextureLosingTheGame);

  
  enum MenuMode {ContinueGame, StartMenu, Pause, LosingTheGame};
  int nMenuMode = StartMenu; // Выбор режима меню

  BackgroundLevel backgroundGame;
  Background backgroundStartMenu;
  Background backgroundPause;
  Background backgroundLossTheGame;

  
public:
  void work(Event &event, RenderWindow &window, TimeGame &timeGame, SnakeHead &head); // Включение работы меню
  void closeWindow(Event &event, RenderWindow &window);                               // Закрытие окна
  void controlContinue(Event &event, RenderWindow &window, SnakeHead &head);          // Управление во время течения игры
  void controlStartMenu(Event &event, RenderWindow &window);                          // Управление в начальном меню
  void controlPause(Event &event, RenderWindow &window);                              // Управление во время паузы
  void controlLosingTheGame(Event &event, RenderWindow &window);                      // Управление после проигрыша игры

};


#endif
