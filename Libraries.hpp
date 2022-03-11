#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <time.h>
#include <conio.h>
#include <ctime>
#include <windows.h>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define Enter 13
const int Xcapacity = 30;
const int Ycapacity = 30;
struct CellConcept
{
    int truth;
    char monitor;
    bool opened, flags, bomb;
};
struct GameDetails
{
    int GameNumber;
    string name;
    int x, y;
    int flagscount = 0;
    int bombcount = 1;
    int TimeLeft = 10000;
};
CellConcept cell[Xcapacity][Ycapacity];
GameDetails CurrentGame;
int pointer[2] = {1, 1};
bool t100 = false, t50 = false;
int dx[] = {1, 1, 1, -1, -1, -1, 0, 0}; // khane haye hamsaye
int dy[] = {1, -1, 0, 1, -1, 0, 1, -1}; // khane haye hamsaye