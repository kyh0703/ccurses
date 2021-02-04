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

class Window
{
public:
    Window();
    virtual ~Window();

    static void Log(const char *format, ...);

    void SetBox(bool isBox);
    Rect GetWinRect(void);
    void SetRect(int h, int w, int y, int x);
    void SetColor(int bg, int fg);
    void SetTitle(string title);

    const map<Pos, Rune> &GetCells(void);
    void AttachCells(map<Pos, Rune> cells);
    void Erase();
    void Print();
    void BindKeyEvent(function<void(int)> keyEvent);
    bool HasKeyEvent(void);
    void KeyEvent(int ch);
    virtual void Draw() = 0;
    void Render();

protected:
    void VLine(int y, int x, int n, Rune c);
    void AddCh(int y, int x, Rune r);
    void AddCh(int y, int x, Style s, chtype c);
    void AddStr(int y, int x, string s);
    const Rune GetCh(int y, int x);
    const string GetStr(int y, int x, int n);
    void DrawBase();

protected:
    bool _isBox;
    Rect _rect, _wrect, _winner;
    Border _border;
    Color _color;
    int _titleColor;
    string _title;
    function<void(int)> _keyEvent;
    map<Pos, Rune> _cells;
    WINDOW *_pWin;
};
