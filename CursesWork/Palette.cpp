#include "Paint.h"
#include "Theme.h"
#include "Palette.h"

Palette::Palette()
{
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
    mousemask(ALL_MOUSE_EVENTS, NULL);
    Color color(th::Get()._default.bg, th::Get()._default.fg);
    short idx = Paint::Get().GetIndex(color.bg, color.fg);
    wbkgd(stdscr, COLOR_PAIR(idx));
    refresh();
    return true;
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

bool Palette::Render(vector<Widget *> widgets)
{
    vector<Widget *>::iterator iter;
    for (iter = widgets.begin(); iter != widgets.end(); ++iter)
    {
        (*iter)->DrawBase();
        (*iter)->Draw();
        (*iter)->Print();
    }
    refresh();
    return true;
}