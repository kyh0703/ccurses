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
    delwin(_window);
}

bool Window::CanFocus()
{
    return (_enable && _visible && _key_default);
}

bool Window::IsHangle(const wchar_t wch)
{
    const wchar_t start_ch = L'가';
    const wchar_t end_ch = L'힣';
    return (start_ch <= wch && wch <= end_ch);
}

void Window::AddCh(int y, int x, Rune r)
{
    int idx = Paint::Get().GetIndex(r.s.bg, r.s.fg);
    cchar_t cch;
    setcchar(&cch, &r.wc, r.s.opt, COLOR_PAIR(idx), NULL);
    mvwadd_wch(_window, y, x, &cch);
    // mvwaddwstr(_window, y, x, &r.wc);
    // wattron(_window, COLOR_PAIR(idx) | r.s.opt);
    // mvwaddch(_window, y, x, r.c);
    // wattroff(_window, COLOR_PAIR(idx) | r.s.opt);
}

void Window::AddCh(int y, int x, Style s, chtype c)
{
    // int idx = Paint::Get().GetIndex(s.bg, s.fg);
    // wattron(_window, COLOR_PAIR(idx) | s.opt);
    // mvwaddch(_window, y, x, c);
    // wattroff(_window, COLOR_PAIR(idx) | s.opt);
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
    if (!_window)
        _window = newwin(_rect.h, _rect.w, _rect.min.y, _rect.min.x);

    werase(_window);

    if (_box)
        box_set(_window, 0, 0);

    int idx = Paint::Get().GetIndex(_color.bg, _color.fg);
    chtype ch = COLOR_PAIR(idx);
    if (_focus)
        ch |= A_BOLD | A_BLINK;

    wbkgd(_window, ch);
    DrawTitle();
}

void Window::DrawTitle()
{
    int idx = Paint::Get().GetIndex(_color.bg, _title_color);
    wattron(_window, COLOR_PAIR(idx));
    mvwaddstr(_window, 0, 2, _title.c_str());
    wattroff(_window, COLOR_PAIR(idx));
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

void Window::Render()
{
    wrefresh(_window);
}