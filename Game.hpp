#pragma once
#include "LeaderBoardFun.hpp"
#include "clui.h"
#include "Libraries.hpp";
void save();
void MainMenu();
void LOSE();
void WIN();
void timesup();
void monitoring(int t);
void open(int X, int Y);
void flag(int X, int Y);
bool ISwinByOPENED();
bool ISwinByFLAGS();
int MakeNewGame();
void clear_Save_slot();

void PLAY()
{
    change_color_rgb(196, 56, 242);
    char command;
    clock_t start;
    start = clock();
    pointer[0] = 1;
    pointer[1] = 1;
    monitoring((CurrentGame.TimeLeft - (clock() - start)) / 1000);
    while ((command = getch()))
    {
        CurrentGame.TimeLeft = CurrentGame.TimeLeft - (clock() - start) / 1000;
        if (command == 'w' || command == 'W')
        {
            if (pointer[1] > 1)
                pointer[1]--;
            else if (pointer[1] == 1)
                pointer[1] = CurrentGame.y - 1;
        }
        else if (command == 's' || command == 'S')
        {
            if (pointer[1] < (CurrentGame.y - 1))
                pointer[1]++;
            else if (pointer[1] == CurrentGame.y - 1)
                pointer[1] = 1;
        }
        else if (command == 'a' || command == 'A')
        {
            if (pointer[0] > 1)
                pointer[0]--;
            else if (pointer[0] == 1)
                pointer[0] = CurrentGame.x - 1;
        }
        else if (command == 'd' || command == 'D')
        {
            if (pointer[0] < (CurrentGame.x - 1))
                pointer[0]++;
            else if (pointer[0] == CurrentGame.x - 1)
                pointer[0] = 1;
        }
        else if (command == 'I' || command == 'i')
        {
            printf("commands : \n");
            printf("         you can use 'w','a','s','d' to move pointer\n");
            printf("         open ; enter o\n");
            printf("         flag ; if you want to put or pick-up flag just enter f\n");
            printf("         end game ; if you want to end the game just enter e :'( \n");
            printf("\n\n    Are you ready ???\n    press a key to start playing\n");
            getch();
        }
        else if (command == ' ')
        {
            if (cell[pointer[0]][pointer[1]].bomb)
            {
                LOSE();
                break;
            }
            else if (cell[pointer[0]][pointer[1]].flags == 0 && cell[pointer[0]][pointer[1]].opened == 0)
                open(pointer[0], pointer[1]);
            if (ISwinByOPENED())
            {
                monitoring(((CurrentGame.TimeLeft - (clock() - start)) / 1000));
                WIN();
            }
        }
        else if (command == 'f' || command == 'F')
        {
            if (CurrentGame.flagscount < CurrentGame.bombcount || cell[pointer[0]][pointer[1]].flags)
                flag(pointer[0], pointer[1]);
            else
            {
                cout << "you reached to maximum flags' count";
                Sleep(600);
            }
            if (CurrentGame.bombcount == CurrentGame.flagscount && ISwinByFLAGS())
            {
                WIN();
            }
        }
        else if (command == 'o' || command == 'O')
        {
            save();
            MainMenu();
            break;
        }
        else if (command == 'q' || command == 'Q')
        {
            MainMenu();
        }
        else
        {
            printf("%c is not recognized as a command\n", command);
            continue;
        }
        int t = ((CurrentGame.TimeLeft - (clock() - start)) / 1000);
        // if (t100 == false && t < 100)
        // {
        //     t100 = true;
        //     system("color 6");
        // }
        // else if (t50 == false && t < 50)
        // {
        //     t50 = true;
        //     system("color 4");
        // }
        if (t > 0)
        {
            monitoring(t);
        }
        else
        {
            timesup();
            break;
        }
    }
}
void LOSE()
{
    system("cls");
    change_color_rgb(170, 50, 54);
    printf("\n\n=================LOSE=================\n");
    play_beep();
    reset_color();
    printf("   ");
    for (int i = 1; i < CurrentGame.x; i++)
        printf("%d ", i);
    printf("\n");
    for (int j = 1; j < CurrentGame.y; j++)
    {
        printf("%d- ", j);
        for (int i = 1; i < CurrentGame.x; i++)
        {
            if (cell[i][j].bomb)
                cell[i][j].monitor = '*';
            else
            {
                if (cell[i][j].truth)
                    cell[i][j].monitor = 48 + cell[i][j].truth;
                else
                {
                    cell[i][j].monitor = ' ';
                }
            }
            printf("%c ", cell[i][j].monitor);
        }
        printf("\n");
    }
    clear_Save_slot();
    printf("do you want play again? \n enter p\n enter M to back to the main menu\n");
    char play;
    while (cin >> play)
    {
        if (play == 'P' || play == 'p')
            MakeNewGame();
        if (play == 'M' || play == 'm')
        {
            MainMenu();
        }
        else
            printf("%c is not recognized as a command\n", play);
    }
}
void WIN()
{
    change_color_rgb(50, 170, 82);
    printf("\n\n=================YOU WON=================\n");
    play_beep();
    reset_color();
    int score = CurrentGame.bombcount * CurrentGame.bombcount * CurrentGame.TimeLeft / 1000;
    Add_To_LeaderBoard_List(score);
        Save_LeaderBoard_List();
    printf("your score : %d\n", score);
    printf("do you want try again? \n enter p\n enter M to back to the main menu\n");
    clear_Save_slot();
    char play;
    while (cin >> play)
    {
        if (play == 'P' || play == 'p')
            MakeNewGame();
        if (play == 'M' || play == 'm')
        {
            MainMenu();
        }
        else
            printf("%c is not recognized as a command\n", play);
    }
}
void timesup()
{
    system("cls");
    change_color_rgb(205, 224, 31);
    play_beep();
    printf("\n\n=================Time is up=================\n");
    reset_color();
    printf("   ");
    for (int i = 1; i < CurrentGame.x; i++)
        printf("%d ", i);
    printf("\n");
    for (int j = 1; j < CurrentGame.y; j++)
    {
        printf("%d- ", j);
        for (int i = 1; i < CurrentGame.x; i++)
        {
            if (cell[i][j].bomb)
                cell[i][j].monitor = '*';
            else
            {
                if (cell[i][j].truth)
                    cell[i][j].monitor = 48 + cell[i][j].truth;
                else
                {
                    cell[i][j].monitor = ' ';
                }
            }
            printf("%c ", cell[i][j].monitor);
        }
        printf("\n");
    }
    clear_Save_slot();
    printf("do you want try again? \n enter p\n enter M to back to the main menu\n");
    char play;
    while (cin >> play)
    {
        if (play == 'P' || play == 'p')
            MakeNewGame();
        if (play == 'M' || play == 'm')
        {
            MainMenu();
        }
        else
            printf("%c is not recognized as a command\n", play);
    }
}
void monitoring(int t)
{
    system("cls");
    printf("Times's Left : %ds      Left flags : %d    press 'i' to see commands\n    ", t, CurrentGame.bombcount - CurrentGame.flagscount);
    for (int i = 1; i < CurrentGame.x; i++)
        if (i < 9)
            printf(" %d  ", i);
        else if (i == 9)
            printf(" %d ", i);
        else
            printf(" %d ", i);
    printf("\n");
    for (int j = 1; j < CurrentGame.y; j++)
    {
        if (j < 10)
            printf("%d-  ", j);
        else
            printf("%d- ", j);
        for (int i = 1; i < CurrentGame.x; i++)
        {
            if (i < 9)
            {
                if (i == pointer[0] && j == pointer[1])
                    printf("\\^/ ");
                else
                    printf(" %c  ", cell[i][j].monitor);
            }
            else if (i == 9)
            {
                if (i == pointer[0] && j == pointer[1])
                    printf("\\^/");
                else
                    printf(" %c ", cell[i][j].monitor);
            }
            else
            {
                if (i == pointer[0] && j == pointer[1])
                    printf(" \\^/");
                else
                    printf("  %c ", cell[i][j].monitor);
            }
        }
        printf("\n\n");
        flush();
    }
}
void open(int X, int Y)
{
    cell[X][Y].opened = true;
    if (cell[X][Y].truth)
    {
        cell[X][Y].monitor = 48 + cell[X][Y].truth;
        return;
    }
    cell[X][Y].monitor = ' ';
    for (int i = 0; i < 8; i++)
    {
        int nx, ny;
        nx = X + dx[i];
        ny = Y + dy[i];
        if (nx < 1 || nx > (CurrentGame.x - 1) || ny < 1 || ny > (CurrentGame.y - 1) || cell[nx][ny].bomb || cell[nx][ny].flags || cell[nx][ny].opened)
            continue;
        open(nx, ny);
    }
}
void flag(int X, int Y)
{
    cell[X][Y].flags ^= 1;
    if (cell[X][Y].flags)
    {
        cell[X][Y].monitor = 'F';
        CurrentGame.flagscount++;
    }
    else
    {
        cell[X][Y].monitor = '_';
        CurrentGame.flagscount--;
    }
}
bool ISwinByOPENED()
{
    for (int i = 1; i < CurrentGame.x; i++)
        for (int j = 1; j < CurrentGame.y; j++)
            if (cell[i][j].bomb == cell[i][j].opened)
                return false;
    return true;
}
bool ISwinByFLAGS()
{
    for (int i = 1; i < CurrentGame.x; i++)
        for (int j = 1; j < CurrentGame.y; j++)
            if (cell[i][j].bomb != cell[i][j].flags)
                return false;
    return true;
}
