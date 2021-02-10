#include "MyForm.h"

MyForm::MyForm()
{
    TextBox *text = new TextBox;
    text->_rect = {5, 10, 10, 10};
    text->_box = true;
    text->_text = "asdfffffffffffffffffffffffffffffff";
    Add(text);

    // pBtn = new Button;
    // pBtn->_rect = {3, 10, 0, 0};
    // pBtn->_color = {COLOR_BLACK, COLOR_RED};
    // pBtn->_title_color = COLOR_RED;
    // pBtn->_title = "test";
    // pBtn->_text = "한글";
    // pBtn->_enable = false;
    // pBtn->_click = bind(&MyForm::btn1_clicked, this);
    // Add(pBtn);

    // pBtn2 = new Button;
    // pBtn2->_rect = {3, 11, 10, 10};
    // pBtn2->_text = "btn2222222";
    // pBtn2->_click = bind(&MyForm::btn2_clicked, this);
    // Add(pBtn2);

    // pList = new List;
    // pList->_rect = {5, 10, 15, 10};
    // pList->_rows = {"test1", "test2", "test3", "test4", "test5", "test6"};
    // pList->_mouse_wheel_up = bind(&MyForm::list_wheel_up, this, placeholders::_1);
    // pList->_mouse_wheel_down = bind(&MyForm::list_wheel_down, this, placeholders::_1);
    // Add(pList);

    // CheckBox *check = new CheckBox;
    // check->_rect = {5, 15, 20, 20};
    // check->_text = "Checkbox";
    // check->_is_check = true;
    // Add(check);

    // Input *input = new Input;
    // input->_rect = {2, 15, 20, 20};
    // input->_is_active = true;
    // input->SetText("test");
    // Add(input);
}

MyForm::~MyForm()
{
}

void MyForm::list_wheel_up(MouseArgs args)
{
    pList->ScrollUp();
}

void MyForm::list_wheel_down(MouseArgs args)
{
    pList->ScrollDown();
}

void MyForm::btn1_clicked()
{
    pBtn->_text = "alter";
}

void MyForm::btn2_clicked()
{
    pBtn2->_text = "alter";
}