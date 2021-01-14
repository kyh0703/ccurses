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
    _text.clear();
    _textColor = th::Get()._basic;
}

Basic::~Basic()
{
}

void Basic::Draw()
{
    Rect inner = GetInner();
    Pos pos(inner.y, inner.x);

    for (size_t idx = 0; idx < _text.size(); ++idx)
    {
        bool isEol = (_text[idx] == '\n');
        if (isEol || inner.Getwx() < pos.x)
        {
            pos.y++;
            pos.x = inner.x;
            if (isEol)
                continue;
        }

        if (inner.Gethy() < pos.y)
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
    Rect inner = GetInner();
    Pos pos(inner.y, inner.x);

    for (size_t idx = 0; idx < _text.size(); ++idx)
    {
        if (inner.Getwx() < pos.x)
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
    _active = th::Get()._btn._active;
    _inactive = th::Get()._btn._inactive;
    _isActive = false;
}

Input::~Input()
{
}

void Input::Draw()
{
    Rect rect = GetRect();
    Pos pos(rect.y, rect.x);

    for (int col = rect.x; col < rect.x + rect.y; ++col)
    {
        AddCh(pos.y, col, ' ');
        if (_isActive)
        {
            Rune r(_active, ACS_S1);
            AddCh(pos.y + 1, col, r);
        }
        else
        {
            Rune r(_inactive, ACS_S1);
            AddCh(pos.y + 1, col, r);
        }
    }
}

Tab::Tab()
{
    _activeIdx = 0;
    _active = th::Get()._tab._active;
    _inactive = th::Get()._tab._inactive;
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
    Rect inner = GetInner();
    Pos pos(inner.y, inner.x);

    for (size_t tabIdx = 0; tabIdx < _tabs.size(); ++tabIdx)
    {
        string text(_tabs[tabIdx]);
        for (size_t idx = 0; idx < text.size(); ++idx)
        {
            if (inner.Getwx() < pos.x)
                return;

            if (_activeIdx == (int)tabIdx)
            {
                Rune r(_active, text[idx]);
                AddCh(pos.y, pos.x++, r);
            }
            else
            {
                Rune r(_inactive, text[idx]);
                AddCh(pos.y, pos.x++, r);
            }
        }
        AddCh(pos.y, pos.x++, ACS_VLINE);
    }
}

List::List()
{
    _curRow = 0;
    _topRow = 0;
    _active = th::Get()._list._active;
    _inactive = th::Get()._list._inactive;
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
    ScrollAmount(_rect.h - 2);
}

void List::ScrollPageDown()
{
    if (_topRow < _curRow)
        _curRow = _topRow;
    else
        ScrollAmount(_rect.h - 2);
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
    Rect inner = GetInner();
    Pos pos(inner.y, inner.x);

    if (inner.h + _topRow <= _curRow)
        _topRow = _curRow - inner.h;
    else if (_curRow < _topRow)
        _topRow = _curRow;

    for (size_t rowIdx = _topRow; rowIdx < _rows.size(); ++rowIdx)
    {
        string text(_rows[rowIdx]);
        for (size_t idx = 0; idx < text.size(); ++idx)
        {
            if (inner.Getwx() < pos.x)
                break;

            Style style;
            if ((int)rowIdx == _curRow)
                style = _active;
            else
                style = _inactive;

            Rune r(style, text[idx]);
            AddCh(pos.y, pos.x++, r);
        }

        pos.y++;
        pos.x = inner.x;
        if (inner.Gethy() < pos.y)
            break;
    }

    if (0 < _topRow)
    {
        Rune r(ACS_DIAMOND);
        AddCh(inner.y, inner.Getwx(), r);
    }

    if (_topRow + inner.h < (int)_rows.size() - 1)
    {
        Rune r(ACS_DIAMOND);
        AddCh(inner.Gethy(), inner.Getwx(), r);
    }
}
