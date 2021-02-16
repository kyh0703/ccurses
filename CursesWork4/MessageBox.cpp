#include "MessageBox.h"
#include "Paint.h"

#define WIDTH 40
#define TEXT_HEIGHT 6

void DestoryMessageBox(WINDOW *win)
{
    werase(win);
    wrefresh(win);
    delwin(win);
}

const int MessageBoxOk(string title, string text)
{
    int height = (text.size() / WIDTH) + TEXT_HEIGHT;
    Rect rect(height, WIDTH, (LINES - height) / 2, (COLS - WIDTH) / 2);

    WINDOW *win = newwin(rect.h, rect.w, rect.min.y, rect.min.x);
    box(win, 0, 0);
    mvwaddstr(win, 0, 2, title.c_str());
    keypad(win, TRUE);

    Rect win_rect((rect.h <= 2 ? rect.h : rect.h - 2),
                  (rect.w <= 2 ? rect.w : rect.w - 2),
                  1, 1);

    Pos pos(win_rect.min.y, win_rect.min.x);
    for (size_t text_index = 0; text_index < text.size(); ++text_index)
    {
        bool isEol = (text[text_index] == '\n');
        if (isEol || win_rect.max.x < pos.x)
        {
            pos.y++;
            pos.x = win_rect.min.x;
            if (isEol)
                continue;
        }

        if (win_rect.max.y - 2 < pos.y)
            break;

        mvwaddch(win, pos.y, pos.x++, text[text_index]);
    }

    const string ok = "< OK >";
    pos.y = win_rect.max.y - 1;
    pos.x = (WIDTH - ok.size()) / 2;
    Rect btn_rect(1, ok.size(), rect.max.y - 2, pos.x + rect.min.x);

    wattron(win, A_REVERSE);
    mvwprintw(win, pos.y, pos.x, "%s", ok.c_str());
    wattroff(win, A_REVERSE);

    MEVENT event;
    while (true)
    {
        int ch = wgetch(win);
        switch (ch)
        {
        case KEY_F(1):
        case KEY_RESIZE:
            DestoryMessageBox(win);
            return MB_RESULT_CANCLE;
        case 10:
            DestoryMessageBox(win);
            return MB_RESULT_OK;
        case KEY_MOUSE:
            if (getmouse(&event) != OK)
                continue;
            if (event.bstate != BUTTON1_CLICKED)
                continue;
            if (!btn_rect.IsInclude(event.y, event.x))
                continue;
            DestoryMessageBox(win);
            return MB_RESULT_OK;
        default:
            break;
        }
    }
}

const int MessageBoxYes(string title, string text)
{
    int height = (text.size() / WIDTH) + TEXT_HEIGHT;
    Rect rect(height, WIDTH, (LINES - height) / 2, (COLS - WIDTH) / 2);

    WINDOW *win = newwin(rect.h, rect.w, rect.min.y, rect.min.x);
    box(win, 0, 0);
    mvwaddstr(win, 0, 2, title.c_str());
    keypad(win, TRUE);

    Rect win_rect((rect.h <= 2 ? rect.h : rect.h - 2),
                  (rect.w <= 2 ? rect.w : rect.w - 2),
                  1, 1);

    Pos pos(win_rect.min.y, win_rect.min.x);
    for (size_t text_index = 0; text_index < text.size(); ++text_index)
    {
        bool isEol = (text[text_index] == '\n');
        if (isEol || win_rect.max.x < pos.x)
        {
            pos.y++;
            pos.x = win_rect.min.x;
            if (isEol)
                continue;
        }

        if (win_rect.max.y - 2 < pos.y)
            break;

        mvwaddch(win, pos.y, pos.x++, text[text_index]);
    }

    bool is_yes = true;

draw_button:
    const string yes = "< YES >";
    int w = (win_rect.w / 2);
    pos.y = win_rect.max.y - 1;
    pos.x = win_rect.min.x + ((w - yes.size()) / 2);
    Rect yes_rect(1, yes.size(), rect.max.y - 2, pos.x + rect.min.x);
    if (is_yes)
    {
        wattron(win, A_REVERSE);
        mvwprintw(win, pos.y, pos.x, "%s", yes.c_str());
        wattroff(win, A_REVERSE);
    }
    else
    {
        mvwprintw(win, pos.y, pos.x, "%s", yes.c_str());
    }

    const string no = "< NO >";
    pos.x = win_rect.max.x - ((w + no.size()) / 2);
    Rect no_rect(1, no.size(), rect.max.y - 2, pos.x + rect.min.x);
    if (!is_yes)
    {
        wattron(win, A_REVERSE);
        mvwprintw(win, pos.y, pos.x, "%s", no.c_str());
        wattroff(win, A_REVERSE);
    }
    else
    {
        mvwprintw(win, pos.y, pos.x, "%s", no.c_str());
    }

    MEVENT event;
    while (true)
    {
        int ch = wgetch(win);
        switch (ch)
        {
        case KEY_F(1):
        case KEY_RESIZE:
            DestoryMessageBox(win);
            return MB_RESULT_CANCLE;
        case 10:
            DestoryMessageBox(win);
            return (is_yes ? MB_RESULT_YES : MB_RESULT_NO);
        case KEY_LEFT:
            if (!is_yes)
                is_yes = true;
            goto draw_button;
        case KEY_RIGHT:
            if (is_yes)
                is_yes = false;
            goto draw_button;
        case KEY_MOUSE:
            if (getmouse(&event) != OK)
                continue;
            if (event.bstate != BUTTON1_CLICKED)
                continue;

            if (yes_rect.IsInclude(event.y, event.x))
            {
                DestoryMessageBox(win);
                return MB_RESULT_YES;
            }
            else if (no_rect.IsInclude(event.y, event.x))
            {
                DestoryMessageBox(win);
                return MB_RESULT_NO;
            }
            break;
        default:
            break;
        }
    }
}

const int MessageBox(string title, string text, int type)
{
    switch (type)
    {
    case MB_TYPE_YESNO:
        return MessageBoxYes(title, text);
    default:
        return MessageBoxOk(title, text);
    }
}