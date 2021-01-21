#include "Form.h"

Form::Form(void)
{
    _pCurrent = NULL;
    _isRun = false;
}

Form::~Form(void)
{
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
        if (pTemp)
            pTemp->Draw();
    }
}

void Form::Run()
{
    if (_worker.joinable())
        Stop();

    thread th = thread(bind(&Form::Work, this));
    _worker.swap(th);

    while (_isRun)
    {

    }
}

void Form::Work()
{

}

void Form::Stop()
{
    if (_worker.joinable())
        _worker.join();
}