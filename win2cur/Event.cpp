#include "Event.h"

MouseArgs::MouseArgs()
{
    this->y = 0;
    this->x = 0;
    this->button = MOUSE_NONE;
}

MouseArgs::MouseArgs(int y, int x, MouseButton button)
{
    this->y = y;
    this->x = x;
    this->button = button;
}

MouseButton MouseArgs::BitToMouseButton(mmask_t &mask)
{
    switch (mask)
    {
    case BUTTON1_CLICKED:
    case BUTTON1_DOUBLE_CLICKED:
    case BUTTON1_PRESSED:
    case BUTTON1_RELEASED:
        return MOUSE_LEFT;
    case BUTTON2_CLICKED:
    case BUTTON2_DOUBLE_CLICKED:
    case BUTTON2_PRESSED:
    case BUTTON2_RELEASED:
    case 524288:
    case 134217728:
        return MOUSE_MIDDLE;
    case BUTTON3_CLICKED:
    case BUTTON3_DOUBLE_CLICKED:
    case BUTTON3_PRESSED:
    case BUTTON3_RELEASED:
        return MOUSE_RIGHT;
    default:
        return MOUSE_NONE;
    }
}