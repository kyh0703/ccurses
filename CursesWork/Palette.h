#pragma once
#include <locale.h>
#include <ncurses.h>
#include <thread>
#include <chrono>
#include <vector>
#include <string>
#include "Form.h"
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

    Form *GetActiveForm(Form *pFrom);
    bool Regist(Form *pForm);
    void Remove(Form *pForm);

    void DrawForm();
    void PollEvent(bool hasTab, int milliseconds = 500);
    void Render(vector<Widget *> pWidgets);

private:
    bool KbHit();

    MainEvt _onKeyEvent;
    int _activeForm;
    Form *_pActvieForm;
    vector<Form *> _pForms;
};