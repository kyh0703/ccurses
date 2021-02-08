#pragma once
#include "Queue.h"
#include "Widget.h"
#include <vector>
#include <mutex>
#include <queue>
#include <thread>

class WinForm
{
public:
    WinForm();
    virtual ~WinForm();

    void Draw();
    void Run();

protected:
    void Add(Widget *pwidget);
    void Close(Widget *pwidget);
    void Clear();

    vector<Widget *> _pwidgetes;
    Queue<int> _eventque;

private:
    void OnMouseEvent(MEVENT &e);
    void OnKeyboardEvent(int ch);
};