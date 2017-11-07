#include <iostream>
#include <windows.h>
#include <vector>
using namespace std;
int MapW,MapH;
char Map[100][100]={
"########################################################",
"#                                                      #",
"#                                                      #",
"#                                                      #",
"#                                                      #",
"#                                                      #",
"#                                                      #",
"#                                                      #",
"#                                                      #",
"#                                                      #",
"#                                                      #",
"#                                                      #",
"#                                                      #",
"########################################################"};
struct Block{
    int x,y;
};

void gotoxy(int x, int y)
{
  COORD coord={x,y};
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void dibujaMapa(vector <Block>jugador)
{
    MapH=0;
    system("cls");
    for (int i=0;Map[i][0];i++)
    {
        MapW=0;
        for (int j = 0 ;Map[i][j];j++)
        {
            MapW++;
            if (Map[i][j]!=' ')
            {
                gotoxy(j,i);
                cout<<Map[i][j];
            }
        }
        MapH++;
    }
    for (int i =0 ;i<jugador.size();i++)
    {
        gotoxy(jugador[i].x,jugador[i].y);
        cout<<char (219);
    }
}

bool checkLose(int x, int y,vector <Block>&jugador)
{
    if (Map[y][x]=='#')
        return true;
    if (jugador.size()>3)
    {
        for (int i = 3;i<jugador.size();i++)
            if (jugador[i].x==x&&jugador[i].y==y)
                return true;
    }
    if (Map[y][x]=='@')
    {
        Map[y][x]=' ';
        Block nuejugador;
        nuejugador.x=jugador[jugador.size()-1].x;
        nuejugador.y=jugador[jugador.size()-1].y;
        jugador.push_back(nuejugador);
        int rx,ry;
        do{
            rx=rand()%MapW;
            ry=rand()%MapH;
        }while (checkLose(rx, ry,jugador));
        Map[ry][rx]='@';
        dibujaMapa(jugador);
    }
    return false;
}

void jInit(int x,int y ,vector<Block> &jugador)
{
    Block nuejugador;
    nuejugador.x=x;
    nuejugador.y=y;
    jugador.push_back(nuejugador);
}

bool Move(vector<Block>&jugador,short dire[2])
{
    int oldx,oldy,x,y;
    gotoxy(jugador[jugador.size()-1].x,jugador[jugador.size()-1].y);
    cout<<" ";
    oldx=jugador[0].x;
    oldy=jugador[0].y;
    jugador[0].x+=dire[0];
    jugador[0].y+=dire[1];
    gotoxy(jugador[0].x,jugador[0].y);
    cout<<char(219);
    if (jugador.size()>1)
    if (checkLose(jugador[0].x,jugador[0].y,jugador))
        return true;
    return false;
}

int main()
{
    bool GameIsRunning=true;
    int GameSpeed=80;
    short dire[2]={0,1};
    vector<Block> jugador;
    jInit(1,1,jugador);
    dibujaMapa(jugador);
    while (GameIsRunning)
    {
        if (GetAsyncKeyState(VK_UP))
        {
            if (dire[1]==0)
            {
                dire[1]=-1;
                dire[0]=0;
            }
        }
        else if (GetAsyncKeyState(VK_DOWN))
        {
            if (dire[1]==0)
            {
                dire[1]=1;
                dire[0]=0;
            }
        }
        else if (GetAsyncKeyState(VK_LEFT))
        {
            if (dire[0]==0)
            {
                dire[1]=0;
                dire[0]=-1;
            }
        }
        else if (GetAsyncKeyState(VK_RIGHT))
        {
            if (dire[0]==0)
            {
                dire[1]=0;
                dire[0]=1;
            }
        }
        if(Move(jugador,dire))
        {
          system("cls");
          cout<<"Game Over"<<endl;
          system("pause");
          return 0;
        }
        Sleep(GameSpeed);
    }
}
