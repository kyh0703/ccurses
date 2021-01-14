#pragma once
#include "Attribute.h"

typedef class Theme th;
class Theme
{
public:
    struct Btn
    {
        Style _active;
        Style _inactive;
    };

    struct Tab
    {
        Style _active;
        Style _inactive;
    };

    struct Menu
    {
        Style _active;
        Style _inactive;
    };

public:
    static Theme &Get();

protected:
    Theme();
    Theme(Theme const &) = delete;
    Theme(Theme &&) = delete;
    Theme &operator=(Theme const &&) = delete;
    Theme &operator=(Theme &&) = delete;

public:
    Color _default;
    int _basic;
    Btn _btn;
    Tab _tab;
    Menu _menu;
};
