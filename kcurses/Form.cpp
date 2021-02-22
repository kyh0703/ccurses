#include "Form.h"

int Form::_count = 0;

Form::Form()
{
    _id = _count++;
    _text = L"Form" + to_wstring(_id);
    _curfocus = NULL;
}

Form::~Form()
{
}

void Form::Draw()
{
    vector<Widget *>::iterator it;
    for (it = _widgets.begin(); it != _widgets.end(); ++it)
        (*it)->Draw();
}

void Form::Add(Widget *widget)
{
    _widgets.push_back(widget);
    if (widget->CanFocus() && !_curfocus)
    {
        mvprintw(LINES - 1, 0, "test[%s]", widget->_title.c_str());
        _curfocus = widget;
        SetForcus();
    }
}

void Form::Delete(Widget *widget)
{
    vector<Widget *>::iterator it;
    for (it = _widgets.begin(); it != _widgets.end(); ++it)
    {
        if (*it == widget)
        {
            Widget *pTemp = *it;
            delete pTemp;
            _widgets.erase(it);
        }
    }
}

void Form::Close(Widget *widget)
{
    vector<Widget *>::iterator it;
    for (it = _widgets.begin(); it != _widgets.end(); ++it)
    {
        if (*it != widget)
            continue;
        Widget *temp = *it;
        if (temp)
            delete temp;
        _widgets.erase(it);
    }
}

void Form::Clear()
{
    vector<Widget *>::iterator it;
    for (it = _widgets.begin(); it != _widgets.end();)
    {
        Widget *temp = *it;
        if (temp)
            delete temp;
        it = _widgets.erase(it);
    }
}

void Form::PrevForcus()
{
    vector<Widget *>::reverse_iterator it;
    it = find(_widgets.rbegin(), _widgets.rend(), _curfocus);
    if (it == _widgets.rend())
        return;

    for (; it != _widgets.rend(); ++it)
    {
        if (*it == _curfocus)
            continue;

        if ((*it)->CanFocus())
        {
            _curfocus = (*it);
            SetForcus();
            return;
        }
    }

    for (it = _widgets.rbegin(); it != _widgets.rend(); ++it)
    {
        if ((*it)->CanFocus())
        {
            _curfocus = (*it);
            SetForcus();
            return;
        }
    }
}

void Form::NextForcus()
{
    vector<Widget *>::iterator it;
    it = find(_widgets.begin(), _widgets.end(), _curfocus);
    if (it == _widgets.end())
        return;

    for (; it != _widgets.end(); ++it)
    {
        if (*it == _curfocus)
            continue;

        if ((*it)->CanFocus())
        {
            _curfocus = (*it);
            SetForcus();
            return;
        }
    }

    for (it = _widgets.begin(); it != _widgets.end(); ++it)
    {
        if ((*it)->CanFocus())
        {
            _curfocus = (*it);
            SetForcus();
            return;
        }
    }
}

void Form::SetForcus()
{
    vector<Widget *>::iterator it;
    for (it = _widgets.begin(); it != _widgets.end(); ++it)
        (*it)->_focus = ((*it) == _curfocus);
}

void Form::OnMouseEvent(MEVENT &e)
{
    MouseArgs args;
    args.y = e.y;
    args.x = e.x;
    args.button = MouseArgs::BitToMouseButton(e.bstate);

    vector<Widget *>::iterator it;
    for (it = _widgets.begin(); it != _widgets.end(); ++it)
    {
        Widget *temp = (*it);
        Rect rect = temp->_rect;
        if (!rect.IsInclude(e.y, e.x))
            continue;

        if (!(*it)->_visible || !(*it)->_enable)
            continue;

        if ((*it)->_key_default)
        {
            _curfocus = *it;
            SetForcus();
        }

        switch (e.bstate)
        {
        case BUTTON1_CLICKED:
            if (temp->_click)
                temp->_click(EventArgs());
        case BUTTON2_CLICKED:
        case BUTTON3_CLICKED:
            if (temp->_mouse_click)
                temp->_mouse_click(args);
            break;
        case BUTTON1_DOUBLE_CLICKED:
        case BUTTON2_DOUBLE_CLICKED:
        case BUTTON3_DOUBLE_CLICKED:
            if (temp->_mouse_double_click)
                temp->_mouse_double_click(args);
            break;
        case BUTTON1_PRESSED:
        case BUTTON2_PRESSED:
        case BUTTON3_PRESSED:
            if (temp->_mouse_press)
                temp->_mouse_press(args);
            break;
        case BUTTON1_RELEASED:
        case BUTTON2_RELEASED:
        case BUTTON3_RELEASED:
            if (temp->_mouse_release)
                temp->_mouse_release(args);
            break;
        case 524288:
            if (temp->_mouse_wheel_up)
                temp->_mouse_wheel_up(args);
            break;
        case 134217728:
            if (temp->_mouse_wheel_down)
                temp->_mouse_wheel_down(args);
            break;
        default:
            break;
        }

        break;
    }
}

void Form::OnKeyboardEvent(wint_t wch)
{
    KeyboardArgs args;
    args.ch = wch;
    switch (wch)
    {
    default:
        if (_curfocus && _curfocus->CanFocus())
            _curfocus->_key_default(args);
        break;
    }
}

void Form::ProcEvent(wint_t &wch)
{
    MEVENT e;
    switch (wch)
    {
    case KEY_MOUSE:
        if (getmouse(&e) == OK)
            OnMouseEvent(e);
        break;
    case 9:
        NextForcus();
        break;
    case KEY_BTAB:
        PrevForcus();
        break;
    default:
        OnKeyboardEvent(wch);
        break;
    }
}
