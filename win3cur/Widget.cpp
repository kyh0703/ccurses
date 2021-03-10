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
    Rect rect = GetDrawRect();
    Pos pos(rect.min.y, rect.min.x);

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
        pos.x += (Util::IsHangle(_text[text_index]) ? 2 : 1);
    }
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
    Rect rect = GetDrawRect();
    Pos pos(rect.min.y, rect.min.x);

    int win_text_len = Util::GetTextSize(_text);
    if (rect.w < (int)_text.size())
        pos.x = rect.min.x;
    else
        pos.x = (rect.min.x + ((rect.w - win_text_len) / 2));

    for (size_t text_index = 0; text_index < _text.size(); ++text_index)
    {
        if (rect.max.x < pos.x)
            break;

        Style style;
        if (_focus)
            style = _active_style;
        else
            style = _inactive_style;

        Rune r(style, _text[text_index]);
        AddCh(pos.y, pos.x, r);
        pos.x += (Util::IsHangle(_text[text_index]) ? 2 : 1);
    }
}

void Button::KeyDefault(KeyboardArgs args)
{
    switch (args.wch)
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
    _active_style = th::Get()._input.active;
    _inactive_style = th::Get()._input.inactive;
    _key_default = bind(&Input::KeyDefault, this, placeholders::_1);
}

Input::~Input()
{
}

const wstring Input::GetText()
{
    wstring text(_text.begin(), _text.end());
    const wstring trim_space = L"\t\n\v";
    wstring rtrim = text.erase(text.find_last_not_of(trim_space) + 1);
    wstring ltrim = rtrim.erase(0, rtrim.find_first_not_of(trim_space));
    return ltrim;
}

void Input::SetText(wstring s)
{
    for (size_t i = 0; i < s.size(); ++i)
        AddText(s[i]);
}

void Input::AddStr(wstring wstr)
{
    for (size_t index = 0; index < wstr.size(); ++index)
        if ((int)_text.size() < ((_rect.max.y + 1) * _rect.w))
            _text.push_back(wstr[index]);
}

void Input::AddText(wint_t wch)
{
    if ((int)_text.size() < ((_rect.max.y + 1) * _rect.w))
        _text.push_back(wch);
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

void Input::Draw()
{
    if (!_visible)
        return;

    DrawBase();
    Rect rect = GetDrawRect();
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
        if (_focus)
            style = _active_style;
        else
            style = _inactive_style;

        Rune r(style, _text[text_index]);
        AddCh(pos.y, pos.x, r);
        pos.x += (Util::IsHangle(_text[text_index]) ? 2 : 1);
    }

    if (pos.x < rect.max.x && _focus)
    {
        Style style(COLOR_BLACK, COLOR_WHITE, WA_UNDERLINE | WA_STANDOUT);
        Rune r(style, ' ');
        AddCh(pos.y, pos.x++, r);
    }
}

void Input::KeyDefault(KeyboardArgs args)
{
    switch(args.wch)
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
        if (iswalnum(args.wch) || args.wch == 95 ||
            args.wch == 46 || args.wch == 58)
            AddText(args.wch);
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
    Rect rect = GetDrawRect();
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
            pos.x += (Util::IsHangle(r.wch) ? 2 : 1);
        }

        if (tab_index != _tabs.size() - 1)
            AddCh(pos.y, pos.x++, WACS_D_VLINE);
    }

    pos.y += 1;
    for (int i = 0; i < COLS; ++i)
        AddCh(pos.y, i, WACS_D_HLINE);
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

wstring List::GetCurrentRow()
{
    if (_rows.empty())
        return L"";

    return _rows[_currow];
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
    if (_toprow < _currow)
        _currow = _toprow;
    else
        ScrollAmount(-_rect.h);
}

void List::ScrollPageDown()
{
    ScrollAmount(_rect.h);
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
    Rect rect = GetDrawRect();
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
            pos.x += (Util::IsHangle(r.wch) ? 2 : 1);
        }

        pos.x = rect.min.x;
        pos.y++;
        if (rect.max.y < pos.y)
            break;
    }

    if (0 < _toprow)
    {
        Rune r(L'\u2191');
        AddCh(rect.min.y, rect.max.x - 1, r);
    }

    if (_toprow + rect.h < (int)_rows.size())
    {
        Rune r(L'\u2193');
        AddCh(rect.max.y, rect.max.x, r);
    }
}

void List::KeyDefault(KeyboardArgs args)
{
    switch(args.wch)
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
    Rect rect = GetDrawRect();
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
    Rect rect = GetDrawRect();
    Pos pos(rect.min.y, rect.min.x);

    int colCnt = _rows[0].size();
    int colWidth = rect.w / colCnt;

    for (size_t row = 0; row < _rows.size(); ++row)
    {
        vector<wstring> cols(_rows[row]);
        for (size_t col = 0; col < cols.size(); ++col)
        {
            wstring text(cols[col]);
            int win_text_len = Util::GetTextSize(text);

            if (colWidth < win_text_len || _alignment == LEFT)
                pos.x = rect.min.x + (col * colWidth);
            else if (_alignment == CENTER)
                pos.x += (colWidth - win_text_len) / 2;
            else if (_alignment == RIGHT)
            {
                if (pos.x + colWidth < rect.max.x)
                    pos.x += colWidth - win_text_len;
                else
                    pos.x = rect.max.x - win_text_len + 1;
            }

            int oneColMax = (rect.min.x + (colWidth * (col + 1)));
            for (size_t strIdx = 0; pos.x < oneColMax;)
            {
                if (text[strIdx] == 0x00)
                    continue;
                wchar_t wch = text[strIdx++];
                AddCh(pos.y, pos.x, wch);
                pos.x += (Util::IsHangle(wch) ? 2 : 1);
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
    Rect rect = GetDrawRect();

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
    Rect rect = GetDrawRect();
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
    Rect rect = GetDrawRect();
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
        pos.x += (Util::IsHangle(wch) ? 2 : 1);
    }
}

void CheckBox::KeyDefault(KeyboardArgs args)
{
    switch (args.wch)
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