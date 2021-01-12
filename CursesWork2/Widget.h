#pragma once
#include <iostream>
#include <sstream>
#include <ncurses.h>
#include <string>
#include <vector>
#include <map>
#include "Window.h"

using namespace std;

class Widget : public Window
{
public:
    Widget();
    ~Widget();

    virtual void Draw() = 0;
};

class Basic : public Widget
{
public:
    Basic();
    ~Basic();

    void SetText(string text);
    void Draw() override;

private:
    string mText;
    bool mIsWrap;
};

class Input : public Widget
{
public:
    void Draw() override;
};

class Menu : public Widget
{
public:
    void Draw() override;
};