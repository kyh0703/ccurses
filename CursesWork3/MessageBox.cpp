#include "MessageBox.h"
#include "Paint.h"

int MessageBox(string title, string text, int type)
{
    const string btn_yes_text = "< YES >";
    const string btn_no_text = "< NO >";
    const string btn_ok_text = "< OK >";

    int width = 40;
    int height = (text.size() / width) + 6;
    Rect rect(height, width, (LINES - height) / 2, (COLS - width) / 2);

    WINDOW *p_window = newwin(rect.h, rect.w, rect.min.y, rect.min.x);
    box(p_window, 0, 0);
    mvwaddstr(p_window, 0, 2, title.c_str());
    wrefresh(p_window);

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

        mvwaddch(p_window, pos.y, pos.x++, text[text_index]);
    }

    switch (type)
    {
    case MB_YESNO:
    {
        int w = (win_rect.w / 2);
        string yes = "< YES >";
        pos.x = win_rect.min.x + ((w - yes.size()) / 2);
        for (size_t i = 0; i < yes.size(); ++i)
            mvwaddch(p_window, win_rect.max.y - 1, pos.x++, yes[i]);

        string no = "< NO >";
        pos.x = win_rect.max.x - ((w + no.size()) / 2);
        for (size_t i = 0; i < no.size(); ++i)
            mvwaddch(p_window, win_rect.max.y - 1, pos.x++, no[i]);
        break;
    }
    default:
    {
        string enter = "< OK >";
        pos.x = (win_rect.w - enter.size()) / 2;
        for (size_t i = 0; i < enter.size(); ++i)
        {
            mvwaddch(p_window, win_rect.max.y - 1, pos.x++, enter[i]);
        }
        break;
    }
    }

    int index = 0;
    keypad(p_window, TRUE);
    int ch = wgetch(p_window);
    int ret = MB_RESULT_OK;
    while (true)
    {
        if (ch == 9 || ch == 10) // ENTER
        {
        }
        else if (ch == 27) // ESC
        {
            break;
        }
    }
    delwin(p_window);
    return ret;
}
