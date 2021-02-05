#include "MyForm.h"
#include "EventHandler.h"

MyForm::MyForm()
{
    pBtn = new Button;
    pBtn->SetRect(3, 3, 0, 0);
    auto a = bind(&MyForm::btn1_clicked, this);
    pBtn->_clicked += *(new EventHandler(a));
    auto b = bind(&MyForm::btn2_clicked, this);
    EventHandler c(b);
    pBtn->_clicked += c;
    Add(pBtn);
}

MyForm::~MyForm()
{
}
void MyForm::btn2_clicked()
{
    printw("22222\n");
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
        Rect rect = (*it)->GetRect();
        if ((rect.min.y <= y && y <= rect.max.y) &&
           (rect.min.x <= x && x <= rect.max.x))
            (*it)->_clicked();
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
    MEVENT event;
    while (int ch = getch())
    {
        switch (ch)
        {
        case 'q':
            return;
        case KEY_MOUSE:
            if (getmouse(&event) == OK)
            {
                if (event.bstate == BUTTON1_CLICKED)
                    OnMouseLCliecked(event.y, event.x);
            }
            break;
        }
    }
}