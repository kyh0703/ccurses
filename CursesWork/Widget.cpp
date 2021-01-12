#include "Paint.h"
#include "Widget.h"

Widget::Widget()
{
    mRect.h = 0;
    mRect.w = 0;
    mRect.x = 0;
    mRect.y = 0;
    mBorder.ls = ACS_VLINE;
    mBorder.rs = ACS_VLINE;
    mBorder.ts = ACS_HLINE;
    mBorder.bs = ACS_HLINE;
    mBorder.tl = ACS_ULCORNER;
    mBorder.tr = ACS_URCORNER;
    mBorder.bl = ACS_LLCORNER;
    mBorder.br = ACS_LRCORNER;
    mColor.fg = COLOR_WHITE;
    mColor.bg = COLOR_BLACK;
}

Widget::~Widget()
{
}

void Widget::Log(const char *format, ...)
{
    char line[1024], *pPos;
    memset(line, 0x00, sizeof(line));
    pPos = line;
    int size = sprintf(pPos, "DEBUG > ");

    va_list Marker;
    va_start(Marker, format);
    vsnprintf(line, sizeof(line) - size, format, Marker);
    va_end(Marker);
    mvaddstr(LINES - 1, 0, line);
}

Rect Widget::GetRect()
{
    return mRect;
}

void Widget::SetRect(short h, short w, short x, short y)
{
    mRect.h = h;
    mRect.w = w;
    mRect.x = x;
    mRect.y = y;
}

void Widget::SetColor(short bg, short fg)
{
    mColor.bg = bg;
    mColor.fg = fg;
}

void Widget::SetTitle(string title)
{
    mTitle = title;
}

void Widget::DrawBase()
{
    short idx = Paint::Get().FindIndex(mColor.fg, mColor.bg);
    attron(COLOR_PAIR(idx));
    mvaddch(mRect.y, mRect.x, mBorder.tl);
    mvaddch(mRect.y, mRect.x + mRect.w, mBorder.tr);
    mvaddch(mRect.y + mRect.h, mRect.x, mBorder.bl);
    mvaddch(mRect.y + mRect.h, mRect.x + mRect.w, mBorder.br);
    mvhline(mRect.y, mRect.x + 1, mBorder.ts, mRect.w - 1);
    mvhline(mRect.y + mRect.h, mRect.x + 1, mBorder.bs, mRect.w - 1);
    mvvline(mRect.y + 1, mRect.x, mBorder.ls, mRect.h - 1);
    mvvline(mRect.y + 1, mRect.x + mRect.w, mBorder.rs, mRect.h - 1);
    attroff(COLOR_PAIR(idx));

    if (!mTitle.empty())
        mvaddnstr(mRect.y, mRect.x + 2, mTitle.c_str(), mTitle.size());
    refresh();
}

void Widget::Erase()
{
    for (int i = mRect.y; i <= mRect.h + mRect.y; ++i)
    {
        for (int j = mRect.x; j <= mRect.x + mRect.w; ++j)
            mvdelch(i, j);
    }
    refresh();
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
    if (mText.empty())
        return;

    Rect rect = GetRect();
    Pos pos(rect.y + 1, rect.x + 1);

    for (size_t idx = 0; idx < mText.size(); ++idx)
    {
        if (mText[idx] == '\n' || rect.w <= pos.x)
        {
            pos.y++;
            pos.x = rect.x + 1;
        }

        if (rect.h <= pos.y)
            break;

        mvaddch(pos.y, pos.x++, mText[idx]);
    }
    refresh();
}

void Input::Draw()
{
}