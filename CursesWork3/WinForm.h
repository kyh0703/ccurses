#pragma once
#include <mutex>
#include <thread>
#include <queue>
#include <list>
#include "Widget.h"
#include "EventHandler.h"

class WinForm
{
public:
    WinForm();
    virtual ~WinForm();

    void Draw();

    virtual void OnKeyEvent(int ch) = 0;

protected:
    void Add(Widget *pWidget);
    void Del(Widget *pWidget);
    void Clear();

private:
    bool _isActive;
    list<Widget *> _pWidgetes;
    Widget *_pCurrent;

    bool _isRun;
    queue<int> _keyEvent;
    thread _worker;
};