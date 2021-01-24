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

    bool IsActive();
    void SetActive(bool isActive);
    void Run();
    void Stop();
    void Draw();

protected:
    void Add(Widget *pWidget);
    void Del(Widget *pWidget);
    void Clear();
    virtual void OnKeyEvent(int ch);

private:
    bool _isActive;
    list<Widget *> _pWidgetes;
    Widget *_pCurrent;

    bool _isRun;
    queue<int> _keyEvent;
    thread _worker;
};