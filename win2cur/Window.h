#pragma once
#include "Attribute.h"
#include "Event.h"
#include "Util.h"
#include <functional>
#include <iostream>
#include <map>
#include <ncursesw/curses.h>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class Window
{
public:
    Window();
    virtual ~Window();

    bool CanFocus();
    virtual void Draw() = 0;

    inline const bool GetEnable() { return _enable; }
    inline const bool GetVisible() { return _visible; }
    inline const bool GetFocus() { return _focus; }
    inline const bool GetBox() { return _box; }
    inline const Rect GetRect() { return _rect; }
    inline const Color GetColor() { return _color; }
    inline const int GetTitleColor() { return _title_color; }
    inline const wstring GetTitle() { return _title; }

    inline void SetEnable(bool enable) { _enable = enable; }
    inline void SetVisible(bool visible) { _visible = visible; }
    inline void SetFocus(bool focus) { _focus = focus; }
    inline void SetBox(bool box) { _box = box; }
    inline void SetRect(Rect rect) { _rect = rect; }
    inline void SetColor(Color color) { _color = color; }
    inline void SetTitleColor(int title_color) { _title_color = title_color; }
    inline void SetTitle(wstring title) { _title = title; }

    Event _click;
    MouseEvent _mouse_click;
    MouseEvent _mouse_press;
    MouseEvent _mouse_double_click;
    MouseEvent _mouse_release;
    MouseEvent _mouse_wheel_up;
    MouseEvent _mouse_wheel_down;
    KeyboardEvent _key_press;
    KeyboardEvent _key_default;

protected:
    void AddCh(int y, int x, cchar_t *cch);
    void AddCh(int y, int x, Style s, cchar_t *cch);
    void AddCh(int y, int x, Rune r);
    void AddCh(int y, int x, Style s, wchar_t wc);

    void InitCell();
    Rect GetDrawRect();
    void DrawBorder();
    void DrawTitle();
    void DrawBase();

    bool _enable;
    bool _visible;
    bool _focus;
    bool _box;
    Rect _rect;
    Color _color;
    int _title_color;
    wstring _title;
};