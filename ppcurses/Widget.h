#pragma once
#include "FormUtil.h"
#include "Window.h"
#include <algorithm>
#include <map>
#include <ncursesw/curses.h>
#include <string>
#include <vector>
#include <wctype.h>
using namespace std;

class Widget : public Window
{
public:
    virtual void Draw() = 0;
};

class TextBox : public Widget
{
public:
    explicit TextBox(int h, int w, int y, int x);
    virtual ~TextBox();

    inline const Style GetStyle() { return _style; }
    inline const wstring GetText() { return _text; }

    inline void SetStyle(Style style) { _style = style; }
    inline void SetText(wstring text) { _text = text; }

    void Draw() override;

private:
    Style _style;
    wstring _text;
};

class Button : public Widget
{
public:
    explicit Button(int h, int w, int y, int x);
    virtual ~Button();

    inline const wstring GetText() { return _text; }
    inline const Style GetActiveStyle() { return _active_style; }
    inline const Style GetInactiveStyle() { return _inactive_style; }

    inline void SetText(wstring text) { _text = text; }
    inline void SetActiveStyle(Style active_style) { _active_style = active_style; }
    inline void SetInactiveStyle(Style inactive_style) { _inactive_style = inactive_style; }

    void Draw() override;

private:
    void KeyDefault(KeyboardArgs args);

    wstring _text;
    Style _active_style;
    Style _inactive_style;
};

class Input : public Widget
{
public:
    explicit Input(int h, int w, int y, int x);
    virtual ~Input();

    inline const Style GetActiveStyle() { return _active_style; }
    inline const Style GetInactiveStyle() { return _inactive_style; }

    inline void SetActiveStyle(Style active_style) { _active_style = active_style; }
    inline void SetInactiveStyle(Style inactive_style) { _inactive_style = inactive_style; }

    const wstring GetText();
    void SetText(wstring s);
    void AddStr(wstring wstr);
    void AddText(wint_t wch);
    void DelText();
    void ClearText();
    void Draw() override;

private:
    void KeyDefault(KeyboardArgs args);

    Style _active_style;
    Style _inactive_style;
    vector<wchar_t> _text;
};

class Tab : public Widget
{
public:
    explicit Tab(int h, int w, int y, int x);
    virtual ~Tab();

    inline const Style GetActiveStyle() { return _active_style; }
    inline const Style GetInactiveStyle() { return _inactive_style; }
    inline const int GetActiveIndex() { return _active_index; }
    const vector<wstring> GetTabs() { return _tabs; }

    inline void SetActiveStyle(Style active_style) { _active_style = active_style; }
    inline void SetInactiveStyle(Style inactive_style) { _inactive_style = inactive_style; }
    inline void SetActiveIndex(int active_index) { _active_index = active_index; }
    inline void SetTabs(vector<wstring> tabs) { _tabs = tabs; }

    bool GetTab(int index, wstring &tab);
    bool SetTab(int index, wstring tab);
    void FocusLeft();
    void FocusRight();
    void Draw() override;

private:
    Style _active_style;
    Style _inactive_style;
    int _active_index;
    vector<wstring> _tabs;
};

class List : public Widget
{
public:
    explicit List(int h, int w, int y, int x);
    virtual ~List();

    inline const Style GetActiveStyle() { return _active_style; }
    inline const Style GetInactiveStyle() { return _inactive_style; }
    inline const int GetCurRow() { return _cur_row; }
    inline vector<wstring> GetRows() { return _rows; }

    inline void SetActiveStyle(Style active_style) { _active_style = active_style; }
    inline void SetInactiveStyle(Style inactive_style) { _inactive_style = inactive_style; }
    inline void SetCurRow(int cur_row) { _cur_row = cur_row; }
    inline void SetRows(vector<wstring> rows) { _rows = rows; }

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

private:
    void KeyDefault(KeyboardArgs args);

    Style _active_style;
    Style _inactive_style;
    int _cur_row;
    int _top_row;
    vector<wstring> _rows;
};

class ProgressBar : public Widget
{
public:
    explicit ProgressBar(int h, int w, int y, int x);
    virtual ~ProgressBar();

    inline const Style GetLabelStyle() { return _label_style; }
    inline const int GetBarColor() { return _bar_color; }
    inline const int GetPercent() { return _percent; }
    inline const wstring GetLabel() { return _label; }

    inline void SetLabelStyle(Style label_style) { _label_style = label_style; }
    inline void SetPercent(int percent) { _percent = (100 <= percent ? 100 : percent); }
    inline void SetBarColor(int bar_color) { _bar_color = bar_color; }
    inline void SetLabel(wstring label) { _label = label; }

    void Draw() override;

private:
    Style _label_style;
    int _bar_color;
    int _percent;
    wstring _label;
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

    explicit Table(int h, int w, int y, int x);
    virtual ~Table();

    inline const int GetAligment() { return _alignment; }
    inline const vector<vector<wstring>> GetRows() { return _rows; }

    inline void SetAlignment(int alignment) { _alignment = alignment; }
    inline void SetRows(vector<vector<wstring>> rows) { _rows = rows; }

    void Draw() override;

private:
    int _alignment;
    vector<vector<wstring>> _rows;
};

class BarChart : public Widget
{
public:
    explicit BarChart(int h, int w, int y, int x);
    virtual ~BarChart();

    inline const int GetBarGap() { return _bar_gap; }
    inline const int GetBarWidth() { return _bar_width; }
    inline const int GetMaxVal() { return _max_val; }
    inline const int GetNumColor() { return _num_color; }
    inline vector<int> GetBarColors() { return _bar_colors; }
    inline vector<Style> GetLabelStyles() { return _label_styles; }
    inline vector<wstring> GetLabels() { return _labels; }
    inline vector<float> GetDatas() { return _datas; }

    inline void SetBarGap(int bar_gap) { _bar_gap = bar_gap; }
    inline void SetBarWidth(int bar_width) { _bar_width = bar_width; }
    inline void SetMaxVal(int max_val) { _max_val = max_val; }
    inline void SetNumColor(int num_color) { _num_color = num_color; }
    inline void SetBarColors(vector<int> bar_colors) { _bar_colors = bar_colors; }
    inline void SetLabelStyles(vector<Style> label_styles) { _label_styles = label_styles; }
    inline void SetLabels(vector<wstring> labels) { _labels = labels; }
    inline void SetDatas(vector<float> datas) { _datas = datas; }

    void Draw() override;

private:
    Rune GetBarColor(int index);
    Rune GetLabelStyle(int index);
    Rune GetNumberStyle(int index);

    int _bar_gap;
    int _bar_width;
    int _max_val;
    int _num_color;
    vector<int> _bar_colors;
    vector<Style> _label_styles;
    vector<wstring> _labels;
    vector<float> _datas;
};

// TODO 라디오 버튼 그룹 필요
class Radio : public Widget
{
public:
    explicit Radio(int h, int w, int y, int x);
    virtual ~Radio();

    inline const bool GetChecked() { return _checked; }
    inline const Style GetStyle() { return _style; }
    inline const wstring GetText() { return _text; }

    inline void SetChecked(bool checked) { _checked = checked; }
    inline void SetStyle(Style style) { _style = style; }
    inline void SetText(wstring text) { _text = text; }

    void Draw() override;

private:
    bool _checked;
    Style _style;
    wstring _text;
};

class CheckBox : public Widget
{
public:
    explicit CheckBox(int h, int w, int y, int x);
    virtual ~CheckBox();

    inline const bool GetChecked() { return _checked; }
    inline const Style GetStyle() { return _style; }
    inline const wstring GetText() { return _text; }

    inline void SetChecked(bool checked) { _checked = checked; }
    inline void SetStyle(Style style) { _style = style; }
    inline void SetText(wstring text) { _text = text; }

    void Draw() override;

private:
    void KeyDefault(KeyboardArgs args);

    bool _checked;
    Style _style;
    wstring _text;
};