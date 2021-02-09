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

bool Palette::operator+=(const WinForm *pform)
{
    vector<WinForm *>::iterator it;
    it = find(_pforms.begin(), _pforms.end(), pform);
    if (it != _pforms.end())
        return false;
    _pforms.push_back((WinForm *)pform);
    return true;
}

void Palette::operator-=(const WinForm *pform)
{
    vector<WinForm *>::iterator it;
    for (it = _pforms.begin(); it != _pforms.end(); ++it)
    {
        if (*it == pform)
        {
            WinForm *pTemp = *it;
            delete pTemp;
            _pforms.erase(it);
        }
    }
}

void Palette::Clear()
{
    vector<WinForm *>::iterator it;
    for (it = _pforms.begin(); it != _pforms.end(); ++it)
    {
        WinForm *pTemp = *it;
        delete pTemp;
        _pforms.erase(it);
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
    if (_pforms.size() == 0)
        _active_form = 0;
    else if (_active_form == 0)
        _active_form = _pforms.size() - 1;
    else
        _active_form--;
}

void Palette::ForcusRight()
{
    if (_pforms.size() == 0)
        _active_form = 0;
    else if (_active_form < (int)(_pforms.size() - 1))
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
    if (_pforms.size() == 0)
        _active_form = 0;
    else
        _active_form = _pforms.size() - 1;
}

void Palette::PollEvent(int fps)
{
    while (true)
    {
        if (KbHit())
        {
            int ch = getch();
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
    for (size_t index = 0; index < _pforms.size(); ++index)
    {
        if ((int)index == _active_form)
        {
            _pforms[index]->Draw();
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