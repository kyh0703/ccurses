#pragma once
#include <iostream>
#include <sstream>
#include <ncurses.h>
#include <string>
#include <vector>
#include <map>

using namespace std;

struct Border
{
    chtype ls, rs, ts, bs;
    chtype tl, tr, bl, br;
};

struct Color
{
    short bg, fg;
};

struct Rect
{
    short h, w, x, y;
};

struct Pos
{
    short y, x;
    Pos(short y, short x)
    {
        this->y = y;
        this->x = x;
    }
};

class Widget
{
public:
    Widget();
    virtual ~Widget();

public:
    static void Log(const char *format, ...);

public:
    Rect GetRect();
    void SetRect(short h, short w, short x, short y);
    void SetColor(short bg, short fg);
    void SetTitle(string title);
    void DrawBase();
    void Erase();

public:
    virtual void Draw() = 0;

protected:
    Rect mRect;
    Border mBorder;
    Color mColor;
    string mTitle;
};

class Basic : public Widget
{
public:
    Basic(void);
    ~Basic(void);

public:
    void SetText(string text);

public:
    void Draw() override;

private:
    string mText;
    bool mIsWrap;
};

class Input : public Widget
{
public:
    void Draw() override;
};

class Menu : public Widget
{
public:
    void Draw() override;
};