#include "Widget.h"
#include "Theme.h"

Widget::Widget()
{
}

Widget::~Widget()
{
}

Basic::Basic()
{
    _textColor = th::Get()._basic.textColor;
    _text.clear();
}

Basic::~Basic()
{
}

void Basic::SetTextColor(int textColor)
{
    _textColor = textColor;
}

void Basic::SetText(string text)
{
    _text = text;
}

void Basic::Draw()
{
    Pos pos(_inner.min.y, _inner.min.x);

    for (size_t idx = 0; idx < _text.size(); ++idx)
    {
        bool isEol = (_text[idx] == '\n');
        if (isEol || _inner.max.x < pos.x)
        {
            pos.y++;
            pos.x = _inner.min.x;
            if (isEol)
                continue;
        }

        if (_inner.max.y < pos.y)
            break;

        int bg = th::Get()._base.color.bg;
        Rune r(bg, _textColor, _text[idx]);
        AddCh(pos.y, pos.x++, r);
    }
}

Button::Button()
{
    _active = th::Get()._btn.active;
    _inactive = th::Get()._btn.inactive;
    _isActive = false;
}

Button::~Button()
{
}

void Button::Draw()
{
    Pos pos(_inner.min.y, _inner.min.x);

    for (size_t idx = 0; idx < _text.size(); ++idx)
    {
        if (_inner.max.x < pos.x)
            return;

        if (_isActive)
        {
            Rune r(_active, _text[idx]);
            AddCh(pos.y, pos.x++, r);
        }
        else
        {
            Rune r(_inactive, _text[idx]);
            AddCh(pos.y, pos.x++, r);
        }
    }
}

Input::Input()
{
    _active = th::Get()._input.active;
    _inactive = th::Get()._input.inactive;
    _isActive = false;
}

Input::~Input()
{
}

const string Input::GetText()
{
    string text(_text.begin(), _text.end());
    return text;
}

void Input::SetText(string s)
{
    for (size_t i = 0; i < s.size(); ++i)
        AddText(s[i]);
}

void Input::AddText(chtype c)
{
    if ((int)_text.size() < ((_rect.max.y + 1) * _rect.w))
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

void Input::Draw()
{
    Pos pos(_rect.min.y, _rect.min.x);

    for (int y = _rect.min.y; y <= _rect.max.y; ++y)
        for (int x = _rect.min.x; x <= _rect.max.x; ++x)
            AddCh(y, x, {COLOR_BLACK, COLOR_WHITE, A_UNDERLINE, ' '});

    for (size_t idx = 0; idx < _text.size(); ++idx)
    {
        if (_rect.max.x < pos.x)
        {
            pos.y++;
            pos.x = _rect.min.x;
        }

        if (_rect.max.y < pos.y)
            break;

        Style style;
        if (_isActive)
            style = _active;
        else
            style = _inactive;
        Rune r(style, _text[idx]);
        AddCh(pos.y, pos.x++, r);
    }

    if (pos.x < _rect.max.x && _isActive)
    {
        Style style(COLOR_WHITE, COLOR_BLACK, A_UNDERLINE | A_BLINK);
        Rune r(style, ' ');
        AddCh(pos.y, pos.x++, r);
    }
}

Tab::Tab()
{
    _activeStyle = th::Get()._tab.active;
    _inactiveStyle = th::Get()._tab.inactive;
    _activeIdx = 0;
}

Tab::~Tab()
{
}

void Tab::ForcusLeft()
{
    if (0 < _activeIdx)
        _activeIdx--;
}

void Tab::ForcusRight()
{
    if (_activeIdx < (int)(_tabs.size() - 1))
        _activeIdx++;
}

void Tab::Draw()
{
    Pos pos(_inner.min.y, _inner.min.x);

    for (size_t tabIdx = 0; tabIdx < _tabs.size(); ++tabIdx)
    {
        string text(_tabs[tabIdx]);
        for (size_t idx = 0; idx < text.size(); ++idx)
        {
            if (_inner.max.x < pos.x)
                return;

            Style style;
            if (_activeIdx == (int)tabIdx)
                style = _activeStyle;
            else
                style = _inactiveStyle;

            Rune r(style, text[idx]);
            AddCh(pos.y, pos.x++, r);
        }
        AddCh(pos.y, pos.x++, ACS_VLINE);
    }
}

List::List()
{
    _activeStyle = th::Get()._list.active;
    _inactiveStyle = th::Get()._list.inactive;
    _curRow = 0;
    _topRow = 0;
}

List::~List()
{
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
    if (_topRow < _curRow)
        _curRow = _topRow;
    else
        ScrollAmount(-_inner.h);
}

void List::ScrollPageDown()
{
    ScrollAmount(_inner.h);
}

void List::ScrollTop()
{
    _curRow = 0;
}

void List::ScrollBottom()
{
    _curRow = _rows.size() - 1;
}

void List::ScrollAmount(int amount)
{
    if ((int)_rows.size() - _curRow <= amount)
        _curRow = _rows.size() - 1;
    else if (_curRow + amount < 0)
        _curRow = 0;
    else
        _curRow += amount;
}

void List::Draw()
{
    Pos pos(_inner.min.y, _inner.min.x);

    if (_inner.h + _topRow <= _curRow)
        _topRow = _curRow - _inner.h + 1;
    else if (_curRow < _topRow)
        _topRow = _curRow;

    for (size_t rowIdx = _topRow; rowIdx < _rows.size(); ++rowIdx)
    {
        string text(_rows[rowIdx]);
        for (size_t idx = 0; idx < text.size(); ++idx)
        {
            if (_inner.max.x < pos.x)
                break;

            Style style;
            if ((int)rowIdx == _curRow)
                style = _activeStyle;
            else
                style = _inactiveStyle;

            Rune r(style, text[idx]);
            AddCh(pos.y, pos.x++, r);
        }

        pos.x = _inner.min.x;
        pos.y++;
        if (_inner.max.y < pos.y)
            break;
    }

    if (0 < _topRow)
    {
        Rune r(ACS_DIAMOND);
        AddCh(_inner.min.y, _inner.max.x, r);
    }

    if (_topRow + _inner.h < (int)_rows.size())
    {
        Rune r(ACS_DIAMOND);
        AddCh(_inner.max.y, _inner.max.x, r);
    }
}

ProgressBar::ProgressBar()
{
    _barColor = th::Get()._progress.bar;
    _refresh = false;
    _percent = 0;
}

ProgressBar::~ProgressBar()
{
}

void ProgressBar::Draw()
{
    Pos pos(_inner.min.y, _inner.min.x);

    string label;
    if (_label.empty())
        label = to_string(_percent) + "%";
    else
        label = _label;

    int barWidth = int(float(_percent * 0.01) * _inner.w);
    while (pos.y <= _inner.max.y)
    {
        Rune r(_barColor, COLOR_BLACK, ' ');
        while (pos.x <= _inner.min.x + barWidth)
        {
            if (_inner.max.x < pos.x)
                break;
            AddCh(pos.y, pos.x, r);
            pos.x++;
        }
        pos.y++;
        pos.x = _inner.min.x;
    }

    pos.y = _inner.min.y + (_inner.h / 2);
    pos.x = _inner.min.x + (_inner.w / 2) - (label.length() / 2);
    if (_inner.max.y < pos.y)
        return;

    for (size_t idx = 0; idx < label.size(); ++idx)
    {
        Style style(_labelStyle);
        if (pos.x + (int)idx <= _inner.min.x + barWidth)
            style = {COLOR_BLACK, _barColor, A_REVERSE};
        Rune r(style, label[idx]);
        AddCh(pos.y, pos.x + idx, r);
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
    Pos pos(_inner.min.y, _inner.min.x);

    int colCnt = _rows[0].size();
    int colWidth = _inner.w / colCnt;

    for (size_t row = 0; row < _rows.size(); ++row)
    {
        vector<string> cols(_rows[row]);
        for (size_t col = 0; col < cols.size(); ++col)
        {
            string text(cols[col]);
            if (colWidth < (int)text.length() || _alignment == LEFT)
                pos.x = _inner.min.x + (col * colWidth);
            else if (_alignment == CENTER)
                pos.x += (colWidth - text.length()) / 2;
            else if (_alignment == RIGHT)
            {
                if (pos.x + colWidth < _inner.max.x)
                    pos.x += colWidth - text.length();
                else
                    pos.x = _inner.max.x - text.length() + 1;
            }

            int oneColMax = (_inner.min.x + (colWidth * (col + 1)));
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

        if (_inner.max.y < pos.y)
            break;

        for (int x = _inner.min.x; x <= _inner.max.x; ++x)
            AddCh(pos.y, x, ACS_S3);

        pos.y++;
        pos.x = _inner.min.x;
    }
}

BarChart::BarChart()
{
    _barColor.push_back(th::Get()._bar.bar);
    _labelStyle.push_back(th::Get()._bar.label);
    _barGap = 1;
    _barWidth = 3;
    _maxVal = 0;
}

BarChart::~BarChart()
{
}

void BarChart::Draw()
{
    int maxVal = _maxVal;
    if (maxVal == 0)
        maxVal = *max_element(_data.begin(), _data.end());

    int barX = _inner.min.x + 1;
    for (size_t col = 0; col < _data.size(); ++col)
    {
        float val = _data[col];
        int h = (((float)(val / maxVal)) * (_inner.h - 2));
        int w = 0;
        if (barX + _barWidth < _inner.max.x)
            w = barX + _barWidth;
        else
            w = _inner.max.x;

        for (int y = _inner.max.y - 2; (_inner.max.y - 2) - h < y; y--)
        {
            for (int x = barX; x < w; x++)
            {
                Rune r(GetBarColor(col));
                r.c = ' ';
                AddCh(y, x, r);
            }
        }

        if (col < _label.size())
        {
            string label(_label[col]);
            int labalX = barX + (float)(_barWidth / 2) - (float)(label.size() / 2);

            for (size_t i = 0; i < label.size(); ++i)
            {
                Rune r(GetLabelStyle(col));
                r.c = label[i];
                AddCh(_inner.max.y - 1, labalX++, r);
            }
        }

        int numX = barX + (float)(_barWidth / 2);
        if (numX <= _inner.max.x)
        {
            string num(to_string((int)val));
            for (size_t i = 0; i < num.size(); ++i)
            {
                Rune r(GetNumberStyle(col));
                r.c = num[i];
                AddCh(_inner.max.y - 2, numX, r);
            }
        }

        barX += _barWidth + _barGap;
    }
}

Rune BarChart::GetBarColor(int idx)
{
    Rune r;
    r.s.fg = _barColor[idx % _barColor.size()];
    r.s.bg = _barColor[idx % _barColor.size()];
    return r;
}

Rune BarChart::GetLabelStyle(int idx)
{
    Rune r;
    r.s = _labelStyle[idx % _labelStyle.size()];
    return r;
}

Rune BarChart::GetNumberStyle(int idx)
{
    Rune r(GetBarColor(idx));
    r.s.bg = COLOR_BLACK;
    r.s.opt = A_REVERSE;
    return r;
}

Form::Form()
{
}

Form::~Form()
{
}

vector<string> Form::GetItems()
{
}

void Form::Draw()
{
    // int centerX = (_inner.w / 2);
    // for (int x = centerX + 1; x < _inner.max.w - 1; ++x)
    // {
    //     AddCh()
    // };

    Pos pos(_inner.min.y, _inner.min.x);
    int colWidth = (_inner.w / 2) / _query.size();

    // pos.x += (colWidth - text.length()) / 2;
    for (size_t idx = 0; idx < _default.size(); ++idx)
    {
        string text(_default[idx]);
        int w = (_inner.w / 2);
        int h = text.size() / w;
        if (h < (float)text.size() / w)
            h += 1;
        Input input;
        input.SetRect(h, w, _inner.min.y, w + 1);
        input.SetText("hihihi");
        input.Draw();
        AttachCells(input.GetCells());

        for (size_t i = 0; i < text.size(); i++)
        {
        }

        // input.SetRect(pos.y, w, pos.y, center + 1);
        // input.Draw();
        // AttachCells(input.GetCells());
        // Log("[%s]", input.GetText().c_str());
    }

    // for (size_t def = 0; def < _default.size(); ++def)
    // {
    // }
}