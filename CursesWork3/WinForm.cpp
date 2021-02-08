#include "WinForm.h"

WinForm::WinForm(void)
{
}

WinForm::~WinForm(void)
{
}

void WinForm::Draw()
{
    vector<Widget *>::iterator it;
    for (it = _pwidgetes.begin(); it != _pwidgetes.end(); ++it)
    {
        Widget *pTemp = *it;
        pTemp->Draw();
    }
}

void WinForm::Add(Widget *pwidget)
{
    _pwidgetes.push_back(pwidget);
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

void WinForm::OnMouseEvent(MEVENT &e)
{
    MouseArgs args;
    args.y = e.y;
    args.x = e.x;
    args.button = MouseArgs::BitToMouseButton(e.bstate);

    vector<Widget *>::iterator it;
    for (it = _pwidgetes.begin(); it != _pwidgetes.end(); ++it)
    {
        Widget *pWidget = (*it);
        Rect rect = pWidget->_rect;
        if ((e.y < rect.min.y || rect.max.y < e.y) ||
            (e.x < rect.min.x || rect.max.x < e.x))
        {
            pWidget->_is_select = false;
            continue;
        }

        pWidget->_is_select = true;
        switch (e.bstate)
        {
        case BUTTON1_CLICKED:
        case BUTTON2_CLICKED:
        case BUTTON3_CLICKED:
            if (args.button == MOUSE_LEFT)
            {
                if (pWidget->_click)
                    pWidget->_click(EventArgs());
            }

            if (pWidget->_mouse_click)
                pWidget->_mouse_click(args);
            break;
        case BUTTON1_DOUBLE_CLICKED:
        case BUTTON2_DOUBLE_CLICKED:
        case BUTTON3_DOUBLE_CLICKED:
            if (pWidget->_mouse_double_click)
                pWidget->_mouse_double_click(args);
            break;
        case BUTTON1_PRESSED:
        case BUTTON2_PRESSED:
        case BUTTON3_PRESSED:
            if (pWidget->_mouse_press)
                pWidget->_mouse_press(args);
            break;
        case BUTTON1_RELEASED:
        case BUTTON2_RELEASED:
        case BUTTON3_RELEASED:
            if (pWidget->_mouse_release)
                pWidget->_mouse_release(args);
            break;
        case 524288:
            if (pWidget->_mouse_wheel_up)
                pWidget->_mouse_wheel_up(args);
            break;
        case 134217728:
            if (pWidget->_mouse_wheel_down)
                pWidget->_mouse_wheel_down(args);
            break;
        default:
            break;
        }
    }
}

void WinForm::OnKeyboardEvent(int ch)
{
    KeyboardArgs args;
    args.ch = ch;
    switch (ch)
    {
    case 9:
        break;
    case KEY_BTAB:
        break;
    case KEY_ENTER:
        break;
    default:
        Widget *pwidget = _pwidgetes[0];
        pwidget->_key_default(args);
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
