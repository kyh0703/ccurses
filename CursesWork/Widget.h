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

class Input : public Widget
{
public:
    Input();
    ~Input();

    void Draw() override;

public:
    Style _active;
    Style _inactive;
    bool _isActive;
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
    Style _active;
    Style _inactive;
};

class List : public Widget
{
public:
    List();
    ~List();

    void ScrollUp();
    void ScrollDown();
    void ScrollPageUp();
    void ScrollPageDown();
    void ScrollTop();
    void ScrollBottom();
    void ScrollAmount(int amount);
    void Draw() override;

public:
    vector<string> _rows;
    int _curRow;
    int _topRow;
    Style _active;
    Style _inactive;
};

class Form : public Widget
{

};