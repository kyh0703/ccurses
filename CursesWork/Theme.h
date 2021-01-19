#pragma once
#include "Attribute.h"

typedef class Theme th;
class Theme
{
public:

    struct Base
    {
        Color color;
        int tilte;
    };

    struct Basic
    {
        int textColor;
    };

    struct Btn
    {
        Style active;
        Style inactive;
    };

    struct Input
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

    struct BarChart
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
    Base _base;
    Basic _basic;
    Btn _btn;
    Input _input;
    Tab _tab;
    List _list;
    ProgressBar _progress;
    BarChart _bar;
};
