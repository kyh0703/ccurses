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
        TextBox *text = new TextBox;
        text->_rect = {5, 10, 10, 10};
        text->_box = true;
        text->_text = L"한글입니다아아aaa";
        Add(text);

        Input *input = new Input;
        input->_rect = {2, 15, 20, 10};
        input->_is_active = true;
        input->SetText("test");
        Add(input);

        // pBtn = new Button;
        // pBtn->_rect = {3, 10, 5, 5};
        // pBtn->_color = {COLOR_BLACK, COLOR_RED};
        // pBtn->_title_color = COLOR_RED;
        // pBtn->_title = L"a";
        // pBtn->_text = L"등록";
        // pBtn->_enable = true;
        // pBtn->_click = bind(&MyForm::btn1_clicked, this);
        // Add(pBtn);

        // Button *pBtn3 = new Button;
        // pBtn3->_rect = {11, 10, 15, 15};
        // pBtn3->_title = L"뭐하지..?";
        // pBtn3->_text = L"후..";
        // Add(pBtn3);

        // pBtn2 = new Button;
        // pBtn2->_rect = {3, 11, 10, 10};
        // pBtn2->_title = L"b";
        // pBtn2->_text = L"btn2222222";
        // pBtn2->_enable = false;
        // pBtn2->_click = bind(&MyForm::btn2_clicked, this);
        // Add(pBtn2);

        // pList = new List;
        // pList->_rect = {5, 15, 15, 10};
        // pList->_rows = {L"안녕", L"안녕1", L"안녕2", L"안녕3", L"test5", L"test6"};
        // pList->_mouse_wheel_up = bind(&MyForm::list_wheel_up, this, placeholders::_1);
        // pList->_mouse_wheel_down = bind(&MyForm::list_wheel_down, this, placeholders::_1);
        // Add(pList);

        // CheckBox *check = new CheckBox;
        // check->_rect = {1, 15, 25, 25};
        // check->_text = L"TLS사용여부";
        // check->_checked = true;
        // check->_focus = false;
        // Add(check);


    }

    virtual ~MyForm() {}

    void list_wheel_up(MouseArgs args)
    {
        pList->ScrollUp();
    }

    void list_wheel_down(MouseArgs args)
    {
        pList->ScrollDown();
    }

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
    List *pList;
};

class MyForm2 : public Form
{
public:
    MyForm2()
    {
        pBtn = new Button;
        pBtn->_rect = {3, 10, LINES / 2, COLS / 2};
        pBtn->_color = {COLOR_BLACK, COLOR_RED};
        pBtn->_title_color = COLOR_RED;
        pBtn->_title = L"버튼";
        pBtn->_text = L"등록";
        pBtn->_enable = false;
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