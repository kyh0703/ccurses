#include "Widget.h"

Widget::Widget()
{
}

Widget::~Widget()
{
}

Basic::Basic()
{
    mIsWrap = true;
    mText.clear();
}

Basic::~Basic()
{
}

void Basic::SetText(string text)
{
    mText = text;
}

void Basic::Draw()
{
    DrawBase();
    CellPrint();
    // if (mText.empty())
    //     return;

    // Rect rect = GetRect();
    // Pos pos(rect.y + 1, rect.x + 1);

    // for (size_t idx = 0; idx < mText.size(); ++idx)
    // {
    //     if (mText[idx] == '\n' || rect.w <= pos.x)
    //     {
    //         pos.y++;
    //         pos.x = rect.x + 1;
    //     }

    //     if (rect.h <= pos.y)
    //         break;

    //     mvaddch(pos.y, pos.x++, mText[idx]);
    // }
    refresh();
}

void Input::Draw()
{
}