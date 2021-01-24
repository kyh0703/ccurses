#include "Window.h"
#include "Paint.h"
#include "Theme.h"

Window::Window()
{
    _isBox = true;
    _color.bg = th::Get()._base.color.bg;
    _color.fg = th::Get()._base.color.fg;
    _titleColor = th::Get()._base.tilte;
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

void Window::SetBox(bool isBox)
{
    _isBox = isBox;
};

void Window::SetRect(int h, int w, int y, int x)
{
    _rect = {h, w, y, x};
    _inner.min.y = _rect.min.y + 1;
    _inner.min.x = _rect.min.x + 1;
    _inner.max.y = _rect.max.y - 1;
    _inner.max.x = _rect.max.x - 1;
    _inner.h = _rect.h - 2;
    _inner.w = _rect.w - 2;
}

void Window::SetColor(int bg, int fg)
{
    _color.bg = bg;
    _color.fg = fg;
}

void Window::SetTitle(string title)
{
    _title = title;
}

const map<Pos, Rune> &Window::GetCells(void)
{
    return _cells;
}

void Window::AttachCells(map<Pos, Rune> cells)
{
    map<Pos, Rune>::iterator it;
    for (it = cells.begin(); it != cells.end(); ++it)
    {
        Pos pos((*it).first);
        Rune r((*it).second);
        if (_cells.find(pos) != _cells.end())
            _cells[pos] = r;
    }
}

void Window::Erase()
{
    for (int y = _rect.min.y; y <= _rect.max.y; ++y)
        for (int x = _rect.min.x; x <= _rect.max.x; ++x)
            mvdelch(y, x);
    refresh();
}

void Window::Print()
{
    for (int y = _rect.min.y; y <= _rect.max.y; ++y)
    {
        for (int x = _rect.min.x; x <= _rect.max.x; ++x)
        {
            Rune rune = _cells[{y, x}];
            int idx = Paint::Get().GetIndex(rune.s.bg, rune.s.fg);
            attron(COLOR_PAIR(idx) | rune.s.opt);
            mvaddch(y, x, rune.c);
            attroff(COLOR_PAIR(idx) | rune.s.opt);
        }
    }
}

void Window::BindKeyEvent(function<void(int)> keyEvent)
{
    _keyEvent = move(keyEvent);
}

bool Window::HasKeyEvent(void)
{
    return (_keyEvent ? true : false);
}

void Window::KeyEvent(int ch)
{
    if (_keyEvent)
        _keyEvent(ch);
}

void Window::HLine(int y, int x, int n, Rune c)
{
    for (int cols = x; cols < n + x; ++cols)
        _cells[{y, cols}] = c;
}

void Window::VLine(int y, int x, int n, Rune c)
{
    for (int line = y; line < n + y; ++line)
        _cells[{line, x}] = c;
}

void Window::AddCh(int y, int x, Rune c)
{
    _cells[{y, x}] = c;
}

void Window::AddStr(int y, int x, string s)
{
    for (size_t idx = 0; idx < s.size(); idx++)
        _cells[{y, x++}] = {_color.bg, COLOR_WHITE, (chtype)s[idx]};
}

const Rune Window::GetCh(int y, int x)
{
    return _cells[{y, x}];
}

const string Window::GetStr(int y, int x, int n)
{
    vector<chtype> runes;
    for (int col = x; col < x + n; ++col)
        runes.push_back(mvgetch(y, col));
    string str(runes.begin(), runes.end());
    return str;
}

Rect Window::InitCell()
{
    for (int y = _rect.min.y; y <= _rect.max.y; ++y)
        for (int x = _rect.min.x; x <= _rect.max.x; ++x)
            _cells[{y, x}] = {_color.bg, _color.bg, ' '};

    Rect rect;
    if (_isBox)
    {
        rect = _inner;
        DrawBase();
    }
    else
    {
        rect = _rect;
        EraseBase();
    }

    return rect;
}

void Window::DrawBase()
{
    MakeBorder();
    MakeTitle();
}

void Window::EraseBase()
{
    for (int y = _rect.min.y; y <= _rect.max.y; ++y)
    {
        for (int x = _rect.min.x; x <= _rect.max.x; ++x)
        {
            Rune r = _cells[{y, x}];
            if (r.c == ACS_VLINE ||
                r.c == ACS_HLINE ||
                r.c == ACS_ULCORNER ||
                r.c == ACS_URCORNER ||
                r.c == ACS_LLCORNER ||
                r.c == ACS_LRCORNER)
                _cells[{y, x}] = ' ';
        }
    }
}

void Window::MakeBorder()
{
    _cells[{_rect.min.y, _rect.min.x}] = {_color.bg, _color.fg, _border.tl};
    _cells[{_rect.min.y, _rect.max.x}] = {_color.bg, _color.fg, _border.tr};
    _cells[{_rect.max.y, _rect.min.x}] = {_color.bg, _color.fg, _border.bl};
    _cells[{_rect.max.y, _rect.max.x}] = {_color.bg, _color.fg, _border.br};
    HLine(_rect.min.y, _rect.min.x + 1, _rect.w - 2, {_color.bg, _color.fg, _border.ts});
    HLine(_rect.max.y, _rect.min.x + 1, _rect.w - 2 , {_color.bg, _color.fg, _border.bs});
    VLine(_rect.min.y + 1, _rect.min.x, _rect.h - 2, {_color.bg, _color.fg, _border.ls});
    VLine(_rect.min.y + 1, _rect.max.x, _rect.h - 2, {_color.bg, _color.fg, _border.rs});
}

void Window::MakeTitle()
{
    AddStr(_rect.min.y, _rect.min.x + 2, _title);
}