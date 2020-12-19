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

    if(txGetPixel(x, y - dy) != RGB(192, 192, 192))
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
    txRectangle(700, 600, x + 100, y + 100);
    if(txGetPixel(x, y + dy) != RGB(192, 192, 192))
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
    if(txGetPixel(x + dx, y) != RGB(192, 192, 192))
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
    if(txGetPixel(x - dx, y) != RGB(192, 192, 192))
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
    int l[9][11] = {{1, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2},
                    {1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2},
                    {1, 1, 0, 1, 1, 1, 1, 2, 2, 2, 2},
                    {0, 2, 0, 2, 0, 0, 0, 2, 0, 2, 2},
                    {2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2},
                    {2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0},
                    {0, 2, 2, 2, 2, 0, 0, 2, 2, 2, 0},
                    {0, 1, 1, 1, 2, 0, 0, 1, 0, 2, 0},
                    {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1}};
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
            txSetColor(RGB (192, 192, 192));
            txSetFillColor(RGB (192, 192, 192));
            if(loc[i][j] == 1)
            {
                txSetFillColor(RGB (239, 228, 176));
                txSetColor(RGB (239, 228, 176));

            }
            if(loc[i][j] == 2)
            {
                txSetFillColor(RGB (153, 217, 234));
                txSetColor(RGB (153, 217, 234));
            }

            txRectangle(j * 64, i * 64, j * 64 + 64, i * 64 + 64);
        }
    }

    txSetFillColor(RGB(255, 255, 255));
}
