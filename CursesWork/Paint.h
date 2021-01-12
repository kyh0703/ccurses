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
    bool IsColorSet(short color);
    short FindIndex(short fg, short bg);
    short AppendColorSet(short fg, short bg);
    short FindColorSet(short fg, short bg);

private:
    int mColorCnt;
    COLOR_TABLE mColorTable[64];
};
