#pragma once
#include <form.h>
#include <menu.h>
#include <ncurses.h>
#include <string.h>

typedef struct
{
    short no;
    short fg;
    short bg;
} COLOR_TABLE;

class Paint
{
public:
    enum
    {
        MENUCOLOR_DISABLE,
        MENUCOLOR_CURSOR,
        MENUCOLOR_DEFAULT,
    };

public:
    static Paint &Get();

protected:
    Paint();
    Paint(Paint const &) = delete;
    Paint(Paint &&) = delete;
    Paint &operator=(Paint const &&) = delete;
    Paint &operator=(Paint &&) = delete;

public:
    short GetIndex(short bg, short fg);

private:
    bool IsColorSet(short color);
    short AddColorSet(short bg, short fg);
    short FindColorSet(short bg, short fg);

private:
    int _colorCnt;
    COLOR_TABLE _colorTable[64];
};
