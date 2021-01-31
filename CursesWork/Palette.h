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

typedef function<void(int)> MainEvt;
class Palette
{
public:

    Palette();
    ~Palette();

    bool Init();
    void SetKeyEvent(MainEvt func);

    void ForcusLeft();
    void ForcusRight();
    void ForcurFirst();
    void ForcurLast();

    bool Regist(WinForm *pForm);
    void Remove(WinForm *pForm);

    void DrawForm();
    void PollEvent(bool hasTab, int milliseconds = 500);
    void Render(vector<Widget *> pWidgets);

private:
    bool KbHit();

    MainEvt _onKeyEvent;
    int _activeForm;
    WinForm *_pActvieForm;
    vector<WinForm *> _pForms;
};