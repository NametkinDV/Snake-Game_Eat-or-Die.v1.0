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
	snakeTail.setPosition(head.fSnakeHeadX, head.fSnakeHeadY + head.sHalfSH + sHalfST);                // Позиция хвоста в начале игры
	snakeTail.setTexture(firstEndTail);
	++SnakeTail::snCount;
	++SnakeTail::snPrevCount;
      } break;

    case 2:
      {
	snakeTail.setPosition(head.fSnakeHeadX, head.fSnakeHeadY + head.sHalfSH + sSizeTail + sHalfST);
      } break;
    }
}


short SnakeTail::snCount = 1;
short SnakeTail::snPrevCount = 1;
int SnakeTail::nDelay = 0;
int SnakeTail::nHeadDelayDiffer = 0;
int SnakeTail::nMaxDelay = 1500;
bool SnakeTail::bStartWithTime = false;


void SnakeTail::resetStaticDataTail() // Функция сброса статических параметров хвоста змейки до начальных
{
  SnakeTail::snCount = 2;
  SnakeTail::snPrevCount = 2;
  SnakeTail::nDelay = 0;
  SnakeTail::nMaxDelay = 1500;
}
