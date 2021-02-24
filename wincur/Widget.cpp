#include "Widget.h"
#include "Theme.h"
#include "Paint.h"

TextBox::TextBox()
{
    _style = th::Get()._textbox.style;
    _box = false;
}

TextBox::~TextBox()
{
}

void TextBox::Draw()
{
    if (!_visible)
        return;

    DrawBase();
    Rect rect = GetWinRect();
    Pos pos(rect.min.x, rect.min.x);
    for (size_t text_index = 0; text_index < _text.size(); ++text_index)
    {
        bool is_EOL = (_text[text_index] == L'\n');
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
        AddCh(pos.y, pos.x, r);

        if (Util::IsHangle(_text[text_index]))
            pos.x += 2;
        else
            pos.x += 1;
    }
    wrefresh(_window);
}

Button::Button()
{
    _active_style = th::Get()._button.active;
    _inactive_style = th::Get()._button.inactive;
    _key_default = bind(&Button::KeyDefault, this, placeholders::_1);
}

Button::~Button()
{
}

void Button::Draw()
{
    if (!_visible)
        return;

    DrawBase();
    Rect rect = GetWinRect();
    Pos pos(rect.min.y, rect.min.x);

    if (rect.w < (int)_text.size())
        pos.x = rect.min.x;
    else
        pos.x = (rect.min.x + ((rect.w - _text.size()) / 2)) - 1;

    for (size_t text_index = 0; text_index < _text.size(); ++text_index)
    {
        if (rect.max.x < pos.x)
            break;

        Style style;
        if (_is_active)
            style = _active_style;
        else
            style = _inactive_style;

        Rune r(style, _text[text_index]);
        AddCh(pos.y, pos.x, r);

        if (Util::IsHangle(_text[text_index]))
            pos.x += 2;
        else
            pos.x += 1;
    }
    wrefresh(_window);
}

void Button::KeyDefault(KeyboardArgs args)
{
    switch (args.ch)
    {
    case ' ':
    case 10:
        if (_click)
            _click(EventArgs());
        break;
    default:
        break;
    }
}

Input::Input()
{
    _box = false;
    _is_active = false;
    _active_style = th::Get()._input.active;
    _inactive_style = th::Get()._input.inactive;
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
    if (!_visible)
        return;

    DrawBase();
    Rect rect = GetWinRect();
    Pos pos(rect.min.y, rect.min.x);

    for (int y = rect.min.y; y <= rect.max.y; ++y)
    {
        for (int x = rect.min.x; x <= rect.max.x; ++x)
        {
            Rune r({COLOR_BLACK, COLOR_WHITE, WA_UNDERLINE}, ' ');
            AddCh(y, x, r);
        }
    }

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
            style = _active_style;
        else
            style = _inactive_style;

        Rune r(style, _text[text_index]);
        AddCh(pos.y, pos.x, r);

        if (Util::IsHangle(_text[text_index]))
            pos.x += 2;
        else
            pos.x += 1;
    }

    if (pos.x < rect.max.x && _is_active)
    {
        Style style(COLOR_BLACK, COLOR_WHITE, WA_UNDERLINE | WA_STANDOUT);
        Rune r(style, ' ');
        AddCh(pos.y, pos.x++, r);
    }
    wrefresh(_window);
}

void Input::AddText(int ch)
{
    Rect rect = GetWinRect();
    if ((int)_text.size() < ((rect.max.y + 1) * rect.w))
        _text.push_back(ch);
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
    case KEY_ENTER:
    case 10:
        break;
        break;
    case KEY_BACKSPACE:
        DelText();
        break;
    case KEY_DC:
        ClearText();
        break;
    case KEY_DL:
        ClearText();
        break;
    default:
        if (iswalnum(args.ch) || args.ch == 95 ||
            args.ch == 46 || args.ch == 58)
            AddText(args.ch);
        break;
    }
}

Tab::Tab()
{
    _box = false;
    _active_style = th::Get()._tab.active;
    _inactive_style = th::Get()._tab.inactive;
    _active_index = 0;
}

Tab::~Tab()
{
}

void Tab::FocusLeft()
{
    if (0 < _active_index)
        _active_index--;
}

void Tab::FocusRight()
{
    if (_active_index < (int)(_tabs.size() - 1))
        _active_index++;
}

void Tab::Draw()
{
    if (!_visible)
        return;

    DrawBase();
    Rect rect = GetWinRect();
    Pos pos(rect.min.y, rect.min.x);

    for (size_t tab_index = 0; tab_index < _tabs.size(); ++tab_index)
    {
        wstring text(_tabs[tab_index]);
        for (size_t text_index = 0; text_index < text.size(); ++text_index)
        {
            if (rect.max.x < pos.x)
                return;

            Style style;
            if (_active_index == (int)tab_index)
                style = _active_style;
            else
                style = _inactive_style;

            Rune r(style, text[text_index]);
            AddCh(pos.y, pos.x, r);
            if (Util::IsHangle(r.wch))
                pos.x += 2;
            else
                pos.x += 1;
        }

        if (tab_index != _tabs.size() - 1)
            AddCh(pos.y, pos.x++, WACS_T_VLINE);
    }

    pos.y += 1;
    for (int i = 0; i < COLS; ++i)
        AddCh(pos.y, i, WACS_D_HLINE);

    wrefresh(_window);
}

List::List()
{
    _active_style = th::Get()._list.active;
    _inactive_style = th::Get()._list.inactive;
    _currow = 0;
    _toprow = 0;
    _key_default = bind(&List::KeyDefault, this, placeholders::_1);
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
    if (!_visible)
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
        wstring text(_rows[row_index]);
        for (size_t text_index = 0; text_index < text.size(); ++text_index)
        {
            if (rect.max.x < pos.x)
                break;

            Style style;
            if ((int)row_index == _currow)
                style = _active_style;
            else
                style = _inactive_style;

            Rune r(style, text[text_index]);
            AddCh(pos.y, pos.x, r);
            if (Util::IsHangle(r.wch))
                pos.x += 2;
            else
                pos.x += 1;
        }

        pos.x = rect.min.x;
        pos.y++;
        if (rect.max.y < pos.y)
            break;
    }

    if (0 < _toprow)
        AddCh(rect.min.y, rect.max.x, WACS_UARROW);

    if (_toprow + rect.h < (int)_rows.size())
        AddCh(rect.max.y, rect.max.x, WACS_DARROW);

    wrefresh(_window);
}

void List::KeyDefault(KeyboardArgs args)
{
    switch(args.ch)
    {
    case KEY_UP:
        ScrollUp();
        break;
    case KEY_DOWN:
        ScrollDown();
        break;
    case KEY_HOME:
        ScrollTop();
        break;
    case KEY_END:
        ScrollBottom();
        break;
    case KEY_PPAGE:
        ScrollPageUp();
        break;
    case KEY_NPAGE:
        ScrollPageDown();
        break;
    default:
        break;
    }
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
    if (!_visible)
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
            style = {COLOR_BLACK, _bar_color, WA_REVERSE};
        Rune r(style, label[label_index]);
        AddCh(pos.y, pos.x + label_index, r);
    }
    // Render();
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
    if (!_visible)
        return;

    DrawBase();
    Rect rect = GetWinRect();
    Pos pos(rect.min.y, rect.min.x);

    int colCnt = _rows[0].size();
    int colWidth = rect.w / colCnt;

    for (size_t row = 0; row < _rows.size(); ++row)
    {
        vector<wstring> cols(_rows[row]);
        for (size_t col = 0; col < cols.size(); ++col)
        {
            wstring text(cols[col]);
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
            for (size_t strIdx = 0; pos.x < oneColMax;)
            {
                if (text[strIdx] == 0x00)
                    continue;
                wchar_t wch = text[strIdx++];
                AddCh(pos.y, pos.x, wch);
                if (Util::IsHangle(wch))
                    pos.x += 2;
                else
                    pos.x += 1;
            }

            if (col != cols.size() - 1)
                AddCh(pos.y, pos.x - 1, WACS_VLINE);
            else
                pos.y++;
        }

        if (rect.max.y < pos.y)
            break;

        for (int x = rect.min.x; x <= rect.max.x; ++x)
            AddCh(pos.y, x, WACS_S3);

        pos.y++;
        pos.x = rect.min.x;
    }
    // Render();
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
    if (!_visible)
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
                r.wch = ' ';
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
                r.wch = label[i];
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
                r.wch = num[i];
                AddCh(rect.max.y - 2, numX, r);
            }
        }

        bar_x += _bar_width + _bar_gap;
    }
    // Render();
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
    r.s.opt = WA_REVERSE;
    return r;
}

Radio::Radio()
{
    _box = false;
    _active = th::Get()._radio.active;
    _inactive = th::Get()._radio.inactive;
}

Radio::~Radio()
{
}

void Radio::Draw()
{
    if (!_visible)
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

    // Render();
}

CheckBox::CheckBox()
{
    _box = false;
    _style = th::Get()._checkbox.style;
    _key_default = bind(&CheckBox::KeyDefault, this, placeholders::_1);
}

CheckBox::~CheckBox()
{
}

void CheckBox::Draw()
{
    if (!_visible)
        return;

    DrawBase();
    Rect rect = GetWinRect();
    Pos pos(rect.min.y, rect.min.x);

    Rune r(_style, _checked ? 'v' : ' ');
    AddCh(pos.y, pos.x, r);
    pos.x += 2;

    for (size_t text_index = 0; text_index < _text.size(); ++text_index)
    {
        if (rect.max.x < pos.x)
            break;

        wchar_t wch = _text[text_index];
        AddCh(pos.y, pos.x, wch);
        if (Util::IsHangle(wch))
            pos.x += 2;
        else
            pos.x += 1;
    }

    // Render();
}

void CheckBox::KeyDefault(KeyboardArgs args)
{
    switch (args.ch)
    {
    case ' ':
    case 10:
        if (_click)
            _click(EventArgs());
        if (_checked)
            _checked = false;
        else
            _checked = true;
        break;
    default:
        break;
    }
}