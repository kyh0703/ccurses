#include <iostream>
#include <unistd.h>
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
    MessageBox("test", "hihihi111111111111111111111111111111111aaaaaaaaaaaaaaa1111111", MB_OK);
    // getch();
    // MyForm my_form;
    // my_form.Draw();
    // my_form.Run();
    // ui.Regist(&my_form);
    // ui.PollEvent();
}