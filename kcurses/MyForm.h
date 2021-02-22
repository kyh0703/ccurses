#pragma once
#include "Form.h"

class MyForm : public Form
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

class MyForm2 : public Form
{
public:
    MyForm2();
    virtual ~MyForm2();

    void btn1_clicked();

private:
    Button *pBtn;
};