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

    struct TextBox
    {
        Style style;
    };

    struct Button
    {
        Style active;
        Style inactive;
    };

    struct Popup
    {
        int text_color;
        Style button;
    };

    struct YesNo
    {
        int text_color;
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
        int number;
        Style label;
    };

    struct CheckBox
    {
        Style active;
        Style inactive;
    };

    struct Radio
    {
        Style active;
        Style inactive;
    };

    struct MessageBox
    {
        Style active;
        Style inactive;
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
    TextBox _textbox;
    Button _button;
    Popup _popup;
    YesNo _yesno;
    Input _input;
    Tab _tab;
    List _list;
    ProgressBar _progress;
    BarChart _bar;
    CheckBox _checkbox;
    Radio _radio;
};
