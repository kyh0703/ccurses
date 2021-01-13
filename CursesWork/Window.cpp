#include "Window.h"
#include "Paint.h"
#include "Theme.h"

Window::Window()
{
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

const map<Pos, Rune> &Window::GetCells(void)
{
    return mCells;
}

void Window::AttachCells(map<Pos, Rune> cells)
{
    map<Pos, Rune>::iterator iter;
    for (iter = cells.begin(); iter != cells.end(); ++iter)
    {
        Pos pos((*iter).first);
        Rune r((*iter).second);
        mCells[pos] = r;
    }
}

void Window::DrawBase()
{
    InitCell();
    MakeBorder();
    MakeTitle();
}

void Window::Erase()
{
    for (int i = mRect.y; i <= mRect.h + mRect.y; ++i)
        for (int j = mRect.x; j <= mRect.x + mRect.w; ++j)
            mvdelch(i, j);
    refresh();
}

void Window::Print()
{
    for (int line = mRect.y; line <= mRect.h + mRect.y; ++line)
    {
        for (int col = mRect.x; col <= mRect.x + mRect.w; ++col)
        {
            Rune rune = mCells[{line, col}];
            int idx = Paint::Get().FindIndex(rune.s.fg, rune.s.bg);
            attron(COLOR_PAIR(idx) | rune.s.opt);
            mvaddch(line, col, rune.c);
            attroff(COLOR_PAIR(idx) | rune.s.opt);
        }
    }
}

void Window::HLine(int y, int x, int n, Rune c)
{
    for (int cols = x; cols < n + x; ++cols)
        mCells[{y, cols}] = c;
}

void Window::VLine(int y, int x, int n, Rune c)
{
    for (int line = y; line < n + y; ++line)
        mCells[{line, x}] = c;
}

void Window::AddCh(int y, int x, Rune c)
{
    mCells[{y, x}] = c;
}

void Window::AddStr(int y, int x, string s)
{
    for (size_t idx = 0; idx < s.size(); idx++)
        mCells[{y, x++}] = {mColor.bg, COLOR_WHITE, (chtype)s[idx]};
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
    mCells[{mRect.y + mRect.h, mRect.x}] = {mColor.bg, mColor.fg, mBorder.bl};
    mCells[{mRect.y + mRect.h, mRect.x + mRect.w}] = {mColor.bg, mColor.fg, mBorder.br};
    HLine(mRect.y + mRect.h, mRect.x + 1, mRect.w - 1, {mColor.bg, mColor.fg, mBorder.bs});
    HLine(mRect.y, mRect.x + 1, mRect.w - 1, {mColor.bg, mColor.fg, mBorder.ts});
    VLine(mRect.y + 1, mRect.x, mRect.h - 1, {mColor.bg, mColor.fg, mBorder.ls});
    VLine(mRect.y + 1, mRect.x + mRect.w, mRect.h - 1, {mColor.bg, mColor.fg, mBorder.rs});
}

void Window::MakeTitle()
{
    AddStr(mRect.y, mRect.x + 2, mTitle);
}