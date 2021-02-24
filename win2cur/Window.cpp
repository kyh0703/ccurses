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
}

Window::~Window()
{
}

bool Window::CanFocus()
{
    return (_enable && _visible && _key_default);
}

void Window::AddCh(int y, int x, cchar_t *cch)
{
    mvadd_wch(y, x, cch);
}

void Window::AddCh(int y, int x, Rune r)
{
    int idx = Paint::Get().GetIndex(r.s.bg, r.s.fg);
    cchar_t cch;
    setcchar(&cch, &r.wch, r.s.opt, COLOR_PAIR(idx), NULL);
    mvadd_wch(y, x, &cch);
}

void Window::AddCh(int y, int x, Style s, wchar_t wch)
{
    int idx = Paint::Get().GetIndex(s.bg, s.fg);
    cchar_t cch;
    setcchar(&cch, &wch, WA_NORMAL, COLOR_PAIR(idx), NULL);
    mvadd_wch(y, x, &cch);
}

Rect Window::GetDrawRect()
{
    if (_box)
    {
        Rect inner;
        inner.min.y = _rect.min.y + 1;
        inner.min.x = _rect.min.x + 1;
        inner.max.y = _rect.max.y - 1;
        inner.max.x = _rect.max.x - 1;
        if (_rect.h <= 2)
            inner.h = _rect.h;
        else
            inner.h = _rect.h - 2;

        if (_rect.w <= 2)
            inner.w = _rect.w;
        else
            inner.w = _rect.w - 2;
        return inner;
    }

    return _rect;
}

void Window::InitCell()
{
    Rune r;
    r.s.bg = _color.bg;
    r.s.fg = _color.fg;
    r.s.opt = WA_NORMAL;
    r.wch = L' ';

    for (int y = _rect.min.y; y <= _rect.max.y; ++y)
        for (int x = _rect.min.x; x <= _rect.max.x; ++x)
            AddCh(y, x, r);
}

void Window::DrawBorder()
{
    AddCh(_rect.min.y, _rect.min.x, WACS_ULCORNER);
    AddCh(_rect.min.y, _rect.max.x, WACS_URCORNER);
    AddCh(_rect.max.y, _rect.min.x, WACS_LLCORNER);
    AddCh(_rect.max.y, _rect.max.x, WACS_LRCORNER);
    for (int x = _rect.min.x + 1; x < _rect.max.x; ++x)
        AddCh(_rect.min.y, x, WACS_HLINE);
    for (int x = _rect.min.x + 1; x < _rect.max.x; ++x)
        AddCh(_rect.max.y, x, WACS_HLINE);
    for (int y = _rect.min.y + 1; y < _rect.max.y; ++y)
        AddCh(y, _rect.min.x, WACS_VLINE);
    for (int y = _rect.min.y + 1; y < _rect.max.y; ++y)
        AddCh(y, _rect.max.x, WACS_VLINE);

    // VLine(_rect.min.y + 1, _rect.min.x, _rect.h - 2, WACS_VLINE);
    // VLine(_rect.min.y + 1, _rect.max.x, _rect.h - 2, WACS_VLINE);
}

void Window::DrawBase()
{
    InitCell();
    DrawBorder();
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