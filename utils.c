#include <stdio.h>
#include <windows.h>

void gotoxy(int x, int y)
{
    HANDLE h;
    COORD pos;
    fflush(stdout);
    pos.X = x;
    pos.Y = y;
    h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(h, pos);
}

void clrscr()
{
    system("cls");
}

void Color(int t, int f)
{
    HANDLE H;
    H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, f * 16 + t);
}

void draw_rectangle(int x, int y, int lon, int haut)
{
    int i;
    gotoxy(x, y);          printf("%c", 218);
    gotoxy(x+lon, y);      printf("%c", 191);
    gotoxy(x, y+haut);     printf("%c", 192);
    gotoxy(x+lon, y+haut); printf("%c", 217);
    for (i = 1; i < lon; i++)
    {
        gotoxy(x+i, y);      printf("%c", 196);
        gotoxy(x+i, y+haut); printf("%c", 196);
    }
    for (i = 1; i < haut; i++)
    {
        gotoxy(x, y+i);     printf("%c", 179);
        gotoxy(x+lon, y+i); printf("%c", 179);
    }
}