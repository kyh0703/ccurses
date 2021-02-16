#include "Palette.h"
#include "Paint.h"
#include "Theme.h"
#include <unistd.h>

Palette::Palette()
{
    setlocale(LC_ALL, "ko_KR.utf8");
    _active_form = 0;
}

Palette::~Palette()
{
    erase();
    endwin();
    Clear();
}

bool Palette::operator+=(const Form *form)
{
    vector<Form *>::iterator it;
    it = find(_forms.begin(), _forms.end(), form);
    if (it != _forms.end())
        return false;
    _forms.push_back((Form *)form);
    return true;
}

void Palette::operator-=(const Form *form)
{
    vector<Form *>::iterator it;
    for (it = _forms.begin(); it != _forms.end(); ++it)
    {
        if (*it == form)
        {
            Form *pTemp = *it;
            delete pTemp;
            _forms.erase(it);
        }
    }
}

void Palette::Clear()
{
    vector<Form *>::iterator it;
    for (it = _forms.begin(); it != _forms.end(); ++it)
    {
        Form *pTemp = *it;
        delete pTemp;
        _forms.erase(it);
    }
}

bool Palette::Init()
{
    if (!initscr())
        return false;
    if (cbreak() == ERR)
        return false;
    if (noecho() == ERR)
        return false;

    clear();
    keypad(stdscr, TRUE);
    curs_set(0);

    printf("\033[?1000h");
    fflush(stdout);

    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);

    int bg = th::Get()._base.color.bg;
    int fg = th::Get()._base.color.fg;
    Color color(bg, fg);
    short idx = Paint::Get().GetIndex(color.bg, color.fg);
    wbkgd(stdscr, COLOR_PAIR(idx));
    refresh();
    return true;
}

void Palette::ForcusLeft()
{
    if (_forms.size() == 0)
        _active_form = 0;
    else if (_active_form == 0)
        _active_form = _forms.size() - 1;
    else
        _active_form--;
}

void Palette::ForcusRight()
{
    if (_forms.size() == 0)
        _active_form = 0;
    else if (_active_form < (int)(_forms.size() - 1))
        _active_form++;
    else
        _active_form = 0;
}

void Palette::ForcurFirst()
{
    _active_form = 0;
}

void Palette::ForcurLast()
{
    if (_forms.size() == 0)
        _active_form = 0;
    else
        _active_form = _forms.size() - 1;
}

void Palette::PollEvent(int fps)
{
    while (true)
    {
        if (KbHit())
        {
            wint_t ch;
            get_wch(&ch);
            if (ch == KEY_RESIZE)
                Draw();
            continue;
        }

        Draw();
        this_thread::sleep_for(chrono::milliseconds(fps));
    };
}

void Palette::Draw()
{
    for (size_t index = 0; index < _forms.size(); ++index)
    {
        if ((int)index == _active_form)
        {
            _forms[index]->Draw();
            return;
        }
    }
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