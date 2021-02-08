#include "Window.h"
#include "Paint.h"
#include "Theme.h"

Window::Window()
{
    _click = NULL;
    _mouse_click = NULL;
    _mouse_press = NULL;
    _mouse_double_click = NULL;
    _mouse_release = NULL;
    _mouse_wheel_up = NULL;
    _mouse_wheel_down = NULL;
    _key_press = NULL;
    _key_default = NULL;
    _is_enable = true;
    _is_visible = true;
    _is_box = true;
    _is_active = false;
    _is_select = false;
    _color.bg = th::Get()._base.color.bg;
    _color.fg = th::Get()._base.color.fg;
    _title_color = th::Get()._base.tilte;
    _pwindow = NULL;
}

Window::~Window()
{
    delwin(_pwindow);
}

void Window::AddCh(int y, int x, Rune r)
{
    int idx = Paint::Get().GetIndex(r.s.bg, r.s.fg);
    wattron(_pwindow, COLOR_PAIR(idx) | r.s.opt);
    mvwaddch(_pwindow, y, x, r.c);
    wattroff(_pwindow, COLOR_PAIR(idx) | r.s.opt);
}

void Window::AddCh(int y, int x, Style s, chtype c)
{
    int idx = Paint::Get().GetIndex(s.bg, s.fg);
    wattron(_pwindow, COLOR_PAIR(idx) | s.opt);
    mvwaddch(_pwindow, y, x, c);
    wattroff(_pwindow, COLOR_PAIR(idx) | s.opt);
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
    if (!_pwindow)
        _pwindow = newwin(_rect.h, _rect.w, _rect.min.y, _rect.min.x);

    werase(_pwindow);

    if (_is_box)
        box(_pwindow, 0, 0);

    int idx = Paint::Get().GetIndex(_color.bg, _color.fg);
    chtype ch = COLOR_PAIR(idx);
    if (_is_select)
        ch |= A_BOLD | A_BLINK;
    wbkgd(_pwindow, ch);
    DrawTitle();
}

void Window::DrawTitle()
{
    int idx = Paint::Get().GetIndex(_color.bg, _title_color);
    wattron(_pwindow, COLOR_PAIR(idx));
    mvwaddstr(_pwindow, 0, 2, _title.c_str());
    wattroff(_pwindow, COLOR_PAIR(idx));
}

Rect Window::GetWinRect()
{
    int h = 0;
    int w = 0;
    int min_y = 0;
    int min_x = 0;

    if (_is_box)
    {
        min_y += 1;
        min_x += 1;
    }

    if (_rect.h <= 2)
        h = _rect.h;
    else
        h = _rect.h - 2;

    if (_rect.w <= 2)
        w = _rect.w;
    else
        w = _rect.w - 2;

    return {h, w, min_y, min_x};
}

void Window::Render()
{
    wrefresh(_pwindow);
}