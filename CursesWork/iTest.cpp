#include <unistd.h>
#if 1
#include "Palette.h"

int main(void)
{
    Palette p;
    printf("\033[?1000h");
    fflush(stdout);
    p.Init();

    Basic *pW = new Basic;
    pW->SetRect(10, 10, 0, 0);
    // pW->SetColor();
    pW->SetTitle("test");
    pW->SetText("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    pW->Draw();

    // Basic *pW2 = new Basic;
    // pW2->SetRect(10, 10, 11, 11);
    // // pW->SetColor();
    // pW2->SetTitle("test");

    // p.AttachWidget(pW);
    // p.AttachWidget(pW2);

    // p.DrawWidget();
    MEVENT event;
    while (int ch = getchar())
    {
        switch (ch)
        {
        case 'q':
            return 1;
        case 'd':
            break;
        case KEY_MOUSE:
            if (getmouse(&event) == OK)
            {
                Widget::Log("ch[%c]", ch);
            }
            break;
        default:
            break;
        }
    }
    return 0;
}

#else
#include <curses.h>
#include <locale.h>

int main()
{
    setlocale(LC_CTYPE, "ko_KR.utf-8"); /* 로케일 설정을 했는데도 */
    initscr();
    printw("%s", "ABCDEFGHIJKLMNOPQRSTUVWXYZ\n");
    addstr("가나다라마바사아자차카타파하\n");
    refresh();
    sleep(1);
    endwin();
    return 0;
}
#endif
