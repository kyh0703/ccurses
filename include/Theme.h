#pragma once
#include "Attribute.h"
#include "Paint.h"
#include <ncursesw/curses.h>
#include <string>
using namespace std;

typedef class Theme th;
class Theme
{
public:
    enum
    {
        DARK_WHITE,
        WHITE_DARK,
        GITHUB_LIGHT,
        GITHUB_DARK,
        WINTER_IS_COMMING,
        VSCODE_DARK,
    };

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
        Style style;
    };

    struct Radio
    {
        Style style;
    };

    struct MessageBox
    {
        Style active;
        Style inactive;
    };

public:
    static Theme &Get();
    void SetTheme(unsigned theme);

    Base _base;
    TextBox _textbox;
    Button _button;
    Input _input;
    Tab _tab;
    List _list;
    ProgressBar _progress;
    BarChart _bar;
    Radio _radio;
    CheckBox _checkbox;

protected:
    Theme();
    Theme(Theme const &) = delete;
    Theme(Theme &&) = delete;
    Theme &operator=(Theme const &&) = delete;
    Theme &operator=(Theme &&) = delete;

private:
    void DarkWhite();
    void WhiteDark();
    void WinterIsComming();
    void GitHubLight();
    void GitHubDark();
    void VSCodeDark();
};
