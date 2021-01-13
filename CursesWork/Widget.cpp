#include "Widget.h"

Widget::Widget()
{
}

Widget::~Widget()
{
}

Basic::Basic()
{
    text.clear();
    textColor = COLOR_WHITE;
}

Basic::~Basic()
{
}

void Basic::Draw()
{
    if (text.empty())
        return;

    Rect rect = GetRect();
    Pos pos(rect.y + 1, rect.x + 1);

    for (size_t idx = 0; idx < text.size(); ++idx)
    {
        bool isEol = (text[idx] == '\n');
        if (isEol || rect.w <= pos.x)
        {
            pos.y++;
            pos.x = rect.x + 1;
            if (isEol)
                continue;
        }

        if (rect.h <= pos.y)
            break;

        Rune r(mColor.bg, textColor, text[idx]);
        AddCh(pos.y, pos.x++, r);
    }
}

Button::Button()
{
}

Button::~Button()
{
}

void Button::Draw()
{
    if (text.empty())
        return;

    Rect rect = GetRect();
    Pos pos(rect.y + 1, rect.x + 1);

    for (size_t idx = 0; idx < text.size(); ++idx)
    {
        if (mRect.x + mRect.w <= pos.x)
            return;

        if (IsActive)
        {
            Rune r(active, text[idx]);
            AddCh(pos.y, pos.x++, r);
        }
        else
        {
            Rune r(inactive, text[idx]);
            AddCh(pos.y, pos.x++, r);
        }
    }
}

TabPane::TabPane()
{
}

TabPane::~TabPane()
{
}

void TabPane::ForcusLeft()
{
    if (0 < activeIdx)
        activeIdx--;
}

void TabPane::ForcusRight()
{
    if (activeIdx < (int)(tabs.size() - 1))
        activeIdx++;
}

void TabPane::Draw()
{
    if (tabs.empty())
        return;

    Rect rect = GetRect();
    Pos pos(rect.y + 1, rect.x + 1);

    for (size_t tabIdx = 0; tabIdx < tabs.size(); ++tabIdx)
    {
        string text(tabs[tabIdx]);
        for (size_t idx = 0; idx < text.size(); ++idx)
        {
            if (mRect.x + mRect.w <= pos.x)
                return;

            if (activeIdx == (int)tabIdx)
            {
                Rune r(active, text[idx]);
                AddCh(pos.y, pos.x++, r);
            }
            else
            {
                Rune r(inactive, text[idx]);
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
    if (0 < activeIdx)
        activeIdx--;
}

void Tab::ForcusRight()
{
    if (activeIdx < (int)(tabs.size() - 1))
        activeIdx++;
}

void Tab::Draw()
{
    if (tabs.empty())
        return;

    Rect rect = GetRect();
    Pos pos(rect.y, rect.x);

    for (size_t tabIdx = 0; tabIdx < tabs.size(); ++tabIdx)
    {
        string text(tabs[tabIdx]);
        Button btn;
        btn.SetRect(rect.h, text.size() + 1, pos.x, pos.y);
        btn.text = text;
        btn.active = {COLOR_WHITE, COLOR_BLUE, A_BOLD};
        btn.inactive = {COLOR_BLACK, COLOR_WHITE};
        btn.IsActive = (activeIdx == (int)tabIdx);
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

void Menu::Draw()
{
}

void Input::Draw()
{
}