#pragma once
#include <functional>
#include <ncursesw/curses.h>
using namespace std;

struct EventArgs
{
};

enum MouseButton
{
    MOUSE_NONE,
    MOUSE_LEFT,
    MOUSE_MIDDLE,
    MOUSE_RIGHT,
};

struct MouseArgs : public EventArgs
{
    MouseArgs();
    MouseArgs(int y, int x, MouseButton button);
    static MouseButton BitToMouseButton(mmask_t &mask);
    int y, x;
    MouseButton button;
};

struct KeyboardArgs : public EventArgs
{
    int ch;
};

using Event = function<void(EventArgs)>;
using MouseEvent = function<void(MouseArgs)>;
using KeyboardEvent = function<void(KeyboardArgs)>;