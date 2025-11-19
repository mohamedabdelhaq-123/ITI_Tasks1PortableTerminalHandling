#ifndef FUNCSHEADERS_H_INCLUDED
#define FUNCSHEADERS_H_INCLUDED


#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
/////////////////////////////////////Prototypes////////////////////////////////////

void gotoXY(u16 row, u16 col);
void clearScreen();
void resetColor();
void setColor(Color color);

u16 colorChoiceByUser(char*dataFromUser);
void printUserInputColor (u16 userColorChoice, char*dataFromUser);
void printColoredString (char*dataFromUser);
void delaySeconds(u16 seconds);

#endif // FUNCSHEADERS_H_INCLUDED
