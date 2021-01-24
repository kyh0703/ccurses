#include "Paint.h"
#include <unistd.h>
#include "Theme.h"
#include "Palette.h"

Palette::Palette()
{
    _active = 0;
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

    int bg = th::Get()._base.color.bg;
    int fg = th::Get()._base.color.fg;
    Color color(bg, fg);
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

Form *Palette::GetActiveForm(Form *pForm)
{
    vector<Form *>::iterator it;
    it = find(_pForms.begin(), _pForms.end(), pForm);
    if (it == _pForms.end())
        return NULL;
    Form *pTemp = *it;
    if (pTemp->IsActive())
        return pTemp;
    return NULL;
}

bool Palette::Regist(Form *pForm)
{
    vector<Form *>::iterator it;
    it = find(_pForms.begin(), _pForms.end(), pForm);
    if (it != _pForms.end())
        return false;
    _pForms.push_back(pForm);
    return true;
}

void Palette::Remove(Form *pForm)
{
    vector<Form *>::iterator it;
    for (it = _pForms.begin(); it != _pForms.end(); ++it)
    {
        if (*it == pForm)
        {
            Form *pTemp = *it;
            delete pTemp;
            _pForms.erase(it);
        }
    }
}

void Palette::DrawForm()
{
    for (size_t idx = 0; idx < _pForms.size(); ++idx)
    {
        if (idx == _active)
        {
            _pForms[idx]->Draw();
            return;
        }
    }
}

void Palette::PollEvent(int millisecond)
{
    thread th(&Form::Run, _pForms[0]);
    th.join();
    DrawForm();
    while (true)
    {
        if (KbHit())
        {
            int ch = getch();
            if (ch == 'q')
            {

                return;
            }
        }
        DrawForm();
        this_thread::sleep_for(chrono::milliseconds(millisecond));
        refresh();
    }
}

void Palette::Render(vector<Widget *> widgets)
{
    vector<Widget *>::iterator it;
    for (it = widgets.begin(); it != widgets.end(); ++it)
    {
        Widget *pWidget = *it;
        pWidget->Draw();
        pWidget->Print();
    }
    refresh();
}