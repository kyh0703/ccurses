#pragma once
#include "Attribute.h"
#include "Event.h"
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

    Event _click;
    MouseEvent _mouse_click;
    MouseEvent _mouse_press;
    MouseEvent _mouse_double_click;
    MouseEvent _mouse_release;
    MouseEvent _mouse_wheel_up;
    MouseEvent _mouse_wheel_down;
    KeyboardEvent _key_press;
    KeyboardEvent _key_default;

    bool _enable;
    bool _visible;
    bool _focus;
    bool _is_active;
    bool _box;
    Rect _rect;
    Color _color;
    int _title_color;
    wstring _title;

protected:
    bool IsHangle(const wchar_t wc);
    void AddCh(int y, int x, cchar_t *cch);
    void AddCh(int y, int x, Rune r);
    void AddCh(int y, int x, Style s, wchar_t wc);
    void DrawBase();
    void DrawTitle();
    Rect GetWinRect(void);
    void Render();

    WINDOW *_window;
};