#pragma once
#include "WinForm.h"

class MyForm : public WinForm
{
public:
    MyForm();
    ~MyForm();
    void btn2_clicked();
    void btn1_clicked();
    void OnMouseLCliecked(int y, int x);
    void OnMouseRCliecked(int y, int x);
    void OnMouseArrived(int y, int x);
    void OnMouseLeave(int y, int x);
    void IsInclude(int y, int x);
    void OnKeyEvent(int ch);

private:
    Button *pBtn;
};