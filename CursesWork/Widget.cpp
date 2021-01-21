#include "Widget.h"
#include "Theme.h"

TextBox::TextBox()
{
    _style = th::Get()._textbox.style;
}

TextBox::~TextBox()
{
}

void TextBox::Draw()
{
    Rect rect = InitCell();
    Pos pos(rect.min.y, rect.min.x);

    for (size_t idx = 0; idx < _text.size(); ++idx)
    {
        bool isEol = (_text[idx] == '\n');
        if (isEol || rect.max.x < pos.x)
        {
            pos.y++;
            pos.x = rect.min.x;
            if (isEol)
                continue;
        }

        if (rect.max.y < pos.y)
            break;

        Rune r(_style, _text[idx]);
        AddCh(pos.y, pos.x++, r);
    }
}

Popup::Popup()
{
    _btnStyle = th::Get()._popup.button;
    _textColor = th::Get()._popup.textColor;
}

Popup::~Popup()
{
}

void Popup::Draw()
{
    Rect rect = InitCell();
    Pos pos(rect.min.y, rect.min.x);

    for (size_t idx = 0; idx < _text.size(); ++idx)
    {
        bool isEol = (_text[idx] == '\n');
        if (isEol || rect.max.x < pos.x)
        {
            pos.y++;
            pos.x = rect.min.x;
            if (isEol)
                continue;
        }

        if (rect.max.y - 2 < pos.y)
            break;

        int bg = th::Get()._base.color.bg;
        Rune r(bg, _textColor, _text[idx]);
        AddCh(pos.y, pos.x++, r);
    }

    string enter = "<ENTER >";
    pos.x = rect.min.x + ((rect.w - enter.size()) / 2);
    for (size_t i = 0; i < enter.size(); ++i)
    {
        Rune r(_btnStyle, enter[i]);
        AddCh(rect.max.y - 1, pos.x++, r);
    }
}

YesNo::YesNo()
{
    _textColor = th::Get()._yesno.textColor;
    _active = th::Get()._yesno.active;
    _inactive = th::Get()._yesno.inactive;
    _isYes = true;
}

YesNo::~YesNo()
{
}

void YesNo::ForcusLeft()
{
    if (!_isYes)
        _isYes = true;
}

void YesNo::ForcusRight()
{
    if (_isYes)
        _isYes = false;
}

void YesNo::Draw()
{
    Rect rect = InitCell();
    Pos pos(rect.min.y, rect.min.x);

    for (size_t idx = 0; idx < _text.size(); ++idx)
    {
        bool isEol = (_text[idx] == '\n');
        if (isEol || rect.max.x < pos.x)
        {
            pos.y++;
            pos.x = rect.min.x;
            if (isEol)
                continue;
        }

        if (rect.max.y - 2 < pos.y)
            break;

        int bg = th::Get()._base.color.bg;
        Rune r(bg, _textColor, _text[idx]);
        AddCh(pos.y, pos.x++, r);
    }

    int w = (rect.w / 2);
    string yes = "< YES >";
    pos.x = rect.min.x + ((w - yes.size()) / 2);
    for (size_t i = 0; i < yes.size(); ++i)
    {
        Style style = (_isYes ? _active : _inactive);
        Rune r(style, yes[i]);
        AddCh(rect.max.y - 1, pos.x++, r);
    }

    string no = "< NO >";
    pos.x = rect.max.x - ((w + no.size()) / 2);
    for (size_t i = 0; i < no.size(); ++i)
    {
        Style style = (_isYes ? _inactive : _active);
        Rune r(style, no[i]);
        AddCh(rect.max.y - 1, pos.x++, r);
    }
}

Input::Input()
{
    _textGap = 1;
}

Input::~Input()
{
}

vector<string> Input::GetItems()
{
}

void Input::Draw()
{
    Rect rect = InitCell();
    Pos pos(rect.min.y, rect.min.x);

    int rowCnt = _query.size();
    int rowWidth = rect.h / rowCnt;
    int colWidth = rect.w / 2;

    for (size_t row = 0; row < _query.size(); ++row)
    {
        string query(_query[row]);

        pos.y = rect.min.y + (row * rowWidth);
        pos.x = rect.min.x;

        for (size_t idx = 0; pos.x < rect.min.x + colWidth; pos.x++)
        {
            if (query[idx] == 0x00)
                AddCh(pos.y, pos.x, ' ');
            else
                AddCh(pos.y, pos.x, query[idx++]);
        }

        AddCh(pos.y, pos.x, ':');
    }

    // int textY = _inner.min.y + 1;
    // for (size_t row = 0; row < _query.size(); ++row)
    // {
    //     int textX = _inner.min.x + 1;

    //     // 1. Draw Query
    //     string query(_query[row]);
    //     for (int i = 0; i < query.size(); ++i)
    //         AddCh(textY, textX++, query[i]);

    //     // 2. Draw :
    //     textX = _inner.w / 2;
    //     AddCh(textY, textX++, ':');

    //     if (row < _default.size())
    //     {
    //         string def(_default[row]);
    //         for (size_t i = 0; i < def.size(); ++i)
    //             AddCh(textY, textX++, def[i]);
    //     }
    // }

    // 2. Draw UnderLine
    // 3. Default Text
    // 4. button

    // pos.x += (colWidth - text.length()) / 2;
    // for (size_t idx = 0; idx < _default.size(); ++idx)
    // {
    //     string text(_default[idx]);
    //     int w = (_inner.w / 2);
    //     int h = text.size() / w;
    //     if (h < (float)text.size() / w)
    //         h += 1;
    //     Input input;
    //     input.SetRect(h, w, _inner.min.y, w + 1);
    //     input.SetText("hihihi");
    //     input.Draw();
    //     AttachCells(input.GetCells());

    //     for (size_t i = 0; i < text.size(); i++)
    //     {
    //     }

    //     // input.SetRect(pos.y, w, pos.y, center + 1);
    //     // input.Draw();
    //     // AttachCells(input.GetCells());
    //     // Log("[%s]", input.GetText().c_str());
    // }

    // for (size_t def = 0; def < _default.size(); ++def)
    // {
    // }
}

// Input::Input()
// {
//     _active = th::Get()._input.active;
//     _inactive = th::Get()._input.inactive;
//     _isActive = false;
// }

// Input::~Input()
// {
// }

// const string Input::GetText()
// {
//     string text(_text.begin(), _text.end());
//     return text;
// }

// void Input::SetText(string s)
// {
//     for (size_t i = 0; i < s.size(); ++i)
//         AddText(s[i]);
// }

// void Input::AddText(chtype c)
// {
//     if ((int)_text.size() < ((_rect.max.y + 1) * _rect.w))
//         _text.push_back(c);
// }

// void Input::DelText()
// {
//     if (!_text.empty())
//         _text.pop_back();
// }

// void Input::ClearText()
// {
//     _text.clear();
// }

// void Input::Draw()
// {
//     Pos pos(_rect.min.y, _rect.min.x);

//     for (int y = _rect.min.y; y <= _rect.max.y; ++y)
//         for (int x = _rect.min.x; x <= _rect.max.x; ++x)
//             AddCh(y, x, {COLOR_BLACK, COLOR_WHITE, A_UNDERLINE, ' '});

//     for (size_t idx = 0; idx < _text.size(); ++idx)
//     {
//         if (_rect.max.x < pos.x)
//         {
//             pos.y++;
//             pos.x = _rect.min.x;
//         }

//         if (_rect.max.y < pos.y)
//             break;

//         Style style;
//         if (_isActive)
//             style = _active;
//         else
//             style = _inactive;
//         Rune r(style, _text[idx]);
//         AddCh(pos.y, pos.x++, r);
//     }

//     if (pos.x < _rect.max.x && _isActive)
//     {
//         Style style(COLOR_WHITE, COLOR_BLACK, A_UNDERLINE | A_BLINK);
//         Rune r(style, ' ');
//         AddCh(pos.y, pos.x++, r);
//     }
// }

Tab::Tab()
{
    _isBox = false;
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
    Rect rect = InitCell();
    Pos pos(rect.min.y, rect.min.x);

    for (size_t tabIdx = 0; tabIdx < _tabs.size(); ++tabIdx)
    {
        string text(_tabs[tabIdx]);
        for (size_t idx = 0; idx < text.size(); ++idx)
        {
            if (rect.max.x < pos.x)
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

void List::ScrollAmount(int amount)
{
    if ((int)_rows.size() - _curRow <= amount)
        _curRow = _rows.size() - 1;
    else if (_curRow + amount < 0)
        _curRow = 0;
    else
        _curRow += amount;
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

void List::Draw()
{
    Rect rect = InitCell();
    Pos pos(rect.min.y, rect.min.x);

    if (rect.h + _topRow <= _curRow)
        _topRow = _curRow - rect.h + 1;
    else if (_curRow < _topRow)
        _topRow = _curRow;

    for (size_t rowIdx = _topRow; rowIdx < _rows.size(); ++rowIdx)
    {
        string text(_rows[rowIdx]);
        for (size_t idx = 0; idx < text.size(); ++idx)
        {
            if (rect.max.x < pos.x)
                break;

            Style style;
            if ((int)rowIdx == _curRow)
                style = _activeStyle;
            else
                style = _inactiveStyle;

            Rune r(style, text[idx]);
            AddCh(pos.y, pos.x++, r);
        }

        pos.x = rect.min.x;
        pos.y++;
        if (rect.max.y < pos.y)
            break;
    }

    if (0 < _topRow)
    {
        Rune r(ACS_DIAMOND);
        AddCh(rect.min.y, rect.max.x, r);
    }

    if (_topRow + rect.h < (int)_rows.size())
    {
        Rune r(ACS_DIAMOND);
        AddCh(rect.max.y, rect.max.x, r);
    }
}

ProgressBar::ProgressBar()
{
    _barColor = th::Get()._progress.bar;
    _percent = 0;
}

ProgressBar::~ProgressBar()
{
}

void ProgressBar::Draw()
{
    Rect rect = InitCell();
    Pos pos(rect.min.y, rect.min.x);

    string label;
    if (_label.empty())
        label = to_string(_percent) + "%";
    else
        label = _label;

    int barWidth = int(float(_percent * 0.01) * rect.w);
    while (pos.y <= rect.max.y)
    {
        Rune r(_barColor, COLOR_BLACK, ' ');
        while (pos.x <= rect.min.x + barWidth)
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

    for (size_t idx = 0; idx < label.size(); ++idx)
    {
        Style style(_labelStyle);
        if (pos.x + (int)idx <= rect.min.x + barWidth)
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
    Rect rect = InitCell();
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
}

BarChart::BarChart()
{
    _numColor = th::Get()._bar.number;
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
    Rect rect = InitCell();

    int maxVal = _maxVal;
    if (maxVal == 0)
        maxVal = *max_element(_data.begin(), _data.end());

    int barX = rect.min.x + 1;
    for (size_t col = 0; col < _data.size(); ++col)
    {
        float val = _data[col];
        int h = (((float)(val / maxVal)) * (rect.h - 2));
        int w = 0;
        if (barX + _barWidth < rect.max.x)
            w = barX + _barWidth;
        else
            w = rect.max.x;

        for (int y = rect.max.y - 2; (rect.max.y - 2) - h < y; y--)
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
                AddCh(rect.max.y - 1, labalX++, r);
            }
        }

        int numX = barX + (float)(_barWidth / 2);
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