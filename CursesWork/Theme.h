#pragma once
#include "Window.h"

class Theme
{
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
};
