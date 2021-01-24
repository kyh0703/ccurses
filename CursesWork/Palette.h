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

class Palette
{
public:
    Palette();
    ~Palette();

    bool Init();
    bool KbHit();

    Form *GetActiveForm(Form *pFrom);
    bool Regist(Form *pForm);
    void Remove(Form *pForm);

    void DrawForm();
    void PollEvent(int milliseconds = 500);
    void Render(vector<Widget *> pWidgets);

private:
    int _active;
    Form *_pActvieForm;
    vector<Form *> _pForms;
};