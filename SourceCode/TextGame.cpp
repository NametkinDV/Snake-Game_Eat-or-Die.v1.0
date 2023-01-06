#include "TextGame.h"


TextGame::TextGame()
{
  gameFont.loadFromFile("./PeaceSans/PeaceSansWebfont.ttf");
  text.setFont(gameFont);
}


void TextGame::setSizeTextPosition(const int &size, const string &someText, const int &X, const int &Y) // Установка размера, текста и позиции
{
  text.setCharacterSize(size);
  text.setString(someText);
  text.setPosition(X, Y);
}
