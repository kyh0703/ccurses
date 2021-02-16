#pragma once
#include <ncursesw/curses.h>
#include <wctype.h>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include "Window.h"
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

    Style _style;
    wstring _text;
};

class Button : public Widget
{
public:
    Button();
    ~Button();

    void Draw() override;

    wstring _text;
    Style _active;
    Style _inactive;

private:
    void KeyDefault(KeyboardArgs args);
};

class Input : public Widget
{
public:
    Input();
    ~Input();

    const string GetText();
    void SetText(string s);

    void Draw() override;

    Style _active;
    Style _inactive;
    vector<wchar_t> _text;

private:
    void AddText(int ch);
    void DelText();
    void ClearText();
    void KeyDefault(KeyboardArgs args);
};

class Tab : public Widget
{
public:
    Tab();
    ~Tab();

    void FocusLeft();
    void FocusRight();
    void Draw() override;

    Style _active;
    Style _inactive;
    int _active_index;
    vector<string> _tabs;
};

class TabPage : public Widget
{
public:
    TabPage();
    ~TabPage();

    void Add(Widget *widget);
    void Del(Widget *widget);
    void Draw() override;

    vector<Widget *> _tab_items;
};

class Panel : public Widget
{
public:
    Panel();
    ~Panel();


    void Draw();
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

    Style _active;
    Style _inactive;
    int _currow;
    int _toprow;
    vector<string> _rows;

private:
    void KeyDefault(KeyboardArgs args);
};

class ProgressBar : public Widget
{
public:
    ProgressBar();
    ~ProgressBar();

    void Draw() override;

    Style _label_style;
    int _bar_color;
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

    int _alignment;
    vector<vector<string>> _rows;
};

class BarChart : public Widget
{
public:
    BarChart();
    ~BarChart();

    void Draw() override;

    int _bar_gap;
    int _bar_width;
    int _max_val;
    int _num_color;
    vector<int> _bar_color;
    vector<Style> _label_style;
    vector<string> _label;
    vector<float> _data;

private:
    Rune GetBarColor(int index);
    Rune GetLabelStyle(int index);
    Rune GetNumberStyle(int index);
};

class Radio : public Widget
{
public:
    Radio();
    ~Radio();

    void Draw() override;

    bool _is_check;
    Style _active;
    Style _inactive;
    string _text;
};

class CheckBox : public Widget
{
public:
    CheckBox();
    ~CheckBox();

    void Draw() override;

    bool _checked;
    Style _active;
    Style _inactive;
    string _text;

private:
    void KeyDefault(KeyboardArgs args);
};