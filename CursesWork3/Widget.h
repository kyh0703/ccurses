#pragma once
#include <ncurses.h>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include "Window.h"
#include "EventHandler.h"
using namespace std;

class Widget : public Window
{
public:
    virtual void Draw() = 0;
};

class TextBox : public Widget
{
public:
    TextBox();
    ~TextBox();

    void Draw() override;

public:
    Style _style;
    string _text;
};

class Button : public Widget
{
public:
    Button();
    ~Button();

    void Draw() override;

public:
    bool _isActive;
    string _text;
    Style _active;
    Style _inactive;
    // function<void(EventType)> e;
};

class Popup : public Widget
{
public:
    Popup();
    ~Popup();

    void Draw() override;

public:
    Style _btnStyle;
    int _textColor;
    string _text;
};

class YesNo : public Widget
{
public:
    YesNo();
    ~YesNo();

    void ForcusLeft();
    void ForcusRight();
    void Draw() override;

public:
    Style _active;
    Style _inactive;
    int _textColor;
    bool _isYes;
    string _text;
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
    int _activeIdx;
    vector<string> _tabs;
};

class List : public Widget
{
public:
    List();
    ~List();

    void ScrollAmount(int amount);
    void ScrollUp();
    void ScrollDown();
    void ScrollPageHalfUp();
    void ScrollPageHalfDown();
    void ScrollPageUp();
    void ScrollPageDown();
    void ScrollTop();
    void ScrollBottom();
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
    };

    Table();
    ~Table();

    void Draw() override;

public:
    int _alignment;
    vector<vector<string>> _rows;
};

class BarChart : public Widget
{
public:
    BarChart();
    ~BarChart();

    void Draw() override;

private:
    Rune GetBarColor(int idx);
    Rune GetLabelStyle(int idx);
    Rune GetNumberStyle(int idx);

public:
    int _barGap;
    int _barWidth;
    int _maxVal;
    int _numColor;
    vector<int> _barColor;
    vector<Style> _labelStyle;
    vector<string> _label;
    vector<float> _data;
};

class Input : public Widget
{
public:
    Input();
    ~Input();

    vector<string> GetItems();
    void Draw() override;

public:
    Style _active;
    Style _inactive;
    int _textGap;
    vector<string> _query;
    vector<string> _default;
    // map<string, Input *> _items;
};
