#include "MyForm.h"

MyForm::MyForm()
{
    pBtn = new Button;
    pBtn->SetRect(30, 30, 0, 0);
    pBtn->_clicked = bind(&MyForm::btn1_clicked, this);
    Add(pBtn);
}

MyForm::~MyForm()
{
}

void MyForm::btn1_clicked()
{
    printw("1111\n");
}

void MyForm::OnMouseLCliecked(int y, int x)
{
    list<Widget *>::iterator it;
    for (it = _pWidgetes.begin(); it != _pWidgetes.end(); ++it)
    {
        Widget *pWidget = (*it);
        Rect rect = pWidget->GetRect();
        if ((rect.min.y <= y && y <= rect.max.y) &&
           (rect.min.x <= x && x <= rect.max.x))
        {
            if (pWidget->_clicked)
                pWidget->_clicked();
            if (pWidget->_mouseClick)
                pWidget->_mouseClick();
        }
    }
}

void MyForm::OnMouseRCliecked(int y, int x)
{
    list<Widget *>::iterator it;
    for (it = _pWidgetes.begin(); it != _pWidgetes.end(); ++it)
    {
        Rect rect = (*it)->GetRect();
        if ((rect.min.y <= y && y <= rect.max.y) &&
            (rect.min.x <= x && x <= rect.max.x))
            (*it)->_clicked();
    }
}

void MyForm::OnKeyEvent(int ch)
{
    while (int ch = getch())
    {
        switch (ch)
        {
        case 'q':
            return;
        case KEY_MOUSE:
            MEVENT event;
            if (getmouse(&event) == OK)
            {
                if (event.bstate == BUTTON1_CLICKED)
                    OnMouseLCliecked(event.y, event.x);
                else if (event.bstate == BUTTON1_DOUBLE_CLICKED)
                    printf("1\n");
                else if (event.bstate == BUTTON1_PRESSED)
                    printf("2\n");
            }
            break;
        }
    }
}