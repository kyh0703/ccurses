#pragma once
#include <form.h>
#include <menu.h>
#include <ncursesw/curses.h>
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

    int _color_count;
    COLOR_TABLE _color_table[64];
};
