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
    virtual void Draw() = 0;
};

class TextBox : public Widget
{
public:
    TextBox();
    ~TextBox();

    void SetStyle(Style style);
    void SetText(string text);
    void Draw() override;

private:
    Style _style;
    string _text;
};

class Popup : public Widget
{
public:
    Popup();
    ~Popup();

    void SetBtnStyle(Style button);
    void SetTextColor(int textColor);
    void SetText(string text);
    void Draw() override;

private:
    Style _button;
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
    void SetActiveStyle(Style active);
    void SetInActiveStyle(Style inactive);
    void SetTextColor(int textColor);
    const bool IsYes();
    void SetText(string text);
    void Draw() override;

private:
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
    void SetActiveStyle(Style active);
    void SetInActiveStyle(Style inactive);
    const int GetActive();
    void SetTabs(vector<string> tabs);
    void Draw() override;

private:
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

    void ScrollUp();
    void ScrollDown();
    void ScrollPageHalfUp();
    void ScrollPageHalfDown();
    void ScrollPageUp();
    void ScrollPageDown();
    void ScrollTop();
    void ScrollBottom();
    void SetActiveStyle(Style active);
    void SetInActiveStyle(Style inactive);
    const int GetCurrent();
    void SetRows(vector<string> rows);
    void Draw() override;

private:
    void ScrollAmount(int amount);

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

    void SetLabelStyle(Style label);
    void SetBarColor(int color);
    void SetPercent(int percent);
    void SetLabel(string label);
    void Draw() override;

private:
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

    void SetAlignment(unsigned int alignment);
    void SetRows(vector<vector<string>> rows);
    void Draw() override;

private:
    int _alignment;
    vector<vector<string>> _rows;
};

class BarChart : public Widget
{
public:
    BarChart();
    ~BarChart();

    void SetBarGap(int gap);
    void SetBarWidth(int width);
    void SetMaxVal(int value);
    void SetBarColor(vector<int> barColor);
    void SetLabelStyle(vector<Style> label);
    void SetLabel(vector<string> label);
    void SetData(vector<float> data);
    void Draw() override;

private:
    Rune GetBarColor(int idx);
    Rune GetLabelStyle(int idx);
    Rune GetNumberStyle(int idx);

    int _barGap;
    int _barWidth;
    int _maxVal;
    vector<int> _barColor;
    vector<Style> _labelStyle;
    vector<string> _label;
    vector<float> _data;
};

class Form : public Widget
{
public:
    Form();
    ~Form();

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