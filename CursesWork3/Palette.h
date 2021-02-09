#pragma once
#include <locale.h>
#include <ncurses.h>
#include <thread>
#include <chrono>
#include <vector>
#include <string>
#include "WinForm.h"
#include "Widget.h"
using namespace std;

class Palette
{
public:
    Palette();
    ~Palette();

    bool operator+=(const WinForm *pform);
    void operator-=(const WinForm *pform);
    void Clear();
    bool Init();
    void ForcusLeft();
    void ForcusRight();
    void ForcurFirst();
    void ForcurLast();
    void PollEvent(int fps = 500);

private:
    void Draw();
    bool KbHit();

    int _active_form;
    vector<WinForm *> _pforms;
};