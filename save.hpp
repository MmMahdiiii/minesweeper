#pragma once
#include "Libraries.hpp"
void save()
{
    ofstream SaveGame_Loading;
    if (CurrentGame.GameNumber == 1)
    {
        system("del save1.txt");
        system("type nul > save1.txt");
        SaveGame_Loading.open("save1.txt");
    }
    else if (CurrentGame.GameNumber == 2)
    {
        system("del save2.txt");
        system("type nul > save2.txt");
        SaveGame_Loading.open("save2.txt");
    }
    else if (CurrentGame.GameNumber == 3)
    {
        system("del save3.txt");
        system("type nul > save3.txt");
        SaveGame_Loading.open("save3.txt");
    }
    else if (CurrentGame.GameNumber == 4)
    {
        system("del save4.txt");
        system("type nul > save4.txt");
        SaveGame_Loading.open("save4.txt");
    }
    else if (CurrentGame.GameNumber == 5)
    {
        system("del save5.txt");
        system("type nul > save5.txt");
        SaveGame_Loading.open("save5.txt");
    }
    SaveGame_Loading << 'f' << endl;
    SaveGame_Loading << CurrentGame.GameNumber << endl
                     << CurrentGame.x << ' '
                     << CurrentGame.y << endl;
    SaveGame_Loading << CurrentGame.bombcount << ' ' << CurrentGame.flagscount << endl;
    SaveGame_Loading << CurrentGame.TimeLeft << "\n\n";
    for (int i = 1; i < CurrentGame.x; i++)
        for (int j = 1; j < CurrentGame.y; j++)
        {
            if (cell[i][j].monitor == ' ')
                cell[i][j].monitor = 'e';
            SaveGame_Loading << cell[i][j].truth << ' ' << cell[i][j].monitor << ' '
                             << cell[i][j].bomb << ' ' << cell[i][j].flags << ' '
                             << cell[i][j].opened << endl;
        }
    SaveGame_Loading.close();
}
void Load_Save()
{
    ifstream SaveGame_Loading;
    if (CurrentGame.GameNumber == 1)
    {
        SaveGame_Loading.open("save1.txt");
    }
    else if (CurrentGame.GameNumber == 2)
    {
        SaveGame_Loading.open("save2.txt");
    }
    else if (CurrentGame.GameNumber == 3)
    {
        SaveGame_Loading.open("save3.txt");
    }
    else if (CurrentGame.GameNumber == 4)
    {
        SaveGame_Loading.open("save4.txt");
    }
    else if (CurrentGame.GameNumber == 5)
    {
        SaveGame_Loading.open("save5.txt");
    }
    char Empty;
    SaveGame_Loading >> Empty;
    SaveGame_Loading >> CurrentGame.GameNumber >> CurrentGame.x >> CurrentGame.y;
    SaveGame_Loading >> CurrentGame.bombcount >> CurrentGame.flagscount;
    SaveGame_Loading >> CurrentGame.TimeLeft;
    for (int i = 1; i < CurrentGame.x; i++)
        for (int j = 1; j < CurrentGame.y; j++)
        {
            SaveGame_Loading >> cell[i][j].truth >> cell[i][j].monitor >> cell[i][j].bomb >> cell[i][j].flags >> cell[i][j].opened;
            if (cell[i][j].monitor == 'e')
                cell[i][j].monitor = ' ';
        }
    SaveGame_Loading.close();
}
void clear_Save_slot()
{
    ofstream SaveGame_Loading;
    if (CurrentGame.GameNumber == 1)
    {
        system("del save1.txt");
        system("type nul > save1.txt");
        SaveGame_Loading.open("save1.txt");
        SaveGame_Loading << 'e' << endl;
    }
    else if (CurrentGame.GameNumber == 2)
    {
        system("del save.txt");
        system("type nul > save2.txt");
        SaveGame_Loading.open("save2.txt");
        SaveGame_Loading << 'e' << endl;
    }
    else if (CurrentGame.GameNumber == 3)
    {
        system("del save.txt");
        system("type nul > save3.txt");
        SaveGame_Loading.open("save3.txt");
        SaveGame_Loading << 'e' << endl;
    }
    else if (CurrentGame.GameNumber == 4)
    {
        system("del save.txt");
        system("type nul > save4.txt");
        SaveGame_Loading.open("save4.txt");
        SaveGame_Loading << 'e' << endl;
    }
    else if (CurrentGame.GameNumber == 5)
    {
        system("del save.txt");
        system("type nul > save5.txt");
        SaveGame_Loading.open("save4.txt");
        SaveGame_Loading << 'e' << endl;
    }
    SaveGame_Loading.close();
}
bool PreView(GameDetails *temp, int a)
{
    ifstream SaveGame_Loading;
    if (a == 1)
    {
        SaveGame_Loading.open("save1.txt");
    }
    else if (a == 2)
    {
        SaveGame_Loading.open("save2.txt");
    }
    else if (a == 3)
    {
        SaveGame_Loading.open("save3.txt");
    }
    else if (a == 4)
    {
        SaveGame_Loading.open("save4.txt");
    }
    else if (a == 5)
    {
        SaveGame_Loading.open("save5.txt");
    }
    char Empty;
    SaveGame_Loading >> Empty;
    if (Empty == 'e')
        return false;
    SaveGame_Loading >> temp->GameNumber >> temp->x >> temp->y;
    SaveGame_Loading >> temp->bombcount >> temp->flagscount;
    SaveGame_Loading >> temp->TimeLeft;
    return true;
}