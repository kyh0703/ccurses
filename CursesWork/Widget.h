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

    void Draw() override;

public:
    int textColor;
    string text;
};

class Button : public Widget
{
public:
    Button();
    ~Button();

    void Draw() override;

public:
    Style active;
    Style inactive;
    bool IsActive;
    string text;
};

class TabPane : public Widget
{
public:
    TabPane();
    ~TabPane();

    void Draw() override;
    void ForcusLeft();
    void ForcusRight();

public:
    vector<string> tabs;
    int activeIdx;
    Style active;
    Style inactive;
};

class Tab : public Widget
{
public:
    Tab();
    ~Tab();

    void Draw() override;
    void ForcusLeft();
    void ForcusRight();

public:
    vector<string> tabs;
    int activeIdx;
};

class Menu : public Widget
{
public:
    Menu();
    ~Menu();

    void Draw() override;

public:
    vector<string> items;
};

class Input : public Widget
{
public:
    void Draw() override;
};
