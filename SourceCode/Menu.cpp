#include "Menu.h"


Menu::Menu(SnakeHead &head,
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


void Menu::work(Event &event, RenderWindow &window, TimeGame &timeGame, SnakeOBJ &snake) // Включение работы меню
{
  switch(nMenuMode)
    {
      
    case ContinueGame:
      {
	if (snake.head.nHeadControlLosingTheGame == snake.head.GameOver) nMenuMode = LosingTheGame;
	controlContinue(event, window, snake.head);
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
	    controlLosingTheGame(event, window, snake);
	  }
      } break;
      
    }
}

  
void Menu::closeWindow(Event &event, RenderWindow &window) // Закрытие окна
{
  if (event.type == Event::Closed)
    {
      window.close();
      nMenuMode = ContinueGame;
    }
}


void Menu::controlContinue(Event &event, RenderWindow &window, SnakeHead &head) // Управление во время течения игры
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

  
void Menu::controlStartMenu(Event &event, RenderWindow &window) // Управление в начальном меню
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

  
void Menu::controlPause(Event &event, RenderWindow &window) // Управление во время паузы
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

  
void Menu::controlLosingTheGame(Event &event, RenderWindow &window, SnakeOBJ &snake) // Управление после проигрыша игры
{
  while(window.pollEvent(event))
    {
      closeWindow(event, window);
      
      if (event.type == Event::KeyPressed)
	{
	  
	  if (Keyboard::isKeyPressed(Keyboard::Space))
	    {
	      snake.head.resetHead();
	      snake.resetTail(snake.tail);
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
 
