#pragma once
#include "Libraries.hpp"
#include "clui.h"
struct LeaderBoard
{
    string name;
    int score;
};
vector<LeaderBoard> LeaderBoard_List;

void Load_LeaderBoard_List()
{
    ifstream LeaderBoard_SaveFile;
    LeaderBoard_SaveFile.open("LeaderBoard.txt");
    int count;
    LeaderBoard_SaveFile >> count;
    for (int i = 0; i < count; i++)
    {
        LeaderBoard_List.push_back(LeaderBoard());
        LeaderBoard_SaveFile >> LeaderBoard_List[i].name;
        LeaderBoard_SaveFile >> LeaderBoard_List[i].score;
    }
    LeaderBoard_SaveFile.close();
}
void Add_To_LeaderBoard_List(int score)
{
    for (int i = 0; i < LeaderBoard_List.size(); i++)
    {
        if (CurrentGame.name == LeaderBoard_List[i].name)
        {
            LeaderBoard_List[i].score += score;
            for (int j = i - 1; ~j; j--)
            {
                if (LeaderBoard_List[j + 1].score > LeaderBoard_List[j].score)
                    swap(LeaderBoard_List[j + 1], LeaderBoard_List[j]);
                else
                    return;
            }
            return;
        }
    }
    LeaderBoard now;
    now.name = CurrentGame.name;
    now.score = score;
    LeaderBoard_List.push_back(now);
    for (int j = LeaderBoard_List.size() - 2; j >= 0; j--)
    {
        if (LeaderBoard_List[j + 1].score > LeaderBoard_List[j].score)
            swap(LeaderBoard_List[j + 1], LeaderBoard_List[j]);
        else
            return;
    }
}
void Save_LeaderBoard_List()
{
    system("del LeaderBoard.txt");
    system("type nul > LeaderBoard.txt");
    ofstream LeaderBoard_SaveFile;
    LeaderBoard_SaveFile.open("LeaderBoard.txt");
    int count = LeaderBoard_List.size();
    LeaderBoard_SaveFile << count << endl;
    for (int i = 0; i < count; i++)
    {
        LeaderBoard_SaveFile << LeaderBoard_List[i].name << "   ";
        LeaderBoard_SaveFile << LeaderBoard_List[i].score << "\n";
    }
    LeaderBoard_SaveFile.close();
}
void Show_LeaderBoard_List()
{
    change_color_rgb(231, 250, 20);
    printf("Top5\n");
    for (int i = 0; i < 5; i++)
    {
        cout << "#" << i + 1 << "   " << LeaderBoard_List[i].name << "   score : " << LeaderBoard_List[i].score << endl;
    }
    reset_color();
}
void Top5LeadrBoard()
{
    Show_LeaderBoard_List();
}
