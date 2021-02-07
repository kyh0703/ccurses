#pragma once
#include "Attribute.h"
#include <functional>
#include <iostream>
#include <map>
#include <ncurses.h>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

using Event = function<void()>;
using MouseEvent = function<void()>;

class Window
{
public:
    Window();
    virtual ~Window();

    static void Log(const char *format, ...);

    void SetBox(bool isBox);
    Rect GetWinRect(void);
    Rect GetRect();
    void SetRect(int h, int w, int y, int x);
    void SetColor(int bg, int fg);
    void SetTitle(string title);

    void Erase();
    virtual void Draw() = 0;
    void Render();

    Event _clicked;
    MouseEvent _mouseClick;
    MouseEvent _mouseUp;
    MouseEvent _mouseDown;
    MouseEvent _mouseLeave;

protected:
    void AddCh(int y, int x, Rune r);
    void AddCh(int y, int x, Style s, chtype c);
    void AddStr(int y, int x, string s);
    const Rune GetCh(int y, int x);
    const string GetStr(int y, int x, int n);
    void DrawBase();
    void DrawBase(WINDOW *pParent);

    bool _isBox;
    unsigned _type;
    Rect _rect, _wrect, _winner;
    Border _border;
    Color _color;
    int _titleColor;
    string _title;
    WINDOW *_pWin;
};