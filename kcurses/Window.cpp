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
    _enable = true;
    _visible = true;
    _box = true;
    _is_active = false;
    _focus = false;
    _color.bg = th::Get()._base.color.bg;
    _color.fg = th::Get()._base.color.fg;
    _title_color = th::Get()._base.tilte;
    _window = NULL;
}

Window::~Window()
{
    clear();
    wclear(_window);
    wrefresh(_window);
    delwin(_window);
}

bool Window::CanFocus()
{
    return (_enable && _visible && _key_default);
}

void Window::AddCh(int y, int x, cchar_t *cch)
{
    mvwadd_wch(_window, y, x, cch);
}

void Window::AddCh(int y, int x, Rune r)
{
    int idx = Paint::Get().GetIndex(r.s.bg, r.s.fg);
    cchar_t cch;
    setcchar(&cch, &r.wch, r.s.opt, COLOR_PAIR(idx), NULL);
    mvwadd_wch(_window, y, x, &cch);
}

void Window::AddCh(int y, int x, Style s, wchar_t wch)
{
    int idx = Paint::Get().GetIndex(s.bg, s.fg);
    cchar_t cch;
    setcchar(&cch, &wch, WA_NORMAL, COLOR_PAIR(idx), NULL);
    mvwadd_wch(_window, y, x, &cch);
}

void Window::DrawBase()
{
    if (!_window)
        _window = newwin(_rect.h, _rect.w, _rect.min.y, _rect.min.x);

    // werase(_window);

    if (_box)
    {
        if (_enable && _key_default)
        {
            wborder_set(_window,
                        WACS_T_VLINE, WACS_T_VLINE,
                        WACS_T_HLINE, WACS_T_HLINE,
                        WACS_T_ULCORNER, WACS_T_URCORNER,
                        WACS_T_LLCORNER, WACS_T_LRCORNER);
        }
        else
        {
            wborder_set(_window,
                        WACS_VLINE, WACS_VLINE,
                        WACS_HLINE, WACS_HLINE,
                        WACS_ULCORNER, WACS_URCORNER,
                        WACS_LLCORNER, WACS_LRCORNER);
        }
    }

    int idx = Paint::Get().GetIndex(_color.bg, _color.fg);
    chtype ch = COLOR_PAIR(idx);
    if (_enable)
        ch |= WA_BOLD;
    else
        ch |= WA_NORMAL;
    if (_focus)
        ch |= WA_STANDOUT;
    wbkgd(_window, ch);

    DrawTitle();
}

void Window::DrawTitle()
{
    Pos pos(0, 2);
    for (size_t title_index = 0; title_index < _title.size(); ++title_index)
    {
        Rune r(_color.bg, _color.fg, _title[title_index]);
        AddCh(pos.y, pos.x, r.wch);
        if (Util::IsHangle(r.wch))
            pos.x += 2;
        else
            pos.x += 1;
    }
}

Rect Window::GetWinRect()
{
    int h = 0;
    int w = 0;
    int min_y = 0;
    int min_x = 0;

    if (_box)
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