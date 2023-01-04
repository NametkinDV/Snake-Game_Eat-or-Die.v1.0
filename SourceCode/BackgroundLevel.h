#ifndef BackgroundLevel_h
#define BackgroundLevel_h

#include "CommonSettings.h"
#include "Background.h"
#include "TextGame.h"


class BackgroundLevel : public Background // Фон уровня
{
public:
  BackgroundLevel(const string &pathOfTexture);
  
  TextGame textScore;
  TextGame textInfo;
  RectangleShape rectangle;
  short snSizeRectangle = 30;

  int num = 0; 
  string szStringText = "Score: ", szStringNumber = "00000";
  
  
  void drawBackground(RenderWindow &window); // Отрисовка фона в окне
  void increasePoints(); // Добавление очков счёту игрока
};


#endif
