#ifndef TextGame_h
#define TextGame_h

#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

class TextGame final // Текст в игре
{
public:
  TextGame();

  Font gameFont;
  Text text;


  void setSizeTextPosition(const int &size, const string &text, const int &X, const int &Y); // Установка размера, текста и позиции
  
};

#endif
