#include "Window.h"
#include "Paint.h"
#include "Theme.h"

Window::Window()
{
    _isBox = true;
    _color.bg = th::Get()._base.color.bg;
    _color.fg = th::Get()._base.color.fg;
    _titleColor = th::Get()._base.tilte;
    _pWin = NULL;
}

Window::~Window()
{
    delwin(_pWin);
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

Rect Window::GetWinRect()
{
    int minY = 0;
    int minX = 0;

    if (_isBox)
    {
        minY += 1;
        minX += 1;
    }

    return {_rect.h - 2, _rect.w - 2, minY, minX};
}

void Window::SetRect(int h, int w, int y, int x)
{
    _rect = {h, w, y, x};
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

void Window::VLine(int y, int x, int n, Rune c)
{
    for (int line = y; line < n + y; ++line)
        _cells[{line, x}] = c;
}

void Window::AddCh(int y, int x, Rune r)
{
    int idx = Paint::Get().GetIndex(r.s.bg, r.s.fg);
    wattron(_pWin, COLOR_PAIR(idx) | r.s.opt);
    mvwaddch(_pWin, y, x, r.c);
    wattroff(_pWin, COLOR_PAIR(idx) | r.s.opt);
}

void Window::AddCh(int y, int x, Style s, chtype c)
{
    int idx = Paint::Get().GetIndex(s.bg, s.fg);
    wattron(_pWin, COLOR_PAIR(idx) | s.opt);
    mvwaddch(_pWin, y, x, c);
    wattroff(_pWin, COLOR_PAIR(idx) | s.opt);
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

void Window::DrawBase()
{
    if (!_pWin)
        _pWin = newwin(_rect.h, _rect.w, _rect.min.y, _rect.min.x);

    werase(_pWin);

    if (_isBox)
        box(_pWin, 0, 0);

    mvwaddstr(_pWin, 0, 2, _title.c_str());
}

void Window::Render()
{
    wrefresh(_pWin);
}