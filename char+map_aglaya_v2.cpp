#include <stdio.h>
#include <windows.h>
#include <TXLib.h>

class Map
{
  public:
    HDC map_pic;
    int n, m;
    int loc[8][10];

    Map();
    ~Map();
    void Draw();
    int  Get_cell(int x, int y);
    void Set_cell(int x, int y, int type);
};

class Character
{
  public:
    HDC DC;
    int x, y, a0, b0, a, b, dy, dx, k;
    int diamond = 0;
    COLORREF color;
    Map location;

    Character();
    ~Character();
    void Up(Map &location);
    void Down(Map &location);
    void Right(Map &location);
    void Left(Map &location);
    void Draw();
};



int main()
{
    txCreateWindow(800, 600);

    Map location;
    location.Draw();

    const char* name = txInputBox ("Tell me your name", "System", "Black knight");

    Character Boy;
    Boy.Draw();

    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        if(GetAsyncKeyState(VK_UP))
            Boy.Up(location);

        if(GetAsyncKeyState(VK_DOWN))
            Boy.Down(location);

        if(GetAsyncKeyState(VK_RIGHT))
            Boy.Right(location);

        if(GetAsyncKeyState(VK_LEFT))
            Boy.Left(location);

        if(location.Get_cell(Boy.x, Boy.y) == 2 && GetAsyncKeyState(VK_SPACE))
        {
            location.Set_cell(Boy.x, Boy.y, 1);
            Boy.diamond += 1;
        }


        if(Boy.x < 80 && Boy.y < 60 && Boy.diamond == 2)
            break;

        location.Draw();
        Boy.Draw();
        txSleep(100);
        txClear();
    }

    txSetFillColor(TX_BLACK);
    txClear();

    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        txSelectFont ("Times New Roman", 40, 0, FW_BOLD);
        txDrawText  (200, 100, 600, 300, "CONGRATULATIONS!");
        txSleep(10000);
        const char* name = txInputBox ("Go to next level?", "System", "Yes!");
    }

    return 0;
}



Character::Character()
{
   DC = txLoadImage("sprite_aglaya.bmp");
   x = 700;
   y = 380;
   a0 = 45;
   b0 = 94;
   a = 0;
   b = 0;
   dx = 10;
   dy = 10;
   k = 6;
   color = TX_WHITE;
}

Character::~Character()
{
    txDeleteDC(DC);
}

void Character::Up(Map &location)
{
    if(y <= 40 && diamond < 2)
        return;
    if(location.Get_cell(x, y - dy) != 0)
    {
        y -= dy;
        b = b0 * 2 + 10;
        a += a0;
        if(a >= a0 * k)
            a = a0;
    }
}

void Character::Down(Map &location)
{
    if(location.Get_cell(x, y + dy) != 0)
    {
        y += dy;
        b = b0 * 0;
        a += a0;
        if(a >= a0 * k)
            a = a0;
    }
}

void Character::Right(Map &location)
{
    if(location.Get_cell(x + dx, y) != 0)
    {
        x += dx;
        b = b0 * 3 + 12;
        a += a0;
        if(a >= a0 * k)
            a = a0;
    }
}

void Character::Left(Map &location)
{
    if(x <= 60 && diamond < 2)
        return;
    if(location.Get_cell(x - dx, y) != 0)
    {
        x -= dx;
        b = b0 * 1;
        a += a0;
        if(a >= a0 * k)
            a = a0;
    }

}

void Character::Draw()
{
    txTransparentBlt (txDC(), x - a0/2, y - b0, a0, b0, DC, a, b, color);
}



Map::Map()
{
    n = 6;
    m = 10;
    int l[6][10] = {{1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {1, 1, 0, 0, 0, 0, 1, 2, 1, 0},
                    {0, 1, 0, 0, 1, 1, 1, 0, 1, 0},
                    {0, 2, 0, 0, 1, 0, 1, 0, 1, 0},
                    {0, 1, 0, 0, 1, 0, 1, 1, 1, 0},
                    {0, 1, 1, 1, 1, 0, 0, 0, 1, 0},};
    map_pic = txLoadImage("map_aglaya.bmp");

    int i, j;
    for(i = 0; i < n; i += 1)
        for(j = 0; j < m; j += 1)
            loc[i][j] = l[i][j];
}

Map::~Map()
{
     txDeleteDC(map_pic);
}

void Map::Draw()
{
    int i, j;
    for(i = 0; i < n; i += 1)
    {
        for(j = 0; j < m; j += 1)
        {
            txTransparentBlt(txDC(), j*80, i*60, 100, 85, map_pic, 214, 82, TX_WHITE);
            if(loc[i][j] == 1)
            {
                txTransparentBlt(txDC(), j*80, i*60, 100, 85, map_pic, 85, 82, TX_WHITE);
            }
            if(loc[i][j] == 2)
            {
                txTransparentBlt(txDC(), j*80, i*60, 100, 85, map_pic, 330, 108, TX_WHITE);
            }
        }
    }

}

int  Map::Get_cell(int x, int y)
{
    int i = x / 80;
    int j = y / 60;
    return loc[j][i];
}

void Map::Set_cell(int x, int y, int type)
{
    loc[y / 60][x / 80] = type;
}
