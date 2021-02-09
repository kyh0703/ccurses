#include "WinForm.h"

WinForm::WinForm()
{
    _pcurrent = NULL;
}

WinForm::~WinForm()
{
}

void WinForm::Draw()
{
    vector<Widget *>::iterator it;
    for (it = _pwidgetes.begin(); it != _pwidgetes.end(); ++it)
        (*it)->Draw();
}

void WinForm::Add(Widget *pwidget)
{
    _pwidgetes.push_back(pwidget);
    if (pwidget->CanFocus() && !_pcurrent)
    {
        _pcurrent = pwidget;
        SetForcus();
    }
}

void WinForm::Close(Widget *pwidget)
{
    vector<Widget *>::iterator it;
    for (it = _pwidgetes.begin(); it != _pwidgetes.end(); ++it)
    {
        if (*it != pwidget)
            continue;
        Widget *pTemp = *it;
        if (pTemp)
            delete pTemp;
        _pwidgetes.erase(it);
    }
}

void WinForm::Clear()
{
    vector<Widget *>::iterator it;
    for (it = _pwidgetes.begin(); it != _pwidgetes.end();)
    {
        Widget *pTemp = *it;
        delete pTemp;
        it = _pwidgetes.erase(it);
    }
}

void WinForm::PrevForcus()
{
    vector<Widget *>::reverse_iterator it;
    it = find(_pwidgetes.rbegin(), _pwidgetes.rend(), _pcurrent);
    if (it == _pwidgetes.rend())
        return;

    for (; it != _pwidgetes.rend(); ++it)
    {
        if (*it == _pcurrent)
            continue;
        if ((*it)->CanFocus())
        {
            _pcurrent = (*it);
            SetForcus();
            return;
        }
    }

    for (it = _pwidgetes.rbegin(); it != _pwidgetes.rend(); ++it)
    {
        if ((*it)->CanFocus())
        {
            _pcurrent = (*it);
            SetForcus();
            return;
        }
    }
}

void WinForm::NextForcus()
{
    vector<Widget *>::iterator it;
    it = find(_pwidgetes.begin(), _pwidgetes.end(), _pcurrent);
    if (it == _pwidgetes.end())
        return;

    for (; it != _pwidgetes.end(); ++it)
    {
        if (*it == _pcurrent)
            continue;
        if ((*it)->CanFocus())
        {
            _pcurrent = (*it);
            SetForcus();
            return;
        }
    }

    for (it = _pwidgetes.begin(); it != _pwidgetes.end(); ++it)
    {
        if ((*it)->CanFocus())
        {
            _pcurrent = (*it);
            SetForcus();
            return;
        }
    }
}

void WinForm::SetForcus()
{
    vector<Widget *>::iterator it;
    for (it = _pwidgetes.begin(); it != _pwidgetes.end(); ++it)
        (*it)->_forcus = ((*it) == _pcurrent ? true : false);
}

void WinForm::OnMouseEvent(MEVENT &e)
{
    MouseArgs args;
    args.y = e.y;
    args.x = e.x;
    args.button = MouseArgs::BitToMouseButton(e.bstate);

    vector<Widget *>::iterator it;
    for (it = _pwidgetes.begin(); it != _pwidgetes.end(); ++it)
    {
        Widget *pwidget = (*it);
        Rect rect = pwidget->_rect;
        if (!rect.IsInclude(e.y, e.x))
            continue;

        if ((*it)->CanFocus())
        {
            _pcurrent = *it;
            SetForcus();
        }

        switch (e.bstate)
        {
        case BUTTON1_CLICKED:
            if (pwidget->_click)
                pwidget->_click(EventArgs());
        case BUTTON2_CLICKED:
        case BUTTON3_CLICKED:
            if (pwidget->_mouse_click)
                pwidget->_mouse_click(args);
            break;
        case BUTTON1_DOUBLE_CLICKED:
        case BUTTON2_DOUBLE_CLICKED:
        case BUTTON3_DOUBLE_CLICKED:
            if (pwidget->_mouse_double_click)
                pwidget->_mouse_double_click(args);
            break;
        case BUTTON1_PRESSED:
        case BUTTON2_PRESSED:
        case BUTTON3_PRESSED:
            if (pwidget->_mouse_press)
                pwidget->_mouse_press(args);
            break;
        case BUTTON1_RELEASED:
        case BUTTON2_RELEASED:
        case BUTTON3_RELEASED:
            if (pwidget->_mouse_release)
                pwidget->_mouse_release(args);
            break;
        case 524288:
            if (pwidget->_mouse_wheel_up)
                pwidget->_mouse_wheel_up(args);
            break;
        case 134217728:
            if (pwidget->_mouse_wheel_down)
                pwidget->_mouse_wheel_down(args);
            break;
        default:
            break;
        }

        break;
    }
}

void WinForm::OnKeyboardEvent(int ch)
{
    KeyboardArgs args;
    args.ch = ch;
    switch (ch)
    {
    case 9:
        NextForcus();
        break;
    case KEY_BTAB:
        PrevForcus();
        break;
    default:
        _pcurrent->_key_default(args);
        break;
    }
}

void WinForm::Run()
{
    int ch = 0;
    MEVENT e;

    // _eventque.pop(ch);

    while (true)
    {
        int ch = getch();
        switch (ch)
        {
        case KEY_MOUSE:
            if (getmouse(&e) == OK)
                OnMouseEvent(e);
            break;
        default:
            OnKeyboardEvent(ch);
            break;
        }
        Draw();
    }
}
