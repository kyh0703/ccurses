#pragma once
#include <iostream>
#include <map>
#include <ncurses.h>
#include <sstream>
#include <string>
#include <vector>
#include "Attribute.h"
using namespace std;

class Window
{
public:
    Window();
    virtual ~Window();

    static void Log(const char *format, ...);

    void SetBox(bool isBox);
    void SetRect(int h, int w, int y, int x);
    void SetColor(int bg, int fg);
    void SetTitle(string title);
    const map<Pos, Rune> &GetCells(void);
    void AttachCells(map<Pos, Rune> cells);
    void Erase();
    void Print();

    virtual void Draw() = 0;

protected:
    void HLine(int y, int x, int n, Rune c);
    void VLine(int y, int x, int n, Rune c);
    void AddCh(int y, int x, Rune c);
    void AddStr(int y, int x, string s);
    const Rune GetCh(int y, int x);
    const string GetStr(int y, int x, int n);
    Rect InitCell();
    void DrawBase();
    void EraseBase();
    void MakeBorder();
    void MakeTitle();

protected:
    bool _isBox;
    Rect _rect;
    Rect _inner;
    Border _border;
    Color _color;
    int _titleColor;
    string _title;
    map<Pos, Rune> _cells;
};
