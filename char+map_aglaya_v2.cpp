// Arseniy version 10.12.2020
#include <stdio.h>
#include <TXLib.h>

struct Map
{
    HDC map_pic;
    int n, m;
    int loc[9][11];

    Map();
    ~Map();
    void Draw();
    int  Get_cell(int x, int y);
    void Set_cell(int x, int y, int type);
};


struct Character
{
    HDC Sprite_list;
    int x, y, a0, b0, a, b, dy, dx, k;
    int point = 0;
    COLORREF color;

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
    txCreateWindow (800, 600);

    Map location;
    location.Draw();

    Character Girl;
    Girl.Draw();

    while (!GetAsyncKeyState (VK_ESCAPE))
    {
        if (GetAsyncKeyState (0x57))
            Girl.Up(location);

        if (GetAsyncKeyState (0x53))
            Girl.Down(location);

        if (GetAsyncKeyState (0x44))
            Girl.Right(location);

        if (GetAsyncKeyState (0x41))
            Girl.Left(location);

        if(location.Get_cell(Girl.x, Girl.y) == 2 && GetAsyncKeyState(0x45))
        {
            location.Set_cell(Girl.x, Girl.y, 1);
            Girl.point += 1;
        }
        if(Girl.point == 5)
        {
            location.Set_cell(600, 560, 1);
        }
        if(Girl.point == 5 && location.Get_cell(Girl.x, Girl.y) == 3)
        {
             const int finish = txMessageBox("Я хочу пиццу");
             return 0;
        }
        location.Draw();
        Girl.Draw();
        txSleep(100);
        txClear();
    }

    return 0;
}



Character::Character()
{
    Sprite_list = txLoadImage ("anime_girl.bmp");
    x = 30;
    y = 65;
    a0 = 42;
    b0 = 71;
    a = 0;
    b = 0;
    dx = 10;
    dy = 10;
    k = 3;
    color = TX_WHITE;
}

Character::~Character()
{
    txDeleteDC (Sprite_list);
}

void Character::Up(Map &location)
{
     if(y <= 40)
        return;
    if(location.Get_cell(x, y - dy) != 0)
    {
        y -= dy;
        b = b0 * 3 + 1;
        a += a0;

        if (a >= a0 * k)
            a = a0;

    }
}

void Character::Down(Map &location)
{
    if(y >= 570)
        return;
    if(location.Get_cell(x, y + dy) != 0)
    {
        y += dy;
        b = b0 * 0;
        a += a0;

        if (a >= a0 * k)
            a = a0;
    }
}

void Character::Right(Map &location)
{
    if(x >= 680)
        return;
    if(location.Get_cell(x + dx, y) != 0)
    {
        x += dx;
        b = b0 * 2;
        a += a0;

        if (a >= a0 * k)
            a = a0;
    }
}

void Character::Left(Map &location)
{
    if(x <= 20)
        return;
    if(location.Get_cell(x - dx, y) != 0)
    {
        x -= dx;
        b = b0 * 1;
        a += a0;

        if (a >= a0 * k)
            a = a0;

    }
}

void Character::Draw()
{
    txTransparentBlt (txDC(), x - a0 / 2, y - b0, a0, b0, Sprite_list, a, b, color);
}

Map::~Map()
{
     txDeleteDC(map_pic);
}

Map::Map()
{
    n = 9;
    m = 11;
    int l[9][11] = {{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {1, 1, 0, 0, 0, 0, 1, 2, 1, 0, 0},
                    {0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0},
                    {0, 2, 0, 0, 1, 0, 1, 0, 1, 0, 0},
                    {0, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0},
                    {0, 1, 2, 1, 1, 0, 1, 0, 1, 0, 0},
                    {0, 1, 0, 0, 1, 0, 2, 0, 1, 0, 0},
                    {0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0},
                    {0, 1, 1, 1, 2, 0, 0, 0, 1, 0, 3}};
    map_pic = txLoadImage("map_pic.bmp");

    int i, j;
    for(i = 0; i < n; i += 1)
        for(j = 0; j < m; j += 1)
            loc[i][j] = l[i][j];
}

void Map::Draw()
{
    int i, j;
    for(i = 0; i < n; i += 1)
    {
        for(j = 0; j < m; j += 1)
        {
            txTransparentBlt(txDC(), j*64, i*64, 64, 64, map_pic, 0, 0, TX_WHITE);
            if(loc[i][j] == 1)
            {
                txTransparentBlt(txDC(), j*64, i*64, 64, 64, map_pic, 0, 64, TX_WHITE);
            }
            if(loc[i][j] == 2)
            {
                txTransparentBlt(txDC(), j*64, i*64, 64, 64, map_pic, 64, 64, TX_WHITE);
            }
            if(loc[i][j] == 3)
            {
                txTransparentBlt(txDC(), j*64, i*64, 64, 64, map_pic, 125, 64, TX_WHITE);
            }
        }
    }

}

int  Map::Get_cell(int x, int y)
{
    int i = x / 64;
    int j = y / 64;
    return loc[j][i];
}

void Map::Set_cell(int x, int y, int type)
{
    loc[y / 64][x / 64] = type;
}


