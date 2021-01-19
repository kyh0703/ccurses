#include <iostream>
#include <unistd.h>
#include "Palette.h"

#define FORM
int main(void)
{
    Palette p;
    if (!p.Init())
    {
        cout << "ncurses init Fail" << endl;
        return 1;
    }

#if  (defined FORM)
    // Input input;
    // input.SetRect(2, 10, 10, 10);

    Form form;
    form.SetRect(10, 30, 0, 0);
    form._query = {"test", "test2"};
    form._default = {"                                                   ", "test2"};
    p.Render({&form});
    while (int ch = getchar())
    {
        switch (ch)
        {
        case 'q':
            return 1;
        case 'j':
            break;
        default:
            break;
        }
        p.Render({&form});
    }
#elif (defined BARCHART)
    BarChart bar;
    bar.SetRect(20, 50, 0, 0);
    bar._data = { 7, 6, 5, 4, 3, 2};
    bar._barColor = {COLOR_WHITE, COLOR_BLUE, COLOR_RED};
    bar._labelStyle = {{COLOR_BLACK, COLOR_BLUE}, {COLOR_BLACK, COLOR_RED}};
    bar._label = { "11", "22", "33", "44", "55", "66"};
    p.Render({&bar});

    while (int ch = getchar())
    {
        switch (ch)
        {
        case 'q':
            return 1;
        case 'j':
            break;
        default:
            break;
        }
        p.Render({&bar});
    }
#elif (defined INPUT)
    Input input;
    input.SetRect(3, 50, 0, 0);
    input._isActive = true;
    p.Render({&input});
    while (int ch = getch())
    {
        switch (ch)
        {
        case 'q':
            return 1;
        case KEY_BACKSPACE:
            input.DelText();
            break;
        case KEY_DC:
            input.ClearText();
            break;
        default:
            input.AddText(ch);
            break;
        }
        p.Render({&input});
    }
#elif (defined TABLE)
    Table table;
    table.SetRect(9, 38, 5, 10);
    table._rows = {
        {"test", "test1", "test2"},
        {"test3", "test4", "test6"},
        {"test3", "test4", "test7"},
        {"test3", "test4", "test7"},
    };
    p.Render({&table});
    while (int ch = getchar())
    {
        switch (ch)
        {
        case 'q':
            return 1;
        default:
            break;
        }
    }
#elif (defined TAB)
    Tab tab;
    tab.SetRect(3, 40, 5, 5);
    tab._tabs = {"test1", "test2", "test3", "test4"};

    Button tab1;
    tab1.SetRect(10, 10, 10, 10);
    tab1.SetTitle("tab1111");

    Button tab2;
    tab2.SetRect(10, 10, 10, 10);
    tab2.SetTitle("tab2222");

    switch (tab._activeIdx)
    {
    case 0:
        p.Render({&tab, &tab1});
        break;
    case 1:
        p.Render({&tab, &tab2});
        break;
    default:
        break;
    }

    while (int ch = getchar())
    {
        switch (ch)
        {
        case 'q':
            return 1;
        case 'h':
            tab.ForcusLeft();
            switch (tab._activeIdx)
            {
            case 0:
                p.Render({&tab, &tab1});
                break;
            case 1:
                p.Render({&tab, &tab2});
                break;
            default:
                p.Render({&tab});
                break;
            }
            break;
        case 'k':
            tab.ForcusRight();
            switch (tab._activeIdx)
            {
            case 0:
                p.Render({&tab, &tab1});
                break;
            case 1:
                p.Render({&tab, &tab2});
                break;
            default:
                p.Render({&tab});
                break;
            }
            break;
        default:
            break;
        }
    }
#elif (defined BASIC)
    Basic basic;
    basic.SetRect(5, 15, 10, 10);
    basic.SetTitle("hello");
    basic._text = "hihihi111111111111111111111111111111111111";
    p.Render({&basic});
    while (int ch = getchar())
    {
    switch (ch)
    {
    case 'q':
        return 1;
    }
    }
#elif (defined LIST)
    List list;
    list.SetRect(5, 15, 10, 10);
    list._rows = {"test11111", "test2", "test3", "test4", "test5", "test6", "test7"};

    p.Render({&list});

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
        case 't':
            list.ScrollPageUp();
            break;
        case 'd':
            list.ScrollPageDown();
            break;
        default:
            break;
        }
        p.Render({&list});
    }
#elif defined(PROGRESS)
    ProgressBar pro;
    pro.SetRect(3, 50, 0, 0);
    pro._percent = 10;
    pro._label = "12341234";
    p.Render({&pro});

    while (int ch = getchar())
    {
        switch (ch)
        {
        case 'q':
            return 1;
        case 'j':
            pro._percent -= 1;
            break;
        case 'k':
            pro._percent += 1;
            break;
        default:
            break;
        }
        p.Render({&pro});
    }
#endif
        return 0;
}
