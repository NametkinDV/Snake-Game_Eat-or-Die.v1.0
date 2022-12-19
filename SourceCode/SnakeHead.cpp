#include "SnakeHead.h"
#include "CommonSettings.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;


SnakeHead::SnakeHead()
{
  textureHead.loadFromFile("./Textures.1.0/TexturesSnake.png");                                         // Путь к текстурам головы
  snakeHead.setTexture(textureHead);                                                                    // Присвоение текстуры спрайту
  sSizeHead = 60;                                                                                       // Размер спрайта головы
  snakeHead.setTextureRect(IntRect(sDirectionHead[UP][0],sDirectionHead[UP][1], sSizeHead, sSizeHead)); // Область текстуры для отрисовки
  sHalfSH = sSizeHead / 2;                                                                              // Размер спрайта от края до центра
  snakeHead.setOrigin(sHalfSH, sHalfSH);                                                                // Центр спрайта, от верхнего лев. угла
  
  fSnakeHeadX = (fWidthField / 2);                                                                      // Начальные координаты головы по ширине
  fSnakeHeadY = (fHeigthField / 2);                                                                     // Начальные координаты головы по высоте
  snakeHead.setPosition(fSnakeHeadX, fSnakeHeadY);                                                      // Установка начальной позиция головы
  fSpeed = 0.04F;                                                                                       // Скорость передвижения
  sDirection = -1;                                                                                      // Направление головы
  //cout << "Head created" << endl;
}

  
void SnakeHead::motionAndViewHead (RenderWindow &window, const double &time) // Функция движения головы
{
  // Функция проигрыша при встрече со стеной
  
  if(fSnakeHeadX <= (fWidthWindow - fWidthField + sHalfSH) || fSnakeHeadX >= (fWidthField - sHalfSH) ||
     fSnakeHeadY <= (fHeigthWindow - fHeigthField + sHalfSH) || fSnakeHeadY >= (fHeigthField - sHalfSH + 30))
    {
      window.close();
    }
  
  /* // Функция переноса змейки на противоположную сторону
     
     if      (fSnakeHeadX <= -fHalfSH)    {fSnakeHeadX = fWidthField + fHalfSH;} 
     else if (fSnakeHeadX >= fWidthField + fHalfSH) {fSnakeHeadX = -fHalfSH;}
     if      (fSnakeHeadY <= -fHalfSH)    {fSnakeHeadY = fHeigthField + fHalfSH;}
     else if (fSnakeHeadY >= fHeigthField + fHalfSH){fSnakeHeadY = -fHalfSH;}
  */
  
  switch (sDirection)
    {
      
    case UP: // Направление вверх
      {
	fSnakeHeadY -= fSpeed * time; 
	snakeHead.setPosition(fSnakeHeadX, fSnakeHeadY);
	snakeHead.setTextureRect(IntRect(sDirectionHead[UP][0],sDirectionHead[UP][1], sSizeHead, sSizeHead));
      };
      break;
      
    case DOWN: // Направление вниз
      {
	fSnakeHeadY += fSpeed * time;
	snakeHead.setPosition(fSnakeHeadX, fSnakeHeadY);
	snakeHead.setTextureRect(IntRect(sDirectionHead[DOWN][0], sDirectionHead[DOWN][1], sSizeHead, sSizeHead));
      };
      break;
      
    case LEFT: // Направление влево
      {
	fSnakeHeadX -= fSpeed * time;
	snakeHead.setPosition(fSnakeHeadX, fSnakeHeadY);
	snakeHead.setTextureRect(IntRect(sDirectionHead[LEFT][0],sDirectionHead[LEFT][1], sSizeHead, sSizeHead));
      };
      break;
      
    case RIGHT: // Направление вправо
      {
	fSnakeHeadX += fSpeed * time;
	snakeHead.setPosition(fSnakeHeadX, fSnakeHeadY);
	snakeHead.setTextureRect(IntRect(sDirectionHead[RIGHT][0],sDirectionHead[RIGHT][1], sSizeHead, sSizeHead));
      }
      
    }

  window.draw(snakeHead); // Отрисовка головы на экране
}
