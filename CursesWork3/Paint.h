#pragma once
#include <form.h>
#include <menu.h>
#include <ncurses.h>
#include <string.h>

typedef struct
{
    int no;
    int fg;
    int bg;
} COLOR_TABLE;

class Paint
{
public:
    static Paint &Get();
    short GetIndex(short bg, short fg);

protected:
    Paint();
    Paint(Paint const &) = delete;
    Paint(Paint &&) = delete;
    Paint &operator=(Paint const &&) = delete;
    Paint &operator=(Paint &&) = delete;

private:
    bool IsColorSet(short color);
    short AddColorSet(short bg, short fg);
    short FindColorSet(short bg, short fg);

    int _colorCnt;
    COLOR_TABLE _colorTable[64];
};
