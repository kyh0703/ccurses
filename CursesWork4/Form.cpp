#include "Form.h"

Form::Form()
{
    _current = NULL;
}

Form::~Form()
{
}

void Form::Draw()
{
    vector<Widget *>::iterator it;
    for (it = widgets.begin(); it != widgets.end(); ++it)
        (*it)->Draw();
}

void Form::Add(Widget *widget)
{
    widgets.push_back(widget);
    if (widget->CanFocus() && !_current)
    {
        _current = widget;
        SetForcus();
    }
}

void Form::Close(Widget *widget)
{
    vector<Widget *>::iterator it;
    for (it = widgets.begin(); it != widgets.end(); ++it)
    {
        if (*it != widget)
            continue;
        Widget *temp = *it;
        if (temp)
            delete temp;
        widgets.erase(it);
    }
}

void Form::Clear()
{
    vector<Widget *>::iterator it;
    for (it = widgets.begin(); it != widgets.end();)
    {
        Widget *temp = *it;
        if (temp)
            delete temp;
        it = widgets.erase(it);
    }
}

void Form::PrevForcus()
{
    vector<Widget *>::reverse_iterator it;
    it = find(widgets.rbegin(), widgets.rend(), _current);
    if (it == widgets.rend())
        return;

    for (; it != widgets.rend(); ++it)
    {
        if (*it == _current)
            continue;

        if ((*it)->CanFocus())
        {
            _current = (*it);
            SetForcus();
            return;
        }
    }

    for (it = widgets.rbegin(); it != widgets.rend(); ++it)
    {
        if ((*it)->CanFocus())
        {
            _current = (*it);
            SetForcus();
            return;
        }
    }
}

void Form::NextForcus()
{
    vector<Widget *>::iterator it;
    it = find(widgets.begin(), widgets.end(), _current);
    if (it == widgets.end())
        return;

    for (; it != widgets.end(); ++it)
    {
        if (*it == _current)
            continue;

        if ((*it)->CanFocus())
        {
            _current = (*it);
            SetForcus();
            return;
        }
    }

    for (it = widgets.begin(); it != widgets.end(); ++it)
    {
        if ((*it)->CanFocus())
        {
            _current = (*it);
            SetForcus();
            return;
        }
    }
}

void Form::SetForcus()
{
    vector<Widget *>::iterator it;
    for (it = widgets.begin(); it != widgets.end(); ++it)
        (*it)->_focus = ((*it) == _current);
}

void Form::OnMouseEvent(MEVENT &e)
{
    MouseArgs args;
    args.y = e.y;
    args.x = e.x;
    args.button = MouseArgs::BitToMouseButton(e.bstate);

    vector<Widget *>::iterator it;
    for (it = widgets.begin(); it != widgets.end(); ++it)
    {
        Widget *temp = (*it);
        Rect rect = temp->_rect;
        if (!rect.IsInclude(e.y, e.x))
            continue;

        if (!(*it)->_visible && !(*it)->_enable)
            continue;

        if ((*it)->_key_default)
        {
            _current = *it;
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
    case 9:
        NextForcus();
        break;
    case KEY_BTAB:
        PrevForcus();
        break;
    default:
        if (_current && _current->CanFocus())
            _current->_key_default(args);
        break;
    }
}

void Form::Run()
{
    MEVENT e;

    while (true)
    {
        wint_t wch;
        get_wch(&wch);
        switch (wch)
        {
        case KEY_MOUSE:
            if (getmouse(&e) == OK)
                OnMouseEvent(e);
            break;
        default:
            OnKeyboardEvent(wch);
            break;
        }
        Draw();
    }
}
