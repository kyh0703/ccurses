#include "Palette.h"
#include "Paint.h"
#include "Theme.h"

Palette::Palette(int max_height, int max_width)
{
    _max_height = max_height;
    _max_width = max_width;
    _tab = NULL;
    setlocale(LC_ALL, "ko_KR.utf8");
    _active_form = 0;
}

Palette::~Palette()
{
    Destroy();
}

bool Palette::Add(Form *form_ptr)
{
    auto const &it = find_if(_forms.begin(), _forms.end(), [&](unique_ptr<Form> &p) {
        return p.get() == form_ptr;
    });

    if (it != _forms.end())
        return false;

    unique_ptr<Form> temp(form_ptr);
    _forms.push_back(move(temp));
    return true;
}

void Palette::Destroy()
{
    printf("\e[?1000h");
    fflush(stdout);
    delete _tab;
    Clear();
    clrtoeol();
    refresh();
    endwin();
}

void Palette::Delete(const Form *form_ptr)
{
    auto const &it = find_if(_forms.begin(), _forms.end(), [&](unique_ptr<Form> &p) {
        return p.get() == form_ptr;
    });

    if (it != _forms.end())
        _forms.erase(it);
}

void Palette::Clear()
{
    _forms.clear();
}

bool Palette::Init(unsigned theme)
{
    if (!initscr())
        return false;
    if (cbreak() == ERR)
        return false;
    if (noecho() == ERR)
        return false;

    resize_term(_max_height, _max_width);
    printf("\033[?1003h");
    fflush(stdout);
    keypad(stdscr, TRUE);
    curs_set(0);
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);

    th::Get().SetTheme(theme);
    Color color(th::Get()._base.color);
    short idx = Paint::Get().GetIndex(color.bg, color.fg);
    wbkgd(stdscr, COLOR_PAIR(idx));
    refresh();
    return true;
}

void Palette::PollEvent(int fps)
{
    while (true)
    {
        if (KbHit())
        {
            MEVENT e;
            wint_t wch;
            int clicked;

            get_wch(&wch);
            switch (wch)
            {
            case KEY_RESIZE:
                erase();
                resize_term(_max_height, _max_width);
                continue;
            case KEY_SLEFT:
                erase();
                FocusLeft();
                continue;
            case KEY_SRIGHT:
                erase();
                FocusRight();
                continue;
            case KEY_MOUSE:
                if (getmouse(&e) != OK)
                    break;

                clicked = ClickTab(e);
                if (clicked == -1)
                {
                    ungetmouse(&e);
                    break;
                }

                erase();
                _active_form = clicked;
                continue;
            }
            _forms[_active_form]->ProcEvent(wch);
        }

        Draw();
        this_thread::sleep_for(chrono::milliseconds(fps));
    };
}

int Palette::ClickTab(MEVENT e)
{
    if (e.bstate != BUTTON1_CLICKED)
        return -1;

    Rect rect = _tab->GetRect();
    if (!rect.IsInclude(e.y, e.x))
        return -1;

    Pos pos(0, 0);
    for (size_t tab_index = 0; tab_index < _tab->GetTabs().size(); ++tab_index)
    {
        Pos str_pos(pos);
        wstring item;
        _tab->GetTab(tab_index, item);
        for (size_t item_index = 0; item_index < item.size(); ++item_index)
            str_pos.x += (fu::IsHangle(item[item_index]) ? 2 : 1);

        if (pos.y <= e.y && e.y <= str_pos.y &&
            pos.x <= e.x && e.x <= str_pos.x)
            return tab_index;

        str_pos.x += 1;
        pos = str_pos;
    }

    return -1;
}

void Palette::FocusLeft()
{
    if (_forms.size() == 0)
        _active_form = 0;
    else if (_active_form == 0)
        _active_form = _forms.size() - 1;
    else
        _active_form -= 1;
}

void Palette::FocusRight()
{
    if (_forms.size() == 0)
        _active_form = 0;
    else if (_active_form < (int)(_forms.size() - 1))
        _active_form += 1;
    else
        _active_form = 0;
}

void Palette::FocusFirst()
{
    _active_form = 0;
}

void Palette::FocusLast()
{
    if (_forms.size() == 0)
        _active_form = 0;
    else
        _active_form = _forms.size() - 1;
}

void Palette::DrawTab()
{
    if (!_tab)
        _tab = new Tab(2, COLS, 0, 0);

    _tab->SetActiveIndex(_active_form);
    _tab->SetFocus(false);
    vector<wstring> items;
    for (auto it = _forms.begin(); it != _forms.end(); ++it)
    {
        wstring form_text = (*it)->_text;
        items.push_back(form_text);
    }
    _tab->SetTabs(items);
    _tab->Draw();
}

void Palette::Draw()
{
    if (_forms.empty())
        return;
    DrawTab();
    _forms[_active_form]->Draw();
}

bool Palette::KbHit()
{
    nodelay(stdscr, TRUE);
    bool ret = false;
    int ch = getch();
    if (ch != ERR)
    {
        ret = true;
        ungetch(ch);
    }
    nodelay(stdscr, false);
    return ret;
}
