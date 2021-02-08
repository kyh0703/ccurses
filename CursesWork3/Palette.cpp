#include "Paint.h"
#include <unistd.h>
#include "Theme.h"
#include "Palette.h"

Palette::Palette()
{
    _activeform = 0;
}

Palette::~Palette()
{
    erase();
    endwin();
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

    setlocale(LC_ALL, "ko_KR.utf8");
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
    if (_pForms.size() == 0)
        _activeform = 0;
    else if (_activeform == 0)
        _activeform = _pForms.size() - 1;
    else
        _activeform--;
}

void Palette::ForcusRight()
{
    if (_pForms.size() == 0)
        _activeform = 0;
    else if (_activeform < (int)(_pForms.size() - 1))
        _activeform++;
    else
        _activeform = 0;
}

void Palette::ForcurFirst()
{
    _activeform = 0;
}

void Palette::ForcurLast()
{
    if (_pForms.size() == 0)
        _activeform = 0;
    else
        _activeform = _pForms.size() - 1;
}

bool Palette::Regist(WinForm *pForm)
{
    vector<WinForm *>::iterator it;
    it = find(_pForms.begin(), _pForms.end(), pForm);
    if (it != _pForms.end())
        return false;
    _pForms.push_back(pForm);
    return true;
}

void Palette::Remove(WinForm *pForm)
{
    vector<WinForm *>::iterator it;
    for (it = _pForms.begin(); it != _pForms.end(); ++it)
    {
        if (*it == pForm)
        {
            WinForm *pTemp = *it;
            delete pTemp;
            _pForms.erase(it);
        }
    }
}

void Palette::DrawForm()
{
    for (size_t idx = 0; idx < _pForms.size(); ++idx)
    {
        if ((int)idx == _activeform)
        {
            _pForms[idx]->Draw();
            return;
        }
    }
}

void Palette::PollEvent(int fps)
{
    while (true)
    {
        if (KbHit())
        {
            int ch = getch();
            if (ch == KEY_RESIZE)
                DrawForm();
            continue;
        }

        DrawForm();
        this_thread::sleep_for(chrono::milliseconds(fps));
    };
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