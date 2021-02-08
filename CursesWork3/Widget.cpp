#include "Widget.h"
#include "Theme.h"
#include "Paint.h"

TextBox::TextBox()
{
    _style = th::Get()._textbox.style;
    _is_box = false;
    _type = TEXTBOX;
}

TextBox::~TextBox()
{
}

void TextBox::Draw()
{
    if (!_is_visible)
        return;

    DrawBase();
    Rect rect = GetWinRect();
    Pos pos(rect.min.x, rect.min.x);

    for (size_t text_index = 0; text_index < _text.size(); ++text_index)
    {
        bool is_EOL = (_text[text_index] == '\n');
        if (is_EOL || rect.max.x < pos.x)
        {
            pos.y++;
            pos.x = rect.min.x;
            if (is_EOL)
                continue;
        }

        if (rect.max.y < pos.y)
            break;

        Rune r(_style, _text[text_index]);
        AddCh(pos.y, pos.x++, r);
    }

    Render();
}

Button::Button()
{
    _active = th::Get()._button.active;
    _inactive = th::Get()._button.inactive;
    _type = BUTTON;
}

Button::~Button()
{
}

void Button::Draw()
{
    if (!_is_visible)
        return;

    DrawBase();
    Rect rect = GetWinRect();
    Pos pos(rect.min.y, rect.min.x);

    for (size_t text_index = 0; text_index < _text.size(); ++text_index)
    {
        if (rect.max.x < pos.x)
            break;

        Style style;
        if (_is_active)
            style = _active;
        else
            style = _inactive;

        Rune r(_active, _text[text_index]);
        AddCh(pos.y, pos.x++, r);
    }
    Render();
}

Popup::Popup()
{
    _button_style = th::Get()._popup.button;
    _text_color = th::Get()._popup.text_color;
    _type = POPUP;
}

Popup::~Popup()
{
}

void Popup::Draw()
{
    if (!_is_visible)
        return;

    DrawBase();
    Rect rect = GetWinRect();
    Pos pos(rect.min.y, rect.min.x);

    for (size_t text_index = 0; text_index < _text.size(); ++text_index)
    {
        bool is_EOL = (_text[text_index] == '\n');
        if (is_EOL || rect.max.x < pos.x)
        {
            pos.y++;
            pos.x = rect.min.x;
            if (is_EOL)
                continue;
        }

        if (rect.max.y - 2 < pos.y)
            break;

        Rune r(_color.bg, _text_color, _text[text_index]);
        AddCh(pos.y, pos.x++, r);
    }

    string enter = "<ENTER >";
    pos.x = rect.min.x + ((rect.w - enter.size()) / 2);
    for (size_t i = 0; i < enter.size(); ++i)
    {
        Rune r(_button_style, enter[i]);
        AddCh(rect.max.y - 1, pos.x++, r);
    }

    Render();
}

YesNo::YesNo()
{
    _text_color = th::Get()._yesno.text_color;
    _active = th::Get()._yesno.active;
    _inactive = th::Get()._yesno.inactive;
    _is_yes = true;
    _type = YESNO;
}

YesNo::~YesNo()
{
}

void YesNo::ForcusLeft()
{
    if (!_is_yes)
        _is_yes = true;
}

void YesNo::ForcusRight()
{
    if (_is_yes)
        _is_yes = false;
}

void YesNo::Draw()
{
    if (!_is_visible)
        return;

    DrawBase();
    Rect rect = GetWinRect();
    Pos pos(rect.min.y, rect.min.x);

    for (size_t text_index = 0; text_index < _text.size(); ++text_index)
    {
        bool isEol = (_text[text_index] == '\n');
        if (isEol || rect.max.x < pos.x)
        {
            pos.y++;
            pos.x = rect.min.x;
            if (isEol)
                continue;
        }

        if (rect.max.y - 2 < pos.y)
            break;

        Rune r(_color.bg, _text_color, _text[text_index]);
        AddCh(pos.y, pos.x++, r);
    }

    int w = (rect.w / 2);
    string yes = "< YES >";
    pos.x = rect.min.x + ((w - yes.size()) / 2);
    for (size_t i = 0; i < yes.size(); ++i)
    {
        Style style = (_is_yes ? _active : _inactive);
        Rune r(style, yes[i]);
        AddCh(rect.max.y - 1, pos.x++, r);
    }

    string no = "< NO >";
    pos.x = rect.max.x - ((w + no.size()) / 2);
    for (size_t i = 0; i < no.size(); ++i)
    {
        Style style = (_is_yes ? _inactive : _active);
        Rune r(style, no[i]);
        AddCh(rect.max.y - 1, pos.x++, r);
    }
    Render();
}

Input::Input()
{
    _is_box = false;
    _is_active = false;
    _active = th::Get()._input.active;
    _inactive = th::Get()._input.inactive;
    _key_default = bind(&Input::KeyDefault, this, placeholders::_1);
}

Input::~Input()
{
}

const string Input::GetText()
{
    string text(_text.begin(), _text.end());
    const string trim_space = "\t\n\v";
    string rtrim = text.erase(text.find_last_not_of(trim_space) + 1);
    string ltrim = rtrim.erase(0, rtrim.find_first_not_of(trim_space));
    return ltrim;
}

void Input::SetText(string s)
{
    for (size_t i = 0; i < s.size(); ++i)
        AddText(s[i]);
}

void Input::Draw()
{
    if (!_is_visible)
        return;

    DrawBase();
    Rect rect = GetWinRect();
    Pos pos(rect.min.y, rect.min.x);

    for (int y = rect.min.y; y <= rect.max.y; ++y)
        for (int x = rect.min.x; x <= rect.max.x; ++x)
            AddCh(y, x, {COLOR_BLACK, COLOR_WHITE, A_UNDERLINE, ' '});

    for (size_t text_index = 0; text_index < _text.size(); ++text_index)
    {
        if (rect.max.x < pos.x)
        {
            pos.y++;
            pos.x = rect.min.x;
        }

        if (rect.max.y < pos.y)
            break;

        Style style;
        if (_is_active)
            style = _active;
        else
            style = _inactive;

        Rune r(style, _text[text_index]);
        AddCh(pos.y, pos.x++, r);
    }

    if (pos.x < rect.max.x && _is_active)
    {
        Style style(COLOR_BLACK, COLOR_WHITE, A_UNDERLINE | A_STANDOUT);
        Rune r(style, ' ');
        AddCh(pos.y, pos.x++, r);
    }
    Render();
}

void Input::AddText(chtype c)
{
    Rect rect = GetWinRect();
    if ((int)_text.size() < ((rect.max.y + 1) * rect.w))
        _text.push_back(c);
}

void Input::DelText()
{
    if (!_text.empty())
        _text.pop_back();
}

void Input::ClearText()
{
    _text.clear();
}

void Input::KeyDefault(KeyboardArgs args)
{
    switch(args.ch)
    {
    case KEY_BACKSPACE:
        DelText();
        break;
    case KEY_DL:
        ClearText();
        break;
    default:
        AddText((chtype)args.ch);
        break;
    }
}

Tab::Tab()
{
    _is_box = false;
    _active = th::Get()._tab.active;
    _inactive = th::Get()._tab.inactive;
    _active_index = 0;
    _type = TAB;
}

Tab::~Tab()
{
}

void Tab::ForcusLeft()
{
    if (0 < _active_index)
        _active_index--;
}

void Tab::ForcusRight()
{
    if (_active_index < (int)(_tabs.size() - 1))
        _active_index++;
}

void Tab::Draw()
{
    if (!_is_visible)
        return;

    DrawBase();
    Rect rect = GetWinRect();
    Pos pos(rect.min.y, rect.min.x);

    for (size_t tab_index = 0; tab_index < _tabs.size(); ++tab_index)
    {
        string text(_tabs[tab_index]);
        for (size_t text_index = 0; text_index < text.size(); ++text_index)
        {
            if (rect.max.x < pos.x)
                return;

            Style style;
            if (_active_index == (int)tab_index)
                style = _active;
            else
                style = _inactive;

            Rune r(style, text[text_index]);
            AddCh(pos.y, pos.x++, r);
        }

        if (tab_index != _tabs.size() - 1)
            AddCh(pos.y, pos.x++, ACS_VLINE);
    }
    Render();
}

List::List()
{
    _active = th::Get()._list.active;
    _inactive = th::Get()._list.inactive;
    _currow = 0;
    _toprow = 0;
}

List::~List()
{
}

void List::ScrollAmount(int amount)
{
    if ((int)_rows.size() - _currow <= amount)
        _currow = _rows.size() - 1;
    else if (_currow + amount < 0)
        _currow = 0;
    else
        _currow += amount;
}

void List::ScrollUp()
{
    ScrollAmount(-1);
}

void List::ScrollDown()
{
    ScrollAmount(1);
}

void List::ScrollPageUp()
{
    int h = GetWinRect().h;
    if (_toprow < _currow)
        _currow = _toprow;
    else
        ScrollAmount(-h);
}

void List::ScrollPageDown()
{
    int h = GetWinRect().h;
    ScrollAmount(h);
}

void List::ScrollTop()
{
    _currow = 0;
}

void List::ScrollBottom()
{
    _currow = _rows.size() - 1;
}

void List::Draw()
{
    if (!_is_visible)
        return;

    DrawBase();
    Rect rect = GetWinRect();
    Pos pos(rect.min.y, rect.min.x);

    if (rect.h + _toprow <= _currow)
        _toprow = _currow - rect.h + 1;
    else if (_currow < _toprow)
        _toprow = _currow;

    for (size_t row_index = _toprow; row_index < _rows.size(); ++row_index)
    {
        string text(_rows[row_index]);
        for (size_t text_index = 0; text_index < text.size(); ++text_index)
        {
            if (rect.max.x < pos.x)
                break;

            Style style;
            if ((int)row_index == _currow)
                style = _active;
            else
                style = _inactive;

            Rune r(style, text[text_index]);
            AddCh(pos.y, pos.x++, r);
        }

        pos.x = rect.min.x;
        pos.y++;
        if (rect.max.y < pos.y)
            break;
    }

    if (0 < _toprow)
    {
        Rune r(ACS_DIAMOND);
        AddCh(rect.min.y, rect.max.x, r);
    }

    if (_toprow + rect.h < (int)_rows.size())
    {
        Rune r(ACS_DIAMOND);
        AddCh(rect.max.y, rect.max.x, r);
    }
    Render();
}

ProgressBar::ProgressBar()
{
    _bar_color = th::Get()._progress.bar;
    _percent = 0;
}

ProgressBar::~ProgressBar()
{
}

void ProgressBar::Draw()
{
    if (!_is_visible)
        return;

    DrawBase();
    Rect rect = GetWinRect();
    Pos pos(rect.min.y, rect.min.x);

    string label;
    if (_label.empty())
        label = to_string(_percent) + "%";
    else
        label = _label;

    int bar_width = int(float(_percent * 0.01) * rect.w);
    while (pos.y <= rect.max.y)
    {
        Rune r(_bar_color, COLOR_BLACK, ' ');
        while (pos.x <= rect.min.x + bar_width)
        {
            if (rect.max.x < pos.x)
                break;
            AddCh(pos.y, pos.x, r);
            pos.x++;
        }
        pos.y++;
        pos.x = rect.min.x;
    }

    pos.y = rect.min.y + (rect.h / 2);
    pos.x = rect.min.x + (rect.w / 2) - (label.length() / 2);
    if (rect.max.y < pos.y)
        return;

    for (size_t label_index = 0; label_index < label.size(); ++label_index)
    {
        Style style(_label_style);
        if (pos.x + (int)label_index <= rect.min.x + bar_width)
            style = {COLOR_BLACK, _bar_color, A_REVERSE};
        Rune r(style, label[label_index]);
        AddCh(pos.y, pos.x + label_index, r);
    }
    Render();
}

Table::Table()
{
    _alignment = LEFT;
}

Table::~Table()
{
}

void Table::Draw()
{
    if (!_is_visible)
        return;

    DrawBase();
    Rect rect = GetWinRect();
    Pos pos(rect.min.y, rect.min.x);

    int colCnt = _rows[0].size();
    int colWidth = rect.w / colCnt;

    for (size_t row = 0; row < _rows.size(); ++row)
    {
        vector<string> cols(_rows[row]);
        for (size_t col = 0; col < cols.size(); ++col)
        {
            string text(cols[col]);
            if (colWidth < (int)text.length() || _alignment == LEFT)
                pos.x = rect.min.x + (col * colWidth);
            else if (_alignment == CENTER)
                pos.x += (colWidth - text.length()) / 2;
            else if (_alignment == RIGHT)
            {
                if (pos.x + colWidth < rect.max.x)
                    pos.x += colWidth - text.length();
                else
                    pos.x = rect.max.x - text.length() + 1;
            }

            int oneColMax = (rect.min.x + (colWidth * (col + 1)));
            for (size_t strIdx = 0; pos.x < oneColMax; ++pos.x)
            {
                if (text[strIdx] == 0x00)
                    continue;
                AddCh(pos.y, pos.x, text[strIdx++]);
            }

            if (col != cols.size() - 1)
                AddCh(pos.y, pos.x - 1, ACS_VLINE);
            else
                pos.y++;
        }

        if (rect.max.y < pos.y)
            break;

        for (int x = rect.min.x; x <= rect.max.x; ++x)
            AddCh(pos.y, x, ACS_S3);

        pos.y++;
        pos.x = rect.min.x;
    }
    Render();
}

BarChart::BarChart()
{
    _num_color = th::Get()._bar.number;
    _bar_color.push_back(th::Get()._bar.bar);
    _label_style.push_back(th::Get()._bar.label);
    _bar_gap = 1;
    _bar_width = 3;
    _max_val = 0;
}

BarChart::~BarChart()
{
}

void BarChart::Draw()
{
    if (!_is_visible)
        return;

    DrawBase();
    Rect rect = GetWinRect();

    int max_val = _max_val;
    if (max_val == 0)
        max_val = *max_element(_data.begin(), _data.end());

    int bar_x = rect.min.x + 1;
    for (size_t col = 0; col < _data.size(); ++col)
    {
        float val = _data[col];
        int h = (((float)(val / max_val)) * (rect.h - 2));
        int w = 0;
        if (bar_x + _bar_width < rect.max.x)
            w = bar_x + _bar_width;
        else
            w = rect.max.x;

        for (int y = rect.max.y - 2; (rect.max.y - 2) - h < y; y--)
        {
            for (int x = bar_x; x < w; x++)
            {
                Rune r(GetBarColor(col));
                r.c = ' ';
                AddCh(y, x, r);
            }
        }

        if (col < _label.size())
        {
            string label(_label[col]);
            int labalX = bar_x + (float)(_bar_width / 2) - (float)(label.size() / 2);

            for (size_t i = 0; i < label.size(); ++i)
            {
                Rune r(GetLabelStyle(col));
                r.c = label[i];
                AddCh(rect.max.y - 1, labalX++, r);
            }
        }

        int numX = bar_x + (float)(_bar_width / 2);
        if (numX <= rect.max.x)
        {
            string num(to_string((int)val));
            for (size_t i = 0; i < num.size(); ++i)
            {
                Rune r(GetNumberStyle(col));
                r.c = num[i];
                AddCh(rect.max.y - 2, numX, r);
            }
        }

        bar_x += _bar_width + _bar_gap;
    }
    Render();
}

Rune BarChart::GetBarColor(int index)
{
    Rune r;
    r.s.fg = _bar_color[index % _bar_color.size()];
    r.s.bg = _bar_color[index % _bar_color.size()];
    return r;
}

Rune BarChart::GetLabelStyle(int index)
{
    Rune r;
    r.s = _label_style[index % _label_style.size()];
    return r;
}

Rune BarChart::GetNumberStyle(int index)
{
    Rune r(GetBarColor(index));
    r.s.bg = COLOR_BLACK;
    r.s.opt = A_REVERSE;
    return r;
}

Radio::Radio()
{
    _is_box = false;
    _active = th::Get()._checkbox.active;
    _inactive = th::Get()._checkbox.inactive;
}

Radio::~Radio()
{
}

void Radio::Draw()
{
    if (!_is_visible)
        return;

    DrawBase();
    Rect rect = GetWinRect();
    Pos pos(rect.min.y, rect.min.x);

    Style style;
    if (_is_check)
        style = _active;
    else
        style = _inactive;

    Rune r(style, _is_check ? 'o' : ' ');
    pos.x += 2;

    for (size_t text_index = 0; text_index < _text.size(); ++text_index)
    {
        if (rect.max.x < pos.x)
            break;

        AddCh(pos.y, pos.x++, _text[text_index]);
    }

    Render();
}

CheckBox::CheckBox()
{
    _is_box = false;
    _active = th::Get()._checkbox.active;
    _inactive = th::Get()._checkbox.inactive;
}

CheckBox::~CheckBox()
{
}

void CheckBox::Draw()
{
    if (!_is_visible)
        return;

    DrawBase();
    Rect rect = GetWinRect();
    Pos pos(rect.min.y, rect.min.x);

    Style style;
    if (_is_check)
        style = _active;
    else
        style = _inactive;

    Rune r(style, _is_check ? 'v' : ' ');
    AddCh(pos.y, pos.x, r);
    pos.x += 2;

    for (size_t text_index = 0; text_index < _text.size(); ++text_index)
    {
        if (rect.max.x < pos.x)
            break;

        AddCh(pos.y, pos.x++, _text[text_index]);
    }

    Render();
}