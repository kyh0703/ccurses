#include "Paint.h"
#include "Palette.h"

Palette::Palette()
{
}

Palette::~Palette()
{
    erase();
    endwin();
}

void Palette::Init()
{
    initscr();
    clear();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    printf("\033[?1000h");
    fflush(stdout);

    setlocale(LC_ALL, "ko_KR.utf8");
    mousemask(ALL_MOUSE_EVENTS, NULL);
    short idx = Paint::Get().FindIndex(COLOR_WHITE, COLOR_BLACK);
    wbkgd(stdscr, COLOR_PAIR(idx));
    refresh();
}

void Palette::Attach(Widget *pWidget)
{
    mWidgets.push_back(pWidget);
}

bool Palette::Render()
{
    vector<Widget *>::iterator iter;
    for (iter = mWidgets.begin(); iter != mWidgets.end(); ++iter)
    {
        (*iter)->DrawBase();
        (*iter)->Draw();
        (*iter)->Print();
    }
    refresh();
    return true;
}