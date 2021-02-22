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

    inline int GetId() { return _id; }
    void Draw();
    void ProcEvent(wint_t &wch);

    wstring _text;

protected:
    void Add(Widget *widget);
    void Delete(Widget *widget);
    void Close(Widget *widget);
    void Clear();

    vector<Widget *> _widgets;

private:
    void PrevForcus();
    void NextForcus();
    void SetForcus();
    void OnMouseEvent(MEVENT &e);
    void OnKeyboardEvent(wint_t ch);

    int _id;
    Widget *_curfocus;
    static int _count;
};