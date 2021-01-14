#include <unistd.h>
#include "Palette.h"

int main(void)
{
    Palette p;
    p.Init();

    Basic basic;
    basic.SetRect(15, 15, 3, 0);
    basic.SetTitle("I love youngkyoung");
    basic._textColor = COLOR_BLUE;
    basic._text = "Good Morning!!!!!!!!!!!\n!!!!!!!!";

    // Button *pBtn = new Button;
    // pBtn->SetRect(2, 4, 10, 10);
    // pBtn->IsActive = true;
    // pBtn->active = {COLOR_WHITE, COLOR_BLACK, A_BOLD};
    // pBtn->inactive = {COLOR_BLACK, COLOR_WHITE};
    // pBtn->text = "YES";
    // p.Attach(pBtn);

    // Tab tab;
    // tab.SetRect(2, 50, 0, 0);
    // tab._tabs = {"test", "test1", "test2"};

    Menu menu;
    menu.SetRect(15, 15, 10, 10);
    menu._items = {"test", "test", "test2"};

    TabPane tab2;
    tab2.SetRect(2, 50, 0, 0);
    tab2._tabs = {"test", "test1", "test2", "pardsadfsereradsd", "adfasdfasdfasdfasdfasdf"};


    // p.Attach(pM);
    p.Render({&basic, &tab2, &menu});

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