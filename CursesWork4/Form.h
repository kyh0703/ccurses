#pragma once
#include "Queue.h"
#include "Widget.h"
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

class Form
{
public:
    Form();
    virtual ~Form();

    void Draw();
    void Run();

protected:
    void Add(Widget *widget);
    void Close(Widget *widget);
    void Clear();

    vector<Widget *> widgets;
    Queue<wint_t> _event_queue;

private:
    void PrevForcus();
    void NextForcus();
    void SetForcus();
    void OnMouseEvent(MEVENT &e);
    void OnKeyboardEvent(wint_t ch);

    Widget *_current;
};