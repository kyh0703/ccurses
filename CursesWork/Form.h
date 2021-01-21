#pragma once
#include <mutex>
#include <thread>
#include <queue>
#include <list>
#include "Widget.h"

class Form
{
public:
    Form();
    ~Form();

protected:
    void Add(Widget *pWidget);
    void Del(Widget *pWidget);
    void Clear();
    void Draw();

public:
    void Run();
    void Work();
    void Stop();

private:
    list<Widget *> _pWidgetes;
    Widget *_pCurrent;

    bool _isRun;
    queue<int> _keyEvent;
    thread _worker;
};