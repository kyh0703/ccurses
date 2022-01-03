#pragma once
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
    bool SetFocus(Widget *widget_ptr);

    wstring _text;

protected:
    void Add(Widget *widget_ptr);
    void Delete(Widget *widget_ptr);
    void Clear();

    vector<unique_ptr<Widget>> _widgets;

private:
    bool PrevFocus(bool is_del = false);
    bool NextFocus(bool is_del = false);
    void SetFocus();

    void OnMouseEvent(MEVENT &e);
    void OnKeyboardEvent(wint_t ch);

    int _id;
    Widget *_curfocus;
    static int _count;
};