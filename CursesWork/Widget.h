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
    int _textColor;
    string _text;
};

class Button : public Widget
{
public:
    Button();
    ~Button();

    void Draw() override;

public:
    Style _active;
    Style _inactive;
    bool _isActive;
    string _text;
};

class TabPane : public Widget
{
public:
    TabPane();
    ~TabPane();

    void ForcusLeft();
    void ForcusRight();
    void Draw() override;

public:
    vector<string> _tabs;
    int _activeIdx;
    Style _active;
    Style _inactive;
};

class Tab : public Widget
{
public:
    Tab();
    ~Tab();

    void ForcusLeft();
    void ForcusRight();
    void Draw() override;

public:
    vector<string> _tabs;
    int _activeIdx;
};

class Menu : public Widget
{
public:
    Menu();
    ~Menu();

    void ForcusUp();
    void ForcusDown();
    void Draw() override;

public:
    vector<string> _items;
    int _activeIdx;
};

class Input : public Widget
{
public:
    void Draw() override;
};
