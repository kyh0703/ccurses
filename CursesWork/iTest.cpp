#include <unistd.h>
#if 1
#include "Palette.h"

int main(void)
{
    Palette p;
    p.Init();

    Basic *pW = new Basic;
    pW->SetRect(15, 15, 0, 3);
    pW->SetColor(COLOR_BLACK, COLOR_RED);
    pW->SetTitle("I love youngkyoung");
    pW->textColor = COLOR_BLUE;
    pW->text = "Good Morning!!!!!!!!!!!\n!!!!!!!!";
    p.Attach(pW);

    Button *pBtn = new Button;
    pBtn->SetRect(2, 4, 10, 10);
    pBtn->IsActive = true;
    pBtn->active = {COLOR_WHITE, COLOR_BLACK, A_BOLD};
    pBtn->inactive = {COLOR_BLACK, COLOR_WHITE};
    pBtn->text = "YES";
    p.Attach(pBtn);

    Tab *pTab = new Tab;
    pTab->SetRect(2, 50, 0, 0);
    pTab->tabs = {"test", "test1", "test2"};
    p.Attach(pTab);

    // Menu *pM = new Menu;
    // pM->SetRect(15, 15, 10, 10);
    // pM->SetTitle("Menu");
    // pM->items = {"test", "test", "test2"};

    // TabPane *pTab = new TabPane;
    // pTab->SetRect(2, 50, 0, 0);
    // pTab->active = {COLOR_BLUE, COLOR_BLACK, A_BLINK};
    // pTab->inactive = {COLOR_BLACK, COLOR_WHITE};
    // pTab->tabs = {"test", "test1", "test2", "pardsadfsereradsd", "adfasdfasdfasdfasdfasdf"};
    // p.Attach(pTab);


    // p.Attach(pM);
    p.Render();

    MEVENT event;
    while (int ch = getchar())
    {
        switch (ch)
        {
        case 'q':
            return 1;
        case 'd':
            break;
        case 'l':
            // pTab->ForcusLeft();
            break;
        case 'h':
            // pTab->ForcusRight();
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
