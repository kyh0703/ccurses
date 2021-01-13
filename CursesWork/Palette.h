#pragma once
#include <locale.h>
#include <ncurses.h>
#include <vector>
#include <string>
#include "Widget.h"

using namespace std;

class Palette
{
public:
    Palette();
    ~Palette();

public:
    void Init();
    void Attach(Widget *pWidget);
    bool Render();

private:
    vector<Widget *> mWidgets;
};
