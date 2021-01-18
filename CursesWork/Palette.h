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
    bool Init();
    bool KbHit();
    bool Render(vector<Widget *> pWidgets);
};
