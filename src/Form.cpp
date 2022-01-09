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
    Clear();
}

void Form::Draw()
{
    for (auto it = _widgets.begin(); it != _widgets.end(); ++it)
        (*it)->Draw();
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
        NextFocus();
        break;
    case KEY_BTAB:
        PrevFocus();
        break;
    default:
        OnKeyboardEvent(wch);
        break;
    }
}

bool Form::SetFocus(Widget *widget_ptr)
{
    if (widget_ptr->CanFocus())
    {
        _curfocus = widget_ptr;
        SetFocus();
        return true;
    }

    return false;
}

void Form::Add(Widget *widget_ptr)
{
    auto const &it = find_if(_widgets.begin(), _widgets.end(), [&](unique_ptr<Widget> &p) {
        return p.get() == widget_ptr;
    });

    if (it != _widgets.end())
        return;

    unique_ptr<Widget> temp(widget_ptr);
    _widgets.push_back(move(temp));
    if (widget_ptr->CanFocus() && !_curfocus)
    {
        _curfocus = widget_ptr;
        SetFocus();
    }
}

void Form::Delete(Widget *widget_ptr)
{
    if (widget_ptr == _curfocus)
    {
        if (!NextFocus(true))
            _curfocus = NULL;
    }

    auto const &it = find_if(_widgets.begin(), _widgets.end(), [&](unique_ptr<Widget> &p) {
        return p.get() == widget_ptr;
    });

    if (it != _widgets.end())
        _widgets.erase(it);
}

void Form::Clear()
{
    _widgets.clear();
}

bool Form::PrevFocus(bool is_del)
{
    std::vector<unique_ptr<Widget>>::reverse_iterator it;
    it = find_if(_widgets.rbegin(), _widgets.rend(), [&](unique_ptr<Widget> &p) {
        return p.get() == _curfocus;
    });

    if (it == _widgets.rend())
        return false;

    for (; it != _widgets.rend(); ++it)
    {
        if ((*it).get() == _curfocus)
            continue;

        if ((*it)->CanFocus())
        {
            _curfocus = (*it).get();
            SetFocus();
            return true;
        }
    }

    for (it = _widgets.rbegin(); it != _widgets.rend(); ++it)
    {
        if ((*it)->CanFocus())
        {
            if (is_del && _curfocus == (*it).get())
                continue;

            _curfocus = (*it).get();
            SetFocus();
            return true;
        }
    }

    return false;
}

bool Form::NextFocus(bool is_del)
{
    std::vector<unique_ptr<Widget>>::iterator it;
    it = find_if(_widgets.begin(), _widgets.end(), [&](unique_ptr<Widget> &p) {
        return p.get() == _curfocus;
    });

    if (it == _widgets.end())
        return false;

    for (; it != _widgets.end(); ++it)
    {
        if ((*it).get() == _curfocus)
            continue;

        if ((*it)->CanFocus())
        {
            _curfocus = (*it).get();
            SetFocus();
            return true;
        }
    }

    for (it = _widgets.begin(); it != _widgets.end(); ++it)
    {
        if ((*it)->CanFocus())
        {
            if (is_del && _curfocus == (*it).get())
                continue;

            _curfocus = (*it).get();
            SetFocus();
            return true;
        }
    }

    return false;
}

void Form::SetFocus()
{
    for (auto it = _widgets.begin(); it != _widgets.end(); ++it)
        (*it)->SetFocus(((*it).get() == _curfocus));
}

void Form::OnMouseEvent(MEVENT &e)
{
    MouseArgs args;
    args.y = e.y;
    args.x = e.x;
    args.button = MouseArgs::BitToMouseButton(e.bstate);

    for (auto it = _widgets.rbegin(); it != _widgets.rend(); ++it)
    {
        Widget *temp = (*it).get();
        Rect rect = temp->GetRect();
        if (!rect.IsInclude(e.y, e.x))
            continue;

        if (!(*it)->GetVisible() || !(*it)->GetEnable())
            continue;

        if ((*it)->_key_default)
        {
            _curfocus = (*it).get();
            SetFocus();
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
    args.wch = wch;
    switch (wch)
    {
    default:
        if (_curfocus && _curfocus->CanFocus())
        {
            _curfocus->_key_default(args);

            if (_curfocus->_key_press)
                _curfocus->_key_press(args);
        }
        break;
    }
}