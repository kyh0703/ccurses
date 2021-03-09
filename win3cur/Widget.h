#pragma once
#include <ncursesw/curses.h>
#include <wctype.h>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include "Util.h"
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
    Style _active_style;
    Style _inactive_style;

private:
    void KeyDefault(KeyboardArgs args);
};

class Input : public Widget
{
public:
    Input();
    ~Input();

    const wstring GetText();
    void SetText(wstring s);
    void AddStr(wstring wstr);
    void AddText(wint_t wch);
    void DelText();
    void ClearText();

    void Draw() override;

    Style _active_style;
    Style _inactive_style;
    vector<wchar_t> _text;

private:
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

    Style _active_style;
    Style _inactive_style;
    int _active_index;
    vector<wstring> _tabs;
};

class List : public Widget
{
public:
    List();
    ~List();

    wstring GetCurrentRow();
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

    Style _active_style;
    Style _inactive_style;
    int _currow;
    int _toprow;
    vector<wstring> _rows;

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
    vector<vector<wstring>> _rows;
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
    Style _style;
    wstring _text;

private:
    void KeyDefault(KeyboardArgs args);
};