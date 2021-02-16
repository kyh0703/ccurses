#include <iostream>
#include <unistd.h>
#include <string.h>
#include <wchar.h>
#include "Palette.h"
#include "MessageBox.h"
#include "MyForm.h"

int main(void)
{
    // const wchar_t start_ch = L'가';
    // const wchar_t end_ch = L'힣';
    // wchar_t s[] = L"a글";
    // wstring s1 = L"a글입니다";
    // if (start_ch <= s1[0] && s1[0] <= end_ch)
    //     printf("한글입니다");
    // else
    //     printf("한글이아닙니다");


    // getch();
    Palette ui;
    if (!ui.Init())
    {
        cout << "ncurses init Fail" << endl;
        return 1;
    }

    // for (size_t i = 0; i < name.size(); ++i)
    // {
    //     cchar_t t;
    //     setcchar(&t, &name[i], 0, A_NORMAL, NULL);
    //     add_wch(&t);
    // }

    // cchar_t t;
    // setcchar(&t, L"한", 0, A_NORMAL, NULL);
    // mvadd_wch(0, 2, &t);
    // getch();
    MyForm my_form;
    my_form.Draw();
    my_form.Run();
    // ui.Regist(&my_form);
    // ui.PollEvent();
}