#ifndef CommonSettings_h
#define CommonSettings_h

const float fWidthWindow = 700.0F;
const float fHeigthWindow = 530.0F;

const float fWidthField = fWidthWindow;  // Размер игрового поля по ширине
const float fHeigthField = fHeigthWindow - 30; // Размер игрового поля по высоте

enum direction {UP, DOWN, LEFT, RIGHT};
enum pos {X, Y, DIR};

#endif
