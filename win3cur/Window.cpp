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
    _focus = false;
    _color.bg = th::Get()._base.color.bg;
    _color.fg = th::Get()._base.color.fg;
    _title_color = th::Get()._base.tilte;
}

Window::~Window()
{
    erase();
}

bool Window::CanFocus()
{
    return (_enable && _visible && _key_default);
}

void Window::AddCh(int y, int x, cchar_t *cch)
{
    mvadd_wch(y, x, cch);
}

void Window::AddCh(int y, int x, Style s, cchar_t *cch)
{
    int idx = Paint::Get().GetIndex(s.bg, s.fg);
    cch->attr |= s.opt;
    cch->attr |= COLOR_PAIR(idx);
    mvadd_wch(y, x, cch);
    cch->attr = WA_NORMAL;
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
    setcchar(&cch, &wch, WA_NORMAL, idx, NULL);
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
        inner.h = (_rect.h <= 2 ? _rect.h : _rect.h - 2);
        inner.w = (_rect.w <= 2 ? _rect.w : _rect.w - 2);
        return inner;
    }

    return _rect;
}

void Window::InitCell()
{
    Rune r;
    r.s.bg = COLOR_BLACK;
    r.s.fg = COLOR_BLACK;
    r.s.opt = WA_NORMAL;
    r.wch = L' ';

    for (int y = _rect.min.y; y <= _rect.max.y; ++y)
        for (int x = _rect.min.x; x <= _rect.max.x; ++x)
            AddCh(y, x, r);
}

void Window::DrawBorder()
{
    if (!_box)
        return;

    Border border;
    if (_enable && _key_default)
    {
        border.tl = WACS_D_ULCORNER;
        border.tr = WACS_D_URCORNER;
        border.bl = WACS_D_LLCORNER;
        border.br = WACS_D_LRCORNER;
        border.ls = WACS_D_VLINE;
        border.rs = WACS_D_VLINE;
        border.ts = WACS_D_HLINE;
        border.bs = WACS_D_HLINE;
    }

    if (_focus)
    {
        border.tl = WACS_T_ULCORNER;
        border.tr = WACS_T_URCORNER;
        border.bl = WACS_T_LLCORNER;
        border.br = WACS_T_LRCORNER;
        border.ls = WACS_T_VLINE;
        border.rs = WACS_T_VLINE;
        border.ts = WACS_T_HLINE;
        border.bs = WACS_T_HLINE;
    }

    Style s;
    s.bg = _color.bg;
    s.fg = _color.fg;

    AddCh(_rect.min.y, _rect.min.x, s, border.tl);
    AddCh(_rect.min.y, _rect.max.x, s, border.tr);
    AddCh(_rect.max.y, _rect.min.x, s, border.bl);
    AddCh(_rect.max.y, _rect.max.x, s, border.br);
    for (int x = _rect.min.x + 1; x < _rect.max.x; ++x)
        AddCh(_rect.min.y, x, s, border.ts);
    for (int x = _rect.min.x + 1; x < _rect.max.x; ++x)
        AddCh(_rect.max.y, x, s, border.bs);
    for (int y = _rect.min.y + 1; y < _rect.max.y; ++y)
        AddCh(y, _rect.min.x, s, border.ls);
    for (int y = _rect.min.y + 1; y < _rect.max.y; ++y)
        AddCh(y, _rect.max.x, s, border.rs);
}

void Window::DrawBase()
{
    InitCell();
    DrawBorder();
    DrawTitle();
}

void Window::DrawTitle()
{
    Pos pos(_rect.min.y, _rect.min.x + 2);
    for (size_t title_index = 0; title_index < _title.size(); ++title_index)
    {
        Rune r(_color.bg, _title_color, _title[title_index]);
        AddCh(pos.y, pos.x, r);
        pos.x += (Util::IsHangle(r.wch) ? 2 : 1);
    }
}