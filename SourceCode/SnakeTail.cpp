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
  firstEndTail.loadFromFile("./Textures.1.0/TexturesTail.png");                                            // Путь к текстурам хвоста
  secondEndTail.loadFromFile("./Textures.1.0/TexturesEndTail.png");
  snakeTail.setTexture(secondEndTail);
  
  sSizeTail = 26;                                                                                          // Размер спрайта хвоста и туловища
  snakeTail.setTextureRect(IntRect(snDirectionTail[UP][0], snDirectionTail[UP][1], sSizeTail, sSizeTail)); // Область текстуры для отрисовки
  sHalfST = sSizeTail / 2;                                                                                 // Размер спрайта от края до центра
  snakeTail.setOrigin(sHalfST, sHalfST);                                                                   // Центр спрайта, от верхнего лев. угла
  
  switch (snCount) // Если хвост в начале игры                                                                                        
    {
    case 1:
      {
	fSnakeTailX = head.fSnakeHeadX;                                                                      // Координаты хвоста по ширине в начале игры
	fSnakeTailY = head.fSnakeHeadY + head.sHalfSH + sHalfST;                                             // Координаты хвоста по высоте в начале игры
	snakeTail.setPosition(fSnakeTailX, fSnakeTailY);                                                     // Позиция хвоста в начале игры
	snakeTail.setTexture(firstEndTail);
	++SnakeTail::snCount;
	++SnakeTail::snPrevCount;
      } break;

    case 2:
      {
	fSnakeTailX = head.fSnakeHeadX;
	fSnakeTailY = head.fSnakeHeadY + head.sHalfSH + sSizeTail + sHalfST;
	snakeTail.setPosition(fSnakeTailX, fSnakeTailY);
      } break;
    }
}


short SnakeTail::snCount = 1;
short SnakeTail::snPrevCount = 1;
int SnakeTail::nDelay = 0;
int SnakeTail::nHeadDelayDiffer = 0;
int SnakeTail::nSizeTail = 1500;
bool SnakeTail::bStartWithTime = false;
