#pragma once
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
    void SetRect(int h, int w, int x, int y);
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
