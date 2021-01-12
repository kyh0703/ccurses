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

    setlocale(LC_ALL, "ko_KR.utf8");
    mousemask(ALL_MOUSE_EVENTS, NULL);
    short idx = Paint::Get().FindIndex(COLOR_WHITE, COLOR_BLACK);
    wbkgd(stdscr, COLOR_PAIR(idx));
    refresh();
}

void Palette::AttachWidget(Widget *pWidget)
{
    mWidgets.push_back(pWidget);
}

bool Palette::DrawWidget()
{
    vector<Widget *>::iterator iter;
    for (iter = mWidgets.begin(); iter != mWidgets.end(); ++iter)
    {
        (*iter)->DrawBase();
        (*iter)->Draw();
    }
    refresh();
    return true;
}