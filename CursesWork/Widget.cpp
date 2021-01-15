#include "Widget.h"
#include "Theme.h"

Widget::Widget()
{
}

Widget::~Widget()
{
}

Basic::Basic()
{
    _textColor = th::Get()._basic;
    _text.clear();
}

Basic::~Basic()
{
}

void Basic::Draw()
{
    Pos pos(_inner.min.y, _inner.min.x);

    for (size_t idx = 0; idx < _text.size(); ++idx)
    {
        bool isEol = (_text[idx] == '\n');
        if (isEol || _inner.max.x < pos.x)
        {
            pos.y++;
            pos.x = _inner.min.x;
            if (isEol)
                continue;
        }

        if (_inner.max.y < pos.y)
            break;

        int bg = th::Get()._default.bg;
        Rune r(bg, _textColor, _text[idx]);
        AddCh(pos.y, pos.x++, r);
    }
}

Button::Button()
{
    _active = th::Get()._btn._active;
    _inactive = th::Get()._btn._inactive;
    _isActive = false;
}

Button::~Button()
{
}

void Button::Draw()
{
    Pos pos(_inner.min.y, _inner.min.x);

    for (size_t idx = 0; idx < _text.size(); ++idx)
    {
        if (_inner.max.x < pos.x)
            return;

        if (_isActive)
        {
            Rune r(_active, _text[idx]);
            AddCh(pos.y, pos.x++, r);
        }
        else
        {
            Rune r(_inactive, _text[idx]);
            AddCh(pos.y, pos.x++, r);
        }
    }
}

Input::Input()
{
    _activeStyle = th::Get()._btn._active;
    _inactiveStyle = th::Get()._btn._inactive;
    _isActive = false;
}

Input::~Input()
{
}

void Input::Draw()
{
    Pos pos(_rect.min.y, _rect.min.x);

    // for (int x = _rect.min.x; x < _rect.max.x + _rect.y; ++x)
    // {
    //     AddCh(pos.y, x, ' ');
    //     if (_isActive)
    //     {
    //         Rune r(_activeStyle, ACS_S1);
    //         AddCh(pos.y + 1, x, r);
    //     }
    //     else
    //     {
    //         Rune r(_inactiveStyle, ACS_S1);
    //         AddCh(pos.y + 1, x, r);
    //     }
    // }
}

Tab::Tab()
{
    _activeStyle = th::Get()._tab._active;
    _inactiveStyle = th::Get()._tab._inactive;
    _activeIdx = 0;
}

Tab::~Tab()
{
}

void Tab::ForcusLeft()
{
    if (0 < _activeIdx)
        _activeIdx--;
}

void Tab::ForcusRight()
{
    if (_activeIdx < (int)(_tabs.size() - 1))
        _activeIdx++;
}

void Tab::Draw()
{
    Pos pos(_inner.min.y, _inner.min.x);

    for (size_t tabIdx = 0; tabIdx < _tabs.size(); ++tabIdx)
    {
        string text(_tabs[tabIdx]);
        for (size_t idx = 0; idx < text.size(); ++idx)
        {
            if (_inner.max.x < pos.x)
                return;

            Style style;
            if (_activeIdx == (int)tabIdx)
                style = _activeStyle;
            else
                style = _inactiveStyle;

            Rune r(style, text[idx]);
            AddCh(pos.y, pos.x++, r);
        }
        AddCh(pos.y, pos.x++, ACS_VLINE);
    }
}

List::List()
{
    _activeStyle = th::Get()._list._active;
    _inactiveStyle = th::Get()._list._inactive;
    _curRow = 0;
    _topRow = 0;
}

List::~List()
{
}

void List::ScrollUp()
{
    ScrollAmount(-1);
}

void List::ScrollDown()
{
    ScrollAmount(1);
}

void List::ScrollPageUp()
{
    if (_topRow < _curRow)
        _curRow = _topRow;
    else
        ScrollAmount(-_inner.h);
}

void List::ScrollPageDown()
{
    ScrollAmount(_inner.h);
}

void List::ScrollTop()
{
    _curRow = 0;
}

void List::ScrollBottom()
{
    _curRow = _rows.size() - 1;
}

void List::ScrollAmount(int amount)
{
    if ((int)_rows.size() - _curRow <= amount)
        _curRow = _rows.size() - 1;
    else if (_curRow + amount < 0)
        _curRow = 0;
    else
        _curRow += amount;
}

void List::Draw()
{
    Pos pos(_inner.min.y, _inner.min.x);

    if (_inner.h + _topRow <= _curRow)
        _topRow = _curRow - _inner.h + 1;
    else if (_curRow < _topRow)
        _topRow = _curRow;

    for (size_t rowIdx = _topRow; rowIdx < _rows.size(); ++rowIdx)
    {
        string text(_rows[rowIdx]);
        for (size_t idx = 0; idx < text.size(); ++idx)
        {
            if (_inner.max.x < pos.x)
                break;

            Style style;
            if ((int)rowIdx == _curRow)
                style = _activeStyle;
            else
                style = _inactiveStyle;

            Rune r(style, text[idx]);
            AddCh(pos.y, pos.x++, r);
        }

        pos.x = _inner.min.x;
        pos.y++;
        if (_inner.max.y < pos.y)
            break;
    }

    if (0 < _topRow)
    {
        Rune r(ACS_DIAMOND);
        AddCh(_inner.min.y, _inner.max.x, r);
    }

    if (_topRow + _inner.h < (int)_rows.size())
    {
        Rune r(ACS_DIAMOND);
        AddCh(_inner.max.y, _inner.max.x, r);
    }
}

Progress::Progress()
{
    _barStyle = th::Get()._tab._active;
    _labelStyle = th::Get()._tab._inactive;
    _percent = 0;
}

Progress::~Progress()
{
}

void Progress::Draw()
{
    Pos pos(_inner.min.y, _inner.min.x);

    if (_label.empty())
        _label = to_string(_percent);

    int barWidth = int(float(_percent * 0.01) * _inner.w);
    Rune r(_barStyle, ACS_RARROW);
    HLine(_inner.min.y, _inner.min.x, barWidth, r);
}

Table::Table()
{
    _alignment = LEFT;
}

Table::~Table()
{
}

void Table::Draw()
{
    Pos pos(_inner.min.y, _inner.min.x);

    int columnCnt = _rows[0].size();
    int columnWidth = _inner.w / columnCnt;

    for (size_t line = 0; line < _rows.size(); ++line)
    {
        vector<string> row(_rows[line]);
        for (size_t col = 0; col < row.size(); ++col)
        {
            string column(row[col]);
            if (_alignment == LEFT)
                pos.x = _inner.min.x;
            else if (_alignment == CENTER)
                pos.x = (columnWidth - column.length()) / 2;
            else if (_alignment == RIGHT)
                pos.x = (_inner.min.x + col * columnWidth) - column.length();

            for (size_t textIdx = 0; textIdx < column.size(); ++textIdx)
                AddCh(pos.y, pos.x++, column[textIdx]);
        }
    }
}