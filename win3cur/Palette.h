#pragma once
#include "Form.h"
#include "Widget.h"
#include <ncursesw/curses.h>
#include <signal.h>
#include <locale.h>
#include <chrono>
#include <string>
#include <thread>
#include <vector>
using namespace std;

class Palette
{
public:
    Palette();
    ~Palette();

    bool Add(Form *form_ptr);
    void Delete(const Form *form_ptr);
    void Clear();
    bool Init();
    void PollEvent(int fps = 50);

private:
    void FocusLeft();
    void FocusRight();
    void FocusFirst();
    void FocusLast();
    int ClickTab(MEVENT e);

    void DrawTab();
    void Draw();
    bool KbHit();

    int _active_form;
    vector<unique_ptr<Form>> _forms;
    Tab _tab;
};