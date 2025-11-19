#include <iostream>
#include <thread>
#include <chrono>



#include "Headers.h"
#include "FuncsHeaders.h"

using namespace std;
using namespace chrono;
using namespace this_thread;

u16 rowInsertedByUser=InitRowValue, columnInsertedByUser=InitColumnValue;  // here bec ld error mult def in funsheaders.h and in main




void delaySeconds(u16 numberOfSeconds) {
    #ifdef _WIN32
    Sleep(numberOfSeconds * 1000);  // Sleep() expects milliseconds
    #else
    sleep_for(seconds(numberOfSeconds)); // instead of std::this_thread::sleep_for(std::chrono::seconds(seconds)); //sleepfor func takes duration of time object, not just a number
    #endif // _WIN32
}                                                              // so,seconds func convert a normal integer into a time duration object that C++ can understand for timing operations


void gotoXY(u16 row, u16 col) {

    #ifdef _WIN32
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { (SHORT)(col - 1), (SHORT)(row - 1) };
    SetConsoleCursorPosition(h, pos);
    #else
    // ANSI escape code: \033[row;colH
    cout << "\033[" << row << ";" << col << "H";     //Moves the cursor to row and col, \033[ starts the command, H tells the terminal “go here”.
    #endif
}


void clearScreen() {
    #ifdef _WIN32
    system("cls");    // Windows command
    #else
    cout << "\033[2J";              // \033[2J is an ANSI escape code that tells the terminal: “wipe the screen clean”.
    #endif
}


void setColor(Color color) {
#ifdef _WIN32
    int winColor = 0;
    switch(color) {
        case Color::RED:   winColor = 4; break; // Windows red
        case Color::GREEN: winColor = 2; break; // Windows green
        case Color::BLUE:  winColor = 1; break; // Windows blue
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), winColor);
#else                                                                       //\033[ → tells the terminal: “this is a command, not normal text”
    cout << "\033[" << static_cast<int>(color) << "m";                     // <number>m → tells the terminal which color to use
    #endif                                                                  //static_cast<int>(color) Converts the enum into its numeric value so the terminal understands it.
}

void resetColor() {
    #ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // default console color
    #else
    cout << "\033[0m";                            // \033[0m cancels any previous color formatting.
    #endif
}



u16 colorChoiceByUser(char*dataFromUser)
{
    u16 colorChoice=InitColor;
    cout << "Enter row position: ";
    cin >> rowInsertedByUser;
    cout << "Enter column position: ";
    cin >> columnInsertedByUser;
    cout << "\nChoose a color:\n1 - Red\n2 - Green\n3 - Blue\nEnter your choice: ";
    cin >> colorChoice;
    return colorChoice;
}



void printUserInputColor (u16 userColorChoice, char*dataFromUser)
{
        Color chosenColor=InitColor;
        switch(userColorChoice) {
        case 1: chosenColor = RED; break;
        case 2: chosenColor = GREEN; break;
        case 3: chosenColor = BLUE; break;
        default: chosenColor = RED; break; // default to red
        }
        clearScreen();
        gotoXY(rowInsertedByUser, columnInsertedByUser);
        setColor(chosenColor);
        cout << dataFromUser << endl;
}


 void printColoredString (char*dataFromUser)
 {
     printUserInputColor(colorChoiceByUser(dataFromUser),dataFromUser);
     resetColor();
     delaySeconds(InitDelay);
     clearScreen();
 }



