#include "Palette.h"
#include <iostream>
#include <unistd.h>

#define BARCHART
int main(void)
{
    Palette p;
    if (!p.Init())
    {
        cout << "ncurses init Fail" << endl;
        return 1;
    }

#if (defined TEXT)
    TextBox text;
    text.SetRect(5, 15, 10, 10);
    text.SetTitle("hello");
    text.SetText("hihihi111111111111111111111111111111111111");
    text.SetStyle({COLOR_BLACK, COLOR_RED});
    p.Render({&text});
    while (int ch = getchar())
    {
        switch (ch)
        {
        case 'q':
            return 1;
        }
    }
#elif (defined POPUP)
    Popup pop;
    pop.SetRect(10, 20, 10, 10);
    pop.SetTitle("hello");
    pop.SetText("hihihiaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa111111111");
    pop.SetTextColor(COLOR_RED);
    p.Render({&pop});
    while (int ch = getchar())
    {
        switch (ch)
        {
        case 'q':
            return 1;
        }
    }
#elif (defined YESNO)
    YesNo yn;
    yn.SetRect(10, 20, 10, 10);
    yn.SetTitle("hello");
    yn.SetText("hihihiaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa111111111");
    yn.SetTextColor(COLOR_RED);
    p.Render({&yn});
    while (int ch = getchar())
    {
        switch (ch)
        {
        case 'q':
            return 1;
        case 'k':
            yn.ForcusLeft();
            break;
        case 'l':
            yn.ForcusRight();
            break;
        default:
            break;
        }
        p.Render({&yn});
    }
#elif (defined TAB)
    Tab tab;
    tab.SetRect(3, 40, 5, 5);
    tab.SetTabs({"test1", "test2", "test3", "test4"});

    TextBox txt1;
    txt1.SetRect(10, 10, 10, 10);
    txt1.SetTitle("tab1111");

    TextBox txt2;
    txt2.SetRect(10, 10, 10, 10);
    txt2.SetTitle("tab2222");

    switch (tab.GetActive())
    {
    case 0:
        p.Render({&tab, &txt1});
        break;
    case 1:
        p.Render({&tab, &txt2});
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
            switch (tab.GetActive())
            {
            case 0:
                p.Render({&tab, &txt1});
                break;
            case 1:
                p.Render({&tab, &txt2});
                break;
            default:
                p.Render({&tab});
                break;
            }
            break;
        case 'k':
            tab.ForcusRight();
            switch (tab.GetActive())
            {
            case 0:
                p.Render({&tab, &txt1});
                break;
            case 1:
                p.Render({&tab, &txt2});
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
#elif (defined LIST)
    List list;
    list.SetRect(5, 15, 10, 10);
    list.SetRows({"test11111",
                  "test2",
                  "test3",
                  "test4",
                  "test5",
                  "test6",
                  "test7"});
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
    pro.SetPercent(10);
    pro.SetLabel("12341234");
    p.Render({&pro});
    while (int ch = getchar())
    {
        switch (ch)
        {
        case 'q':
            return 1;
        case 'j':
            pro.SetPercent(9);
            break;
        case 'k':
            pro.SetPercent(11);
            break;
        default:
            break;
        }
        p.Render({&pro});
    }
#elif (defined TABLE)
    Table table;
    table.SetRect(9, 38, 5, 10);
    table.SetAlignment(Table::LEFT);
    table.SetRows({
        {"test", "test1", "test2"},
        {"test3", "test4", "test6"},
        {"test3", "test4", "test7"},
        {"test3", "test4", "test7"},
    });
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
#elif (defined BARCHART)
    BarChart bar;
    bar.SetRect(20, 50, 0, 0);
    bar.SetData({7, 6, 5, 4, 3, 2});
    bar.SetBarColor({COLOR_WHITE, COLOR_BLUE, COLOR_RED});
    bar.SetLabelStyle({
        {COLOR_BLACK, COLOR_BLUE}, {COLOR_BLACK, COLOR_RED}}
    );
    bar.SetLabel({"11", "22", "33", "44", "55", "66"});
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
#elif (defined FORM)
    Form form;
    form.SetRect(10, 30, 0, 0);
    form._query = {"test1", "test2", "test3", "test4", "test5"};
    form._default = {"             ", "test2"};
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
#endif
    return 0;
}
