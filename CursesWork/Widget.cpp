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
        if (mRect.x + mRect.w <= pos.x)
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
            if (mRect.x + mRect.w <= pos.x)
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

Menu::Menu()
{
}

Menu::~Menu()
{
}

void Menu::ForcusUp()
{
    if (0 < _activeIdx)
        _activeIdx--;
}

void Menu::ForcusDown()
{
    if (_activeIdx < (int)(_items.size() - 1))
        _activeIdx++;
}

void Menu::Draw()
{
    if (_items.empty())
        return;

    Rect rect = GetRect();
    Pos pos(rect.y, rect.x);

    for (size_t itemIdx = 0; itemIdx < _items.size(); ++itemIdx)
    {
        string text(_items[itemIdx]);
        Button btn;
        btn.SetRect(2, rect.w, pos.y, pos.x);
        btn._text = text;
        btn._active = th::Get()._menu._active;
        btn._inactive = th::Get()._menu._inactive;
        btn._isActive = (_activeIdx == (int)itemIdx);
        btn.Draw();
        AttachCells(btn.GetCells());
        pos.y += 2;
        HLine(pos.y, pos.x + 1, rect.w - 1, ACS_HLINE);
    }
}

void Input::Draw()
{
}