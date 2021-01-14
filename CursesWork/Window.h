#pragma once
#include "Attribute.h"
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

public:
    static void Log(const char *format, ...);

public:
    Rect GetRect();
    void SetRect(int h, int w, int y, int x);
    void SetColor(int bg, int fg);
    void SetTitle(string title);
    const map<Pos, Rune> &GetCells(void);
    void AttachCells(map<Pos, Rune> cells);
    void DrawBase();
    void Erase();
    void Print();

public:
    virtual void Draw() = 0;

protected:
    void HLine(int y, int x, int n, Rune c);
    void VLine(int y, int x, int n, Rune c);
    void AddCh(int y, int x, Rune c);
    void AddStr(int y, int x, string s);
    void GetCh(int y, int x, Rune c);
    const string GetStr(int y, int x, int n);

private:
    void InitCell();
    void MakeBorder();
    void MakeTitle();

protected:
    Rect _rect;
    Border _border;
    Color _color;
    string _title;
    map<Pos, Rune> _cells;
};
