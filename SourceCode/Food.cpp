#include "Food.h"


Food::Food(BackgroundLevel &background)
{
  textureApple.loadFromFile("./Textures.1.0/Apple.png");                                                // Путь к текстурам яблока
  food.setTexture(textureApple);                                                                        // Присвоение текстуры спрайту
  sSizeFood = 26;                                                                                       // Размер спрайта еды
  food.setTextureRect(IntRect(0, 0, sSizeFood, sSizeFood));                                             // Область текстуры для отрисовки
  fHalfFood = sSizeFood / 2;                                                                            // Размер спрайта от края до центра
  food.setOrigin(fHalfFood, fHalfFood);                                                                 // Центр спрайта, от верхнего лев. угла
  
  srand(time(0));
  fPositionFoodX = rand() % ((int)fWidthField - sSizeFood);                                          // Координаты еды по ширине в начале игры
  if (fPositionFoodX < sSizeFood) fPositionFoodX += sSizeFood;
  fPositionFoodY = rand() % ((int)fHeigthField - sSizeFood + background.snSizeRectangle);            // Координаты еды по высоте в начале игры
  if (fPositionFoodY < sSizeFood + background.snSizeRectangle) fPositionFoodY += sSizeFood + background.snSizeRectangle;
  food.setPosition(fPositionFoodX, fPositionFoodY);                                                     // Позиция еды в начале игры
  //cout << "Food created" << endl;
}


void Food::eatFood(RenderWindow &window, SnakeHead &head, BackgroundLevel &background) // Функция съедания еды змейкой
{ // Диапазон съедания еды
  if ((head.fSnakeHeadX + head.sHalfSH >= fPositionFoodX - fHalfFood && head.fSnakeHeadX - head.sHalfSH <= fPositionFoodX + fHalfFood) &&
      (head.fSnakeHeadY + head.sHalfSH >= fPositionFoodY - fHalfFood && head.fSnakeHeadY - head.sHalfSH <= fPositionFoodY + fHalfFood))
    {
      // Пересчёт координат еды
      
      fPositionFoodX = rand() % ((int)fWidthField  - sSizeFood);
      if (fPositionFoodX < sSizeFood) fPositionFoodX += sSizeFood;
      fPositionFoodY = rand() % ((int)fHeigthField - sSizeFood + background.snSizeRectangle);
      if (fPositionFoodY < sSizeFood + background.snSizeRectangle) fPositionFoodY += sSizeFood + background.snSizeRectangle;
      food.setPosition(fPositionFoodX, fPositionFoodY);
      
      ++SnakeTail::snCount;
      //cout << "Tail objects in the game: " << SnakeTail::snCount << endl;
      
      background.increasePoints();
    }
  
  window.draw(food); // Отрисовка еды на экране
}
  
