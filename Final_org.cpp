#include "Libraries.hpp"
#include "LeaderBoardFun.hpp"
#include "Game.hpp"
#include "save.hpp"
#include "clui.h"
void MAKErandomBOMBS();
int ChackName(string);
void MainMenu();
int MakeNewGame();
void Menu_Monitoring(int How_Many_Option, string Options[], int Menu_Pointer);
void Select_SaveSlot();
void save();
void Top5LeadrBoard();
void MakeCustomGame();
void Add_To_LeaderBoard_List(int score);
void open(int, int);  // baz kardan ye khane (ba ghabeliyat baz kardan chand khoone khali hamzaman)
void flag(int, int);  // ye khoone ro flag mikone ya barmidare
void timesup();       // payan bazi ba tamoom shodan zaman
bool ISwinByFLAGS();  // check kardan win shodan ba flags
bool ISwinByOPENED(); // check kardan win shodan ba khane haye baz shode
void WIN();           // age bebazi in tabe ejra mishe
void SetTruth();
void welcome();
void GetName();
void Load_LeaderBoard_List();
void Monitoring_LoadGame(GameDetails temp[], bool Full[], int Menu_Pointer);
void LOSE();          // age bebazi in tabe ejra mishe
void monitoring(int); // neshan dadan jadval ,
                      // zaman va flag haye baghi mande,
                      // age zaman kamtar az 100 beshe zard mishe , age zaman kamtar az 50 she ghermez mishe

void Load_Game(bool);
bool PreView(GameDetails &, int);
void ChangeName();
int main()
{
    init_clui();
    Load_LeaderBoard_List();
    GetName();
    welcome();
    MainMenu();
    return 0;
}
void GetName()
{
    system("cls");
    printf("name ?: ");
    getline(cin, CurrentGame.name);
}
void MainMenu()
{
    char command;
    const int How_Many_Option = 6;
    string Options[How_Many_Option] = {"MakeNewGame", "loadgame", "ChangeName", "LeadrBoard", "controls", "Quit"};
    int Main_Menu_Pointer = 1;
    Menu_Monitoring(How_Many_Option, Options, Main_Menu_Pointer);
    while (command = getch())
    {
        if (command == 'w')
        {
            if (Main_Menu_Pointer > 1)
                Main_Menu_Pointer--;
            else
                Main_Menu_Pointer = How_Many_Option;
        }
        else if (command == 's')
        {
            if (Main_Menu_Pointer < How_Many_Option)
                Main_Menu_Pointer++;
            else
                Main_Menu_Pointer = 1;
        }
        else if (command == Enter)
        {
            switch (Main_Menu_Pointer)
            {
            case 1:
                MakeNewGame();
                break;
            case 2:
                Load_Game(0);
                Load_Save();
                PLAY();
                break;
            case 3:
                ChangeName();
                break;
            case 4:
                Top5LeadrBoard();
                getch();
                break;
            case 5:
                change_color_rgb(60, 224, 31);
                printf("commands : \n");
                printf("         you can use 'w','a','s','d' to move pointer\n");
                printf("         open ; press space\n");
                printf("         flag ; if you want to put or pick-up flag just enter f\n");
                printf("         end game ; o\n");
                printf("         end game (without save) ; q\n");
                getch();
                reset_color();
                break;
            case 6:
                system("cls");
                cout << "Bye...";
                Sleep(2000);
                quit();
                break;
            }
        }
        Menu_Monitoring(How_Many_Option, Options, Main_Menu_Pointer);
    }
}
void ChangeName()
{
    cout << "Enter new name : ";
    cin >> CurrentGame.name;
}
void Menu_Monitoring(int How_Many_Option, string Options[], int Menu_Pointer)
{
    system("cls");
    change_color_rgb(40, 102, 242);
    for (int i = 0; i < How_Many_Option; i++)
    {
        if (Menu_Pointer - 1 == i)
            cout << " ->";
        else
            cout << "   ";
        cout << Options[i] << endl;
    }
    reset_color();
}
int MakeNewGame()
{
    Load_Game(1);
    for (int i = 1; i < CurrentGame.x; i++)
        for (int j = 1; j < CurrentGame.y; j++)
        {
            cell[i][j].bomb = 0;
            cell[i][j].truth = 0;
            cell[i][j].flags = 0;
            cell[i][j].opened = 0;
        }

    CurrentGame.flagscount = 0;
    system("cls");
    char command;
    const int How_Many_Option = 5;
    string Options[How_Many_Option] = {"Level 1 : square(5 * 5) & 4 bombs & time : 200 s",
                                       "Level 2 : square(12 * 12) & 28 bombs & time : 800 s",
                                       "Level 3 : square(20 * 20) & 96 bombs & time : 2000 s",
                                       "Custom Game",
                                       "Back to Main menu"};
    int Make_NewGame_Pointer = 1;
    Menu_Monitoring(How_Many_Option, Options, Make_NewGame_Pointer);
    while (command = getch())
    {
        if (command == 'w')
        {
            if (Make_NewGame_Pointer > 1)
                Make_NewGame_Pointer--;
            else
                Make_NewGame_Pointer = How_Many_Option;
        }
        else if (command == 's')
        {
            if (Make_NewGame_Pointer < How_Many_Option)
                Make_NewGame_Pointer++;
            else
                Make_NewGame_Pointer = 1;
        }
        else if (command == Enter)
        {
            switch (Make_NewGame_Pointer)
            {
            case 1:
                CurrentGame.x = 6;
                CurrentGame.y = 6;
                CurrentGame.bombcount = 4;
                CurrentGame.TimeLeft = 200e3;
                break;
            case 2:
                CurrentGame.x = 13;
                CurrentGame.y = 13;
                CurrentGame.bombcount = 28;
                CurrentGame.TimeLeft = 800e3;
                break;
            case 3:
                CurrentGame.x = 21;
                CurrentGame.y = 21;
                CurrentGame.bombcount = 96;
                CurrentGame.TimeLeft = 2000e3;
                break;
            case 4:
                MakeCustomGame();
                break;
            case 5:
                MainMenu();
                break;
            }
            break;
        }
        Menu_Monitoring(How_Many_Option, Options, Make_NewGame_Pointer);
    }
    MAKErandomBOMBS();
    SetTruth();
    PLAY();
}
void MakeCustomGame()
{
    printf("\nx (min : 5 & max : 20): ");
    cin >> CurrentGame.x;
    CurrentGame.x += 1;
    printf("y (min : 5 & max : 20): ");
    cin >> CurrentGame.y;
    CurrentGame.y += 1;
    printf("how many bombs do you need ?: ");
    while (cin >> CurrentGame.bombcount)
    {
        if (CurrentGame.bombcount <= CurrentGame.x * CurrentGame.y)
            break;
    }
    printf("time(s): ");
    cin >> CurrentGame.TimeLeft;
    CurrentGame.TimeLeft *= 1000;
}
void MAKErandomBOMBS()
{
    srand(time(NULL));
    int done = 0;
    while (done < CurrentGame.bombcount)
    {
        int temp = rand() % ((CurrentGame.x - 1) * (CurrentGame.y - 1));
        if (cell[temp % (CurrentGame.x - 1) + 1][temp / (CurrentGame.x - 1) + 1].bomb == false)
            done++, cell[temp % (CurrentGame.x - 1) + 1][temp / (CurrentGame.x - 1) + 1].bomb = true;
    }
}
void SetTruth()
{
    for (int i = 1; i < CurrentGame.x; i++)
        for (int j = 1; j < CurrentGame.y; j++)
        {
            cell[i][j].monitor = '_';
            if (cell[i][j].bomb)
            {
                cell[i - 1][j - 1].truth++;
                cell[i - 1][j].truth++;
                cell[i - 1][j + 1].truth++;
                cell[i][j - 1].truth++;
                cell[i][j + 1].truth++;
                cell[i + 1][j - 1].truth++;
                cell[i + 1][j].truth++;
                cell[i + 1][j + 1].truth++;
            }
        }
}
void Load_Game(bool newGame)
{
    bool Full[5];
    int Menu_Pointer = 1;
    GameDetails temp[5];

    for (int i = 0; i < 5; i++)
    {
        if (PreView(&temp[i], i + 1))
            Full[i] = true;
        else
            Full[i] = false;
    }
    Monitoring_LoadGame(temp, Full, Menu_Pointer);
    char command;
    while (command = getch())
    {
        if (command == 'w')
        {
            if (Menu_Pointer > 1)
                Menu_Pointer--;
            else
                Menu_Pointer = 6;
        }
        else if (command == 's')
        {
            if (Menu_Pointer < 6)
                Menu_Pointer++;
            else
                Menu_Pointer = 1;
        }
        else if (command == Enter)
        {
            if (Menu_Pointer != 6)
            {
                if (newGame == false && Full[Menu_Pointer - 1] == false)
                {
                    cout << "\nyou can not choose this";
                    Sleep(1000);
                    continue;
                }
                else
                {
                    CurrentGame.GameNumber = Menu_Pointer;
                }
            }
            else
                MainMenu();
            break;
        }
        Monitoring_LoadGame(temp, Full, Menu_Pointer);
    }
}
void Monitoring_LoadGame(GameDetails temp[], bool Full[], int Menu_Pointer)
{
    change_color_rgb(40, 102, 242);
    system("cls");
    for (int i = 0; i < 6; i++)
    {
        if (Menu_Pointer - 1 == i)
            printf(" ->");
        else
            printf("   ");
        if (i == 5)
        {
            printf("back to main menu");
        }
        else if (Full[i])
            printf("save %d : (%d*%d)   bombs :%d   flags %d/%d    TimeLeft : %d(s)\n", i + 1, temp[i].x, temp[i].y, temp[i].bombcount, temp[i].flagscount, temp[i].bombcount, (temp[i].TimeLeft / 1000));
        else
            printf("save %d : Empty\n", i + 1);
    }
    reset_color();
}
void welcome()
{
    system("cls");
    change_color_rgb(40, 102, 242);
    cout << "Hello dear " + CurrentGame.name << endl;
    int end = get_window_cols();
    srand(time(NULL));
    for (int i = 0; i < end; i++)
    {
        change_color_rgb(rand() % 256, rand() % 256, rand() % 256);
        cout << '-';
        delay(20);
    }
    reset_color();
}