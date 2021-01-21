#pragma once
#include <locale.h>
#include <ncurses.h>
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
    void Render(vector<Widget *> pWidgets);
    void Render(Form &form);

    void AddForm(string id, Form *pForm);
    void DelForm(string id);

    int GetActiveForm();
    void PollEvent();

private:
    int _actvieForm;
};