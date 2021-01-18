#pragma once
#include <ncurses.h>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include "Window.h"

using namespace std;

class Widget : public Window
{
public:
    Widget();
    ~Widget();

    virtual void Draw() = 0;
};

class Basic : public Widget
{
public:
    Basic();
    ~Basic();

    void Draw() override;

public:
    int _textColor;
    string _text;
};

class Button : public Widget
{
public:
    Button();
    ~Button();

    void Draw() override;

private:
    Style _active;
    Style _inactive;
    bool _isActive;
    string _text;
};

class Input : public Widget
{
public:
    Input();
    ~Input();

    void ClearText();
    void DelText();
    void AddText(chtype c);
    const string GetText();
    void Draw() override;

public:
    vector<chtype> _text;
};

class Tab : public Widget
{
public:
    Tab();
    ~Tab();

    void ForcusLeft();
    void ForcusRight();
    void Draw() override;

public:
    Style _activeStyle;
    Style _inactiveStyle;
    vector<string> _tabs;
    int _activeIdx;
};

class List : public Widget
{
public:
    List();
    ~List();

    void ScrollUp();
    void ScrollDown();
    void ScrollPageHalfUp();
    void ScrollPageHalfDown();
    void ScrollPageUp();
    void ScrollPageDown();
    void ScrollTop();
    void ScrollBottom();
    void ScrollAmount(int amount);
    void Draw() override;

public:
    Style _activeStyle;
    Style _inactiveStyle;
    int _curRow;
    int _topRow;
    vector<string> _rows;
};

class ProgressBar : public Widget
{
public:
    ProgressBar();
    ~ProgressBar();

    void Draw() override;

public:
    Style _labelStyle;
    int _barColor;
    bool _refresh;
    int _percent;
    string _label;
};

class Table : public Widget
{
public:
    enum
    {
        CENTER,
        LEFT,
        RIGHT,
    } ALIGNMENT;

public:
    Table();
    ~Table();

    void Draw() override;

public:
    Style _textStyle;
    int _alignment;
    vector<vector<string>> _rows;
};

class BarChart : public Widget
{
public:
    BarChart();
    ~BarChart();

    void Draw() override;

public:
    vector<vector<float>> _data;
    int _barGap;
    int _barWidth;
    int _maxVal;
};