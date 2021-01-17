#pragma once
#include "Attribute.h"

typedef class Theme th;
class Theme
{
public:
    struct Btn
    {
        Style active;
        Style inactive;
    };

    struct Tab
    {
        Style active;
        Style inactive;
    };

    struct List
    {
        Style active;
        Style inactive;
    };

    struct ProgressBar
    {
        int bar;
        Style label;
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
    List _list;
    ProgressBar _progress;
};
