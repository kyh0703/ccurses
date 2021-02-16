#pragma once
#include "Form.h"
#include "Widget.h"
#include <chrono>
#include <locale.h>
#include <ncursesw/curses.h>
#include <string>
#include <thread>
#include <vector>
using namespace std;

class Palette
{
public:
    Palette();
    ~Palette();

    bool operator+=(const Form *form);
    void operator-=(const Form *form);
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
    vector<Form *> _forms;
};