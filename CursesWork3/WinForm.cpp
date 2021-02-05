#include "WinForm.h"

WinForm::WinForm(void)
{
    _pCurrent = NULL;
    _isRun = false;
}

WinForm::~WinForm(void)
{
}

void WinForm::Draw()
{
    list<Widget *>::iterator it;
    for (it = _pWidgetes.begin(); it != _pWidgetes.end(); ++it)
    {
        Widget *pTemp = *it;
        pTemp->Draw();
    }
}

void WinForm::Add(Widget *pWidget)
{
    _pWidgetes.push_back(pWidget);
}

void WinForm::Del(Widget *pWidget)
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

void WinForm::Clear()
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
