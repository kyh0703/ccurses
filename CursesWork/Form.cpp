#include "Form.h"

Form::Form(void)
{
    _pCurrent = NULL;
    _isRun = false;
}

Form::~Form(void)
{
}

bool Form::IsActive()
{
    return _isActive;
}

void Form::SetActive(bool isActive)
{
    _isActive = isActive;
}

void Form::Run()
{
    printf("hihihihi");
    while (true)
    {
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

void Form::Stop()
{
    if (_worker.joinable())
        _worker.join();
}

void Form::Add(Widget *pWidget)
{
    _pWidgetes.push_back(pWidget);
}

void Form::Del(Widget *pWidget)
{
    list<Widget *>::iterator it;
    for (it = _pWidgetes.begin(); it != _pWidgetes.end(); ++it)
    {
        if (*it != pWidget)
            continue;
        Widget *pTemp = *it;
        if (pTemp)
            delete pTemp;
        _pWidgetes.erase(it);
    }
}

void Form::Clear()
{
    list<Widget *>::iterator it;
    for (it = _pWidgetes.begin(); it != _pWidgetes.end(); ++it)
    {
        Widget *pTemp = *it;
        if (pTemp)
            delete pTemp;
        _pWidgetes.erase(it);
    }
}

void Form::Draw()
{
    list<Widget *>::iterator it;
    for (it = _pWidgetes.begin(); it != _pWidgetes.end(); ++it)
    {
        Widget *pTemp = *it;
        pTemp->Draw();
        pTemp->Print();
    }
}

void Form::OnKeyEvent(int ch)
{
}