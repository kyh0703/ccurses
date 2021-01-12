#pragma once
#include <iostream>
#include <map>
#include <ncurses.h>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Border
{
    Border()
    {
        ls = ACS_VLINE;
        rs = ACS_VLINE;
        ts = ACS_HLINE;
        bs = ACS_HLINE;
        tl = ACS_ULCORNER;
        tr = ACS_URCORNER;
        bl = ACS_LLCORNER;
        br = ACS_LRCORNER;
    }

    chtype ls, rs, ts, bs;
    chtype tl, tr, bl, br;
};

struct Color
{
    Color()
    {
        bg = COLOR_BLACK;
        fg = COLOR_WHITE;
    }

    int bg, fg;
};

struct Rect
{
    Rect()
    {
        h = 0;
        w = 0;
        x = 0;
        y = 0;
    }

    Rect(int h, int w, int x, int y)
    {
        this->h = h;
        this->w = w;
        this->x = x;
        this->y = y;
    }

    int h, w, x, y;
};

struct Pos
{
    Pos(int y, int x)
    {
        this->y = y;
        this->x = x;
    }

    bool operator<(const Pos &rhs) const
    {
        if (y != rhs.y)
            return y < rhs.y;
        return x < rhs.x;
    }

    int y, x;
};

struct Rune
{
    Rune()
    {
        this->bg = COLOR_BLACK;
        this->fg = COLOR_WHITE;
        this->c = ' ';
    }

    Rune(chtype c)
    {
        this->bg = COLOR_BLACK;
        this->fg = COLOR_WHITE;
        this->c = c;
    }

    Rune(int bg, int fg, chtype c)
    {
        this->bg = bg;
        this->fg = fg;
        this->c = c;
    }

    int bg, fg;
    chtype c;
};

class Window
{
public:
    Window();
    virtual ~Window();

public:
    static void Log(const char *format, ...);

public:
    Rect GetRect();
    void SetRect(int h, int w, int x, int y);
    void SetColor(int bg, int fg);
    void SetTitle(string title);
    void DrawBase();
    void Erase();

public:
    virtual void Draw() = 0;

protected:
    void HLine(int y, int x, int n, Rune c);
    void VLine(int y, int x, int n, Rune c);
    void AddStr(int y, int x, string s);
    void CellPrint();

private:
    void InitCell();
    void MakeBorder();
    void MakeTitle();

protected:
    Rect mRect;
    Border mBorder;
    Color mColor;
    string mTitle;
    map<Pos, Rune> mCells;
};
