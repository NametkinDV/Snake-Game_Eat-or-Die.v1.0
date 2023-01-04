#ifndef TextGame_h
#define TextGame_h

#include <SFML/Graphics.hpp>

using namespace sf;

class TextGame final // Текст в игре
{
public:
  TextGame();

  Font gameFont;
  Text text;
};


#endif
