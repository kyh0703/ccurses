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

    bool Init();

    void ForcusLeft();
    void ForcusRight();
    void ForcurFirst();
    void ForcurLast();

    bool Regist(WinForm *pForm);
    void Remove(WinForm *pForm);

    void DrawForm();
    void PollEvent(int fps = 500);

private:
    bool KbHit();

    int _activeform;
    WinForm *_pAactvieForm;
    vector<WinForm *> _pForms;
};