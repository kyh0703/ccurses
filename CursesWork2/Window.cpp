#include "Paint.h"
#include "Window.h"

Window::Window()
{

    mColor.fg = COLOR_WHITE;
    mColor.bg = COLOR_BLACK;
}

Window::~Window()
{
}

void Window::Log(const char *format, ...)
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

Rect Window::GetRect()
{
    return mRect;
}

void Window::SetRect(int h, int w, int x, int y)
{
    mRect.h = h;
    mRect.w = w;
    mRect.x = x;
    mRect.y = y;
}

void Window::SetColor(int bg, int fg)
{
    mColor.bg = bg;
    mColor.fg = fg;
}

void Window::SetTitle(string title)
{
    mTitle = title;
}

void Window::DrawBase()
{
    InitCell();
    MakeBorder();
    MakeTitle();
    // if (!mTitle.empty())
    //     mvaddnstr(mRect.y, mRect.x + 2, mTitle.c_str(), mTitle.size());
    // refresh();
}

void Window::Erase()
{
    for (int i = mRect.y; i <= mRect.h + mRect.y; ++i)
    {
        for (int j = mRect.x; j <= mRect.x + mRect.w; ++j)
            mvdelch(i, j);
    }
    refresh();
}

void Window::HLine(int y, int x, int n, Rune c)
{
    for (int cols = x; cols <= n; ++cols)
        mCells[{y, cols}] = c;
}

void Window::VLine(int y, int x, int n, Rune c)
{
    for (int line = y; line <= n; ++line)
        mCells[{line, x}] = c;
}

void Window::AddStr(int y, int x, string s)
{
    for (size_t idx = 0; idx < s.size(); idx++)
        mCells[{y, x++}] = {mColor.bg, COLOR_WHITE, s[idx]};
}

void Window::CellPrint()
{
    for (int line = mRect.y; line <= mRect.h + mRect.y; ++line)
    {
        for (int col = mRect.x; col <= mRect.x + mRect.w; ++col)
        {
            Rune rune = mCells[{line, col}];
            int idx = Paint::Get().FindIndex(rune.fg, rune.bg);
            attron(COLOR_PAIR(idx));
            mvaddch(line, col, rune.c);
            attroff(COLOR_PAIR(idx));
        }
    }
}

void Window::InitCell()
{
    for (int line = mRect.y; line <= mRect.h + mRect.y; ++line)
        for (int col = mRect.x; col <= mRect.x + mRect.w; ++col)
            mCells[{line, col}] = {mColor.bg, mColor.bg, ' '};
}

void Window::MakeBorder()
{
    mCells[{mRect.y, mRect.x}] = {mColor.bg, mColor.fg, mBorder.tl};
    mCells[{mRect.y, mRect.x + mRect.w}] = {mColor.bg, mColor.fg, mBorder.tr};
    mCells[{mRect.y + mRect.h, mRect.x}] = { mColor.bg, mColor.fg, mBorder.bl};
    mCells[{mRect.y + mRect.h, mRect.x + mRect.w}] = { mColor.bg, mColor.fg, mBorder.br};
    HLine(mRect.y, mRect.x + 1, mRect.w - 1, {mColor.bg, mColor.fg, mBorder.ts});
    HLine(mRect.y + mRect.h, mRect.x + 1, mRect.w - 1, {mColor.bg, mColor.fg, mBorder.bs});
    VLine(mRect.y + 1, mRect.x, mRect.h - 1, {mColor.bg, mColor.fg, mBorder.ls});
    VLine(mRect.y + 1, mRect.x + mRect.w, mRect.h - 1, {mColor.bg, mColor.fg, mBorder.rs});
}

void Window::MakeTitle()
{
    AddStr(mRect.y, mRect.x + 2, mTitle);
}