#pragma once
#include <ncurses.h>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include "Window.h"
using namespace std;

enum
{
    TEXTBOX,
    BUTTON,
    POPUP,
    YESNO,
    INPUT,
    TAB,
    LIST,
    PROGRESSBAR,
    TABLE,
    BARCHART,
    RADIO,
    CHECKBOX,
};

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
    string _text;
};

class Button : public Widget
{
public:
    Button();
    ~Button();

    void Draw() override;

    string _text;
    Style _active;
    Style _inactive;
};

class Popup : public Widget
{
public:
    Popup();
    ~Popup();

    void Draw() override;

    Style _button_style;
    int _text_color;
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

    Style _active;
    Style _inactive;
    int _text_color;
    bool _is_yes;
    string _text;
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
    vector<chtype> _text;

private:
    void AddText(chtype c);
    void DelText();
    void ClearText();
    void KeyDefault(KeyboardArgs args);
};

class Tab : public Widget
{
public:
    Tab();
    ~Tab();

    void ForcusLeft();
    void ForcusRight();
    void Draw() override;

    Style _active;
    Style _inactive;
    int _active_index;
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

    Style _active;
    Style _inactive;
    int _currow;
    int _toprow;
    vector<string> _rows;
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

    bool _is_check;
    Style _active;
    Style _inactive;
    string _text;
};