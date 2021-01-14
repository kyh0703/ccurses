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
    if (_text.empty())
        return;

    Rect rect = GetRect();
    Pos pos(rect.y + 1, rect.x + 1);

    for (size_t idx = 0; idx < _text.size(); ++idx)
    {
        bool isEol = (_text[idx] == '\n');
        if (isEol || rect.w <= pos.x)
        {
            pos.y++;
            pos.x = rect.x + 1;
            if (isEol)
                continue;
        }

        if (rect.h <= pos.y)
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
    if (_text.empty())
        return;

    Rect rect = GetRect();
    Pos pos(rect.y + 1, rect.x + 1);

    for (size_t idx = 0; idx < _text.size(); ++idx)
    {
        if (_rect.x + _rect.w <= pos.x)
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

TabPane::TabPane()
{
    _activeIdx = 0;
    _active = th::Get()._tab._active;
    _inactive = th::Get()._tab._inactive;
}

TabPane::~TabPane()
{
}

void TabPane::ForcusLeft()
{
    if (0 < _activeIdx)
        _activeIdx--;
}

void TabPane::ForcusRight()
{
    if (_activeIdx < (int)(_tabs.size() - 1))
        _activeIdx++;
}

void TabPane::Draw()
{
    if (_tabs.empty())
        return;

    Rect rect = GetRect();
    Pos pos(rect.y + 1, rect.x + 1);

    for (size_t tabIdx = 0; tabIdx < _tabs.size(); ++tabIdx)
    {
        string text(_tabs[tabIdx]);
        for (size_t idx = 0; idx < text.size(); ++idx)
        {
            if (_rect.x + _rect.w <= pos.x)
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

Tab::Tab()
{
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
    if (_tabs.empty())
        return;

    Rect rect = GetRect();
    Pos pos(rect.y, rect.x);

    for (size_t tabIdx = 0; tabIdx < _tabs.size(); ++tabIdx)
    {
        string text(_tabs[tabIdx]);
        Button btn;
        btn.SetRect(rect.h, text.size() + 1, pos.y, pos.x);
        btn._text = text;
        btn._active = th::Get()._tab._active;
        btn._inactive = th::Get()._tab._inactive;
        btn._isActive = (_activeIdx == (int)tabIdx);
        btn.Draw();
        AttachCells(btn.GetCells());
        Rect r = btn.GetRect();
        pos.x = r.w + r.x;
        AddCh(pos.y + 1, pos.x, ACS_VLINE);
    }
}

List::List()
{
}

List::~List()
{
}

void List::ScrollUp()
{
    if (0 < _activeIdx)
        _activeIdx--;
}

void List::ScrollDown()
{
    if (_activeIdx < (int)(_rows.size() - 1))
        _activeIdx++;
}

void List::Draw()
{
    if (_rows.empty())
        return;

    Rect rect = GetRect();
    Pos pos(rect.y, rect.x);

    for (size_t itemIdx = 0; itemIdx < _rows.size(); ++itemIdx)
    {
        string text(_rows[itemIdx]);
        Button btn;
        btn.SetRect(2, rect.w, pos.y, pos.x);
        btn._text = text;
        btn._active = th::Get()._menu._active;
        btn._inactive = th::Get()._menu._inactive;
        btn._isActive = (_activeIdx == (int)itemIdx);
        btn.Draw();
        AttachCells(btn.GetCells());
        if (btn._isActive)
            AddCh(pos.y + 1, rect.w + rect.x - 1, ACS_RARROW);
        pos.y += 1;
    }
}
