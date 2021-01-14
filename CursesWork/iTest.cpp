#include <unistd.h>
#include "Palette.h"

int main(void)
{
    Palette p;
    p.Init();

    // Basic basic;
    // basic.SetRect(8, 15, 3, 0);
    // basic.SetTitle("I love youngkyoung");
    // basic._textColor = COLOR_BLUE;
    // basic._text = "Good Moaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";

    // Button btn;
    // btn.SetRect(2, 4, 10, 10);
    // btn._isActive = true;
    // btn._text = "YES";

    // Tab tab;
    // tab.SetRect(2, 50, 0, 0);
    // tab._tabs = {"test", "test1", "test2"};

    List list;
    list.SetRect(5, 15, 10, 10);
    list._rows = {"test", "test1", "test2", "test4", "test5", "test6", "test7"};

    // Input input;
    // input.SetRect(1, 10, 20, 20);

    // p.Render({&basic, &tab, &list, /*&btn, &input*/});
    p.Render({&list, /*&btn, &input*/});

    MEVENT event;
    while (int ch = getchar())
    {
        switch (ch)
        {
        case 'q':
            return 1;
        case 'j':
            list.ScrollDown();
            break;
        case 'k':
            list.ScrollUp();
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
        p.Render({&list});
    }
    return 0;
}