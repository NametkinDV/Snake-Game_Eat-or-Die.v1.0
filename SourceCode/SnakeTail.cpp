#include "SnakeTail.h"
#include "SnakeHead.h"
#include "CommonSettings.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;


SnakeTail::SnakeTail(SnakeHead &head)
{  
  bodyTail.loadFromFile("./Textures.1.0/Body.png");                                                        // Путь к текстурам туловища
  endTail.loadFromFile("./Textures.1.0/TexturesTail.png");                                                 // Путь к текстурам хвоста
  snakeTail.setTexture(endTail);
  
  sSizeTail = 60;                                                                                          // Размер спрайта хвоста и туловища
  snakeTail.setTextureRect(IntRect(snDirectionTail[UP][0], snDirectionTail[UP][1], sSizeTail, sSizeTail)); // Область текстуры для отрисовки
  sHalfST = sSizeTail / 2;                                                                                 // Размер спрайта от края до центра
  snakeTail.setOrigin(sHalfST, sHalfST);                                                                   // Центр спрайта, от верхнего лев. угла
  
  if (snCount == 1) // Если хвост в начале игры                                                                                        
    {
      fSnakeTailX = head.fSnakeHeadX;                                                                      // Координаты хвоста по ширине в начале игры
      fSnakeTailY = head.fSnakeHeadY + head.sHalfSH + sHalfST;                                             // Координаты хвоста по высоте в начале игры
      snakeTail.setPosition(fSnakeTailX, fSnakeTailY);                                                     // Позиция хвоста в начале игры
    }
}


short SnakeTail::snCount = 1;
short SnakeTail::snPrevCount = 1;
int SnakeTail::delay = 0;
int SnakeTail::nSizeTail = 1500;
bool SnakeTail::bStartWithTime = false;
