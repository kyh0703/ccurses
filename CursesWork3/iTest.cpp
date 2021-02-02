#include <iostream>
#include <unistd.h>
#include "Palette.h"

Palette ui;
void TestText();
void TestPopup();
void TestYesNo();
void TestTap();
void TestList();
void TestProgressBar();
void TestTable();
void TestBarChart();
void TestInput();

int main(void)
{
    if (!ui.Init())
    {
        cout << "ncurses init Fail" << endl;
        return 1;
    }

    TestList();
    return 1;
}

void TestText()
{
    TextBox text;
    text.SetRect(5, 15, 10, 10);
    text.SetTitle("hello");
    text._text = "hihihi111111111111111111111111111111111111";
    text._style = {COLOR_BLACK, COLOR_RED};
    ui.Render({&text});
    while (int ch = getchar())
    {
        switch (ch)
        {
        case 'q':
            return;
        }
    }
}

void TestPopup()
{
    Popup pop;
    pop.SetRect(10, 20, 10, 10);
    pop.SetTitle("hello");
    pop._text = "hihihiaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa111111111";
    pop._textColor = COLOR_RED;
    ui.Render({&pop});
    while (int ch = getchar())
    {
        switch (ch)
        {
        case 'q':
            return;
        }
    }
}

void TestYesNo()
{
    YesNo yn;
    yn.SetRect(10, 20, 10, 10);
    yn.SetTitle("hello");
    yn._text = "hihihiaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa111111111";
    yn._textColor = COLOR_RED;
    ui.Render({&yn});
    while (int ch = getchar())
    {
        switch (ch)
        {
        case 'q':
            return;
        case 'k':
            yn.ForcusLeft();
            break;
        case 'l':
            yn.ForcusRight();
            break;
        default:
            // ui.Render({&yn});
            break;
        }
    }
}

void TestTap()
{
    Tab tab;
    tab.SetRect(3, 40, 5, 5);
    tab._tabs = {"test1", "test2", "test3", "test4"};

    TextBox txt1;
    txt1.SetRect(10, 10, 10, 10);
    txt1.SetTitle("tab1111");

    TextBox txt2;
    txt2.SetRect(10, 10, 10, 10);
    txt2.SetTitle("tab2222");

    switch (tab._activeIdx)
    {
    case 0:
        ui.Render({&tab, &txt1});
        break;
    case 1:
        ui.Render({&tab, &txt2});
        break;
    default:
        break;
    }

    while (int ch = getchar())
    {
        switch (ch)
        {
        case 'q':
            return;
        case 'h':
            tab.ForcusLeft();
            switch (tab._activeIdx)
            {
            case 0:
                ui.Render({&tab, &txt1});
                break;
            case 1:
                ui.Render({&tab, &txt2});
                break;
            default:
                ui.Render({&tab});
                break;
            }
            break;
        case 'k':
            tab.ForcusRight();
            switch (tab._activeIdx)
            {
            case 0:
                ui.Render({&tab, &txt1});
                break;
            case 1:
                ui.Render({&tab, &txt2});
                break;
            default:
                ui.Render({&tab});
                break;
            }
            break;
        default:
            break;
        }
    }
}

void TestList()
{
    List list;
    list.SetRect(5, 15, 10, 10);
    list._rows = {"test11111", "test2", "test3", "test4",
                  "test5", "test6", "test7"};
    ui.Render({&list});

    while (int ch = getchar())
    {
        switch (ch)
        {
        case 'q':
            return;
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
        ui.Render({&list});
    }
}

void TestProgressBar()
{
    ProgressBar pro;
    pro.SetRect(3, 50, 0, 0);
    pro._percent = 10;
    pro._label = "12341234";
    ui.Render({&pro});
    while (int ch = getchar())
    {
        switch (ch)
        {
        case 'q':
            return;
        case 'j':
            if (0 < pro._percent)
                pro._percent--;
            break;
        case 'k':
            if (pro._percent < 100)
                pro._percent++;
            break;
        default:
            break;
        }
        ui.Render({&pro});
    }
}

void TestTable()
{
    Table table;
    table.SetRect(9, 38, 5, 10);
    table._alignment = Table::LEFT;
    table._rows = {
        {"test", "test1", "test2"},
        {"test3", "test4", "test6"},
        {"test3", "test4", "test7"},
        {"test3", "test4", "test7"},
    };
    ui.Render({&table});
    while (int ch = getchar())
    {
        switch (ch)
        {
        case 'q':
            return;
        default:
            break;
        }
    }
}

void TestBarChart()
{
    BarChart bar;
    bar.SetRect(20, 50, 0, 0);
    bar._data = {7, 6, 5, 4, 3, 2};
    bar._barColor = {COLOR_WHITE, COLOR_BLUE, COLOR_RED};
    bar._labelStyle = {{COLOR_BLACK, COLOR_BLUE}, {COLOR_BLACK, COLOR_RED}};
    bar._label = {"11", "22", "33", "44", "55", "66"};
    ui.Render({&bar});
    while (int ch = getchar())
    {
        switch (ch)
        {
        case 'q':
            return;
        default:
            break;
        }
        ui.Render({&bar});
    }
}

void TestInput()
{
    // Form form;
    // form.SetRect(10, 30, 0, 0);
    // form._query = {"test1", "test2", "test3", "test4", "test5"};
    // form._default = {"             ", "test2"};
    // ui.Render({&form});
    // while (int ch = getchar())
    // {
    //     switch (ch)
    //     {
    //     case 'q':
    //         return 1;
    //     case 'j':
    //         break;
    //     default:
    //         break;
    //     }
    //     ui.Render({&form});
    // }
}