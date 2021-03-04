#include <iostream>
#include <unistd.h>
#include <string.h>
#include <wchar.h>
#include "Palette.h"
#include "MessageBox.h"

class MyForm : public Form
{
public:
    MyForm()
    {
        ProgressBar *prs = new ProgressBar;
        prs->_rect = {3, 25, 20, 20};
        prs->_box = true;
        prs->_title = L"제목";
        prs->_percent = 10;
        Add(prs);

        pBtn = new Button;
        pBtn->_rect = {3, 10, 5, 5};
        // pBtn->_color = {COLOR_BLACK, COLOR_RED
        pBtn->_title = L"a";
        pBtn->_text = L"1";
        pBtn->_enable = true;
        pBtn->_click = bind(&MyForm::btn1_clicked, this);
        Add(pBtn);

        pBtn2 = new Button;
        pBtn2->_rect = {3, 10, 15, 15};
        pBtn2->_title = L"a2";
        pBtn2->_text = L"등록2";
        pBtn2->_click = bind(&MyForm::btn2_clicked, this);
        Add(pBtn2);

        Input *input = new Input;
        input->_rect = {1 ,10, 11, 12};
        Add(input);
    }

    virtual ~MyForm() {}

    void btn1_clicked()
    {
        int ret = MessageBox(L"안녕", L"BTS를 아시나요?", MB_TYPE_YESNO);
        Delete(pBtn);
    }

    void btn2_clicked()
    {
        pBtn2->_text = L"alter";
    }

private:
    Button *pBtn, *pBtn2;
    // List *pList;
};

class MyForm2 : public Form
{
public:
    MyForm2()
    {
        pBtn = new Button;
        pBtn->_rect = {3, 10, 10, 10};
        pBtn->_title = L"버튼";
        pBtn->_text = L"등록";
        pBtn->_enable = true;
        pBtn->_click = bind(&MyForm2::btn1_clicked, this);
        Add(pBtn);
    }
    virtual ~MyForm2() {}

    void btn1_clicked()
    {
        int ret = MessageBox(L"안녕", L"BTS2를 아시나요?", MB_TYPE_YESNO);
    }

private:
    Button *pBtn;
};

int main(void)
{
    Palette ui;
    if (!ui.Init())
    {
        cout << "ncurses init Fail" << endl;
        return 1;
    }

    MyForm *my_form = new MyForm;
    my_form->_text = L"정보입력";
    ui.Add(my_form);

    MyForm2 *my_form2 = new MyForm2;
    ui.Add(my_form2);

    // ui.Delete(my_form2);
    ui.PollEvent();
}