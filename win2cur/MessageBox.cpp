#include "MessageBox.h"
#include "Theme.h"
#include "Paint.h"

#define WIDTH 40
#define TEXT_HEIGHT 6

cchar_t Convcch(int opt, wchar_t wch)
{
    cchar_t cch;
    Color c = th::Get()._base.color;
    int index = Paint::Get().GetIndex(c.bg, c.fg);
    setcchar(&cch, &wch, opt, index, NULL);
    return cch;
}

void DrawTitle(WINDOW *window, wstring title)
{
    Pos pos(0, 2);
    for (size_t title_index = 0; title_index < title.size(); ++title_index)
    {
        wchar_t wch = title[title_index];
        cchar_t cch = Convcch(WA_NORMAL, wch);
        mvwadd_wch(window, pos.y, pos.x, &cch);
        pos.x += (Util::IsHangle(wch) ? 2 : 1);
    }
}

void DrawText(WINDOW *window, Rect win_rect, wstring text)
{
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

        wchar_t wch = text[text_index];
        cchar_t cch = Convcch(WA_NORMAL, wch);
        mvwadd_wch(window, pos.y, pos.x, &cch);
        pos.x += (Util::IsHangle(wch) ? 2 : 1);
    }
}

void DestoryMessageBox(WINDOW *window)
{
    werase(window);
    wrefresh(window);
    delwin(window);
}

const int MessageBoxOk(wstring title, wstring text)
{
    int height = (text.size() / WIDTH) + TEXT_HEIGHT;
    Rect rect(height, WIDTH, (LINES - height) / 2, (COLS - WIDTH) / 2);

    WINDOW *window = newwin(rect.h, rect.w, rect.min.y, rect.min.x);
    box_set(window, 0, 0);
    keypad(window, TRUE);

    Rect win_rect((rect.h <= 2 ? rect.h : rect.h - 2),
                  (rect.w <= 2 ? rect.w : rect.w - 2),
                  1, 1);

    DrawTitle(window, title);
    DrawText(window, win_rect, text);
    Color c = th::Get()._base.color;
    int index = Paint::Get().GetIndex(c.bg, c.fg);
    wbkgd(window, COLOR_PAIR(index));

    const wstring ok = L"< 확인 >";
    Pos pos;
    pos.y = win_rect.max.y - 1;
    pos.x = ((WIDTH - ok.size()) / 2) - 1;
    Rect btn_rect(1, ok.size(), rect.max.y - 2, pos.x + rect.min.x);

    for (size_t ok_index = 0; ok_index < ok.size(); ++ok_index)
    {
        wchar_t wch = ok[ok_index];
        cchar_t cch = Convcch(WA_REVERSE, wch);
        mvwadd_wch(window, pos.y, pos.x, &cch);
        pos.x += (Util::IsHangle(wch) ? 2 : 1);
    }

    MEVENT event;
    while (true)
    {
        int ch = wgetch(window);
        switch (ch)
        {
        case KEY_F(1):
        case KEY_RESIZE:
            DestoryMessageBox(window);
            return MB_RESULT_CANCLE;
        case 10:
            DestoryMessageBox(window);
            return MB_RESULT_OK;
        case KEY_MOUSE:
            if (getmouse(&event) != OK)
                continue;
            if (event.bstate != BUTTON1_CLICKED)
                continue;
            if (!btn_rect.IsInclude(event.y, event.x))
                continue;
            DestoryMessageBox(window);
            return MB_RESULT_OK;
        default:
            break;
        }
    }
}

const int MessageBoxYes(wstring title, wstring text)
{
    int height = (text.size() / WIDTH) + TEXT_HEIGHT;
    Rect rect(height, WIDTH, (LINES - height) / 2, (COLS - WIDTH) / 2);

    WINDOW *window = newwin(rect.h, rect.w, rect.min.y, rect.min.x);
    box_set(window, 0, 0);
    keypad(window, TRUE);

    Rect win_rect((rect.h <= 2 ? rect.h : rect.h - 2),
                  (rect.w <= 2 ? rect.w : rect.w - 2),
                  1, 1);

    DrawTitle(window, title);
    DrawText(window, win_rect, text);
    Color c = th::Get()._base.color;
    int index = Paint::Get().GetIndex(c.bg, c.fg);
    wbkgd(window, COLOR_PAIR(index));
    bool is_yes = true;

draw_button:
    const wstring yes = L"< 예 >";
    int w = (win_rect.w / 2);
    Pos pos;
    pos.y = win_rect.max.y - 1;
    pos.x = win_rect.min.x + ((w - yes.size()) / 2);
    Rect yes_rect(1, yes.size(), rect.max.y - 2, pos.x + rect.min.x);
    for (size_t yes_index = 0; yes_index < yes.size(); ++yes_index)
    {
        wchar_t wch = yes[yes_index];
        cchar_t cch = Convcch((is_yes ? WA_REVERSE : WA_NORMAL), wch);
        mvwadd_wch(window, pos.y, pos.x, &cch);
        pos.x += (Util::IsHangle(wch) ? 2 : 1);
    }

    const wstring no = L"< 아니오 >";
    pos.x = win_rect.max.x - ((w + no.size()) / 2);
    Rect no_rect(1, no.size(), rect.max.y - 2, pos.x + rect.min.x);
    for (size_t no_index = 0; no_index < no.size(); ++no_index)
    {
        wchar_t wch = no[no_index];
        cchar_t cch = Convcch((!is_yes ? WA_REVERSE : WA_NORMAL), wch);
        mvwadd_wch(window, pos.y, pos.x, &cch);
        pos.x += (Util::IsHangle(wch) ? 2 : 1);
    }

    MEVENT event;
    while (true)
    {
        int ch = wgetch(window);
        switch (ch)
        {
        case KEY_F(1):
        case KEY_RESIZE:
            DestoryMessageBox(window);
            return MB_RESULT_CANCLE;
        case 10:
            DestoryMessageBox(window);
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
                DestoryMessageBox(window);
                return MB_RESULT_YES;
            }
            else if (no_rect.IsInclude(event.y, event.x))
            {
                DestoryMessageBox(window);
                return MB_RESULT_NO;
            }
            break;
        default:
            break;
        }
    }
}

const int MessageBox(wstring title, wstring text, int type)
{
    switch (type)
    {
    case MB_TYPE_YESNO:
        return MessageBoxYes(title, text);
    default:
        return MessageBoxOk(title, text);
    }
}