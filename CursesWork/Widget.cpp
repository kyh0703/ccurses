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
    _active = th::Get()._btn.active;
    _inactive = th::Get()._btn.inactive;
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
    _activeStyle = th::Get()._btn.active;
    _inactiveStyle = th::Get()._btn.inactive;
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
    _activeStyle = th::Get()._tab.active;
    _inactiveStyle = th::Get()._tab.inactive;
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
    _activeStyle = th::Get()._list.active;
    _inactiveStyle = th::Get()._list.inactive;
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

ProgressBar::ProgressBar()
{
    _barColor = th::Get()._progress.bar;
    _labelStyle = th::Get()._progress.label;
    _percent = 0;
}

ProgressBar::~ProgressBar()
{
}

void ProgressBar::Draw()
{
    Pos pos(_inner.min.y, _inner.min.x);

    if (_label.empty())
        _label = to_string(_percent) + "%";

    int barWidth = int(float(_percent * 0.01) * _inner.w);
    while (pos.y <= _inner.max.y)
    {
        Rune r(_barColor, _barColor, ' ');
        HLine(pos.y, pos.x, barWidth, r);
        pos.y++;
    }

    pos.y = _inner.min.y + ((_inner.h) / 2);
    pos.x = _inner.min.x + (_inner.w / 2) - _label.length();
    if (_inner.max.y < pos.y)
        return;

    for (size_t idx = 0; idx < _label.size(); ++idx)
    {
        // if (pos.x + idx + 1 <= _inner.max.x + barWidth)
        // {

        // }
        Rune r(COLOR_BLUE, COLOR_RED,_label[idx]);
        AddCh(pos.y, pos.x++, _label[idx]);
    }
}

Table::Table()
{
    _alignment = CENTER;
}

Table::~Table()
{
}

void Table::Draw()
{
    Pos pos(_inner.min.y, _inner.min.x);

    int colCnt = _rows[0].size();
    int colWidth = _inner.w / colCnt;

    for (size_t row = 0; row < _rows.size(); ++row)
    {
        vector<string> cols(_rows[row]);
        for (size_t col = 0; col < cols.size(); ++col)
        {
            string text(cols[col]);
            if (colWidth < (int)text.length() || _alignment == LEFT)
                pos.x = _inner.min.x + (col * colWidth);
            else if (_alignment == CENTER)
                pos.x += (colWidth - text.length()) / 2;
            else if (_alignment == RIGHT)
            {
                if (pos.x + colWidth < _inner.max.x)
                    pos.x += colWidth - text.length();
                else
                    pos.x = _inner.max.x - text.length() + 1;
            }

            int oneColMax = (_inner.min.x + (colWidth * (col + 1)));
            for (size_t strIdx = 0; pos.x < oneColMax; ++pos.x)
            {
                if (text[strIdx] == 0x00)
                    continue;
                AddCh(pos.y, pos.x, text[strIdx++]);
            }

            if (col != cols.size() - 1)
                AddCh(pos.y, pos.x - 1, ACS_VLINE);
            else
                pos.y++;
        }

        if (_inner.max.y < pos.y)
            break;

        for (int x = _inner.min.x; x <= _inner.max.x; ++x)
            AddCh(pos.y, x, ACS_S3);

        pos.y++;
        pos.x = _inner.min.x;
    }
}