#include "TextGame.h"


TextGame::TextGame()
{
  gameFont.loadFromFile("./PeaceSans/PeaceSansWebfont.ttf");
  text.setFont(gameFont);
}
