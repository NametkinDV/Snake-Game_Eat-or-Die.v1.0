#include "BackgroundLevel.h"


BackgroundLevel::BackgroundLevel(const string &pathOfTexture) : Background{pathOfTexture}
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
  
  
void BackgroundLevel::drawBackground(RenderWindow &window) // Отрисовка фона в окне
{
  window.draw(backgroundArea);
  window.draw(rectangle);
  window.draw(textScore.text);
  window.draw(textInfo.text);
}


void BackgroundLevel::increasePoints() // Добавление очков счёту игрока
{
  num += 10;
  szStringNumber = to_string(num);
  
  if (num >= 10000) textScore.text.setString(szStringText + szStringNumber);
  else if (num >= 1000) textScore.text.setString(szStringText + "0" + szStringNumber);
  else if (num >= 100) textScore.text.setString(szStringText + "00" + szStringNumber);
  else textScore.text.setString(szStringText + "000" + szStringNumber);
}
