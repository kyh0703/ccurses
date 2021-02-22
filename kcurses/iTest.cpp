#include <iostream>
#include <unistd.h>
#include <string.h>
#include <wchar.h>
#include "Palette.h"
#include "MessageBox.h"
#include "MyForm.h"

int main(void)
{
    Palette ui;
    if (!ui.Init())
    {
        cout << "ncurses init Fail" << endl;
        return 1;
    }

    MyForm my_form;
    my_form._text = L"정보입력";
    ui.Add(&my_form);

    MyForm2 my_form2;
    ui.Add(&my_form2);

    ui.PollEvent();
}