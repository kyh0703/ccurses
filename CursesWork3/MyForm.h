#pragma once
#include "WinForm.h"

class MyForm : public WinForm
{
public:
    MyForm();
    virtual ~MyForm();

    void list_wheel_up(MouseArgs args);
    void list_wheel_down(MouseArgs args);
    void btn1_clicked();
    void btn2_clicked();

private:
    Button *pBtn, *pBtn2;
    List *pList;
};