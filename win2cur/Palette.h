#pragma once
#include "Form.h"
#include "Theme.h"
#include "Widget.h"
#include <chrono>
#include <locale.h>
#include <ncursesw/curses.h>
#include <signal.h>
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
    bool Init(unsigned theme = Theme::DARK_WHITE);
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
    Tab *_tab;
};