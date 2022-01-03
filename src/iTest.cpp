#include "MessageBox.h"
#include "Palette.h"
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <wchar.h>

class MyForm : public Form
{
public:
    MyForm()
    {
        TextBox *box = new TextBox(3, 30, 15, 80);
        box->SetText(L"hkhkhkhkhk");
        box->SetBox(true);
        Add(box);

        ProgressBar *prs = new ProgressBar(3, 25, 20, 20);
        prs->SetTitle(L"제목");
        prs->SetPercent(100);
        Add(prs);

        pBtn = new Button(3, 10, 21, 5);
        pBtn->SetTitle(L"a");
        pBtn->SetText(L"1");
        pBtn->_click = bind(&MyForm::btn1_clicked, this);
        Add(pBtn);

        CheckBox *check = new CheckBox(1, 10, 5, 30);
        check->SetText(L"hihihihi");
        Add(check);

        Radio *radio = new Radio(1, 10, 6, 30);
        radio->SetText(L"hihihihi222");
        Add(radio);

        BarChart *bar = new BarChart(10, 20, 2, 80);
        bar->SetTitle(L"하이");
        bar->SetDatas({
            1.0,
            2.0,
            3.0,
            2.0,
        });
        bar->SetLabels({
            L"1번",
            L"2번",
            L"3번",
            L"4번",
        });
        Add(bar);

        Table *table = new Table(20, 30, 5, 50);
        table->SetTitle(L"햐햐햐햐");
        table->SetRows({
            {L"하이", L"하이2"},
            {L"하이", L"하이2"},
        });
        Add(table);

        Input *input = new Input(1, 10, 30, 12);
        Add(input);

        List *list = new List(10, 30, 2, 0);
        list->SetTitle(L"파일리스트");
        list->SetRows({
            L"1234",
            L"1234",
            L"1234",
            L"1234",
            L"1234",
            L"1234",
            L"1234",
            L"1234",
            L"1234",
            L"1234",
            L"1234",
            L"1234",
            L"1234",
            L"1234",
            L"1234",
            L"1234",
            L"2번입니다",
            L"3번입니다",
            L"3번입니다",
            L"3번입니다",
            L"3번입니다",
            L"3번입니다",
            L"3번입니다",
            L"3번입니다",
            L"3번입니다",
        });
        Add(list);
    }

    virtual ~MyForm() {}

    void btn1_clicked()
    {
        int ret = MessageBox(L"안녕", L"BTS를 아시나요?", MB_TYPE_YESNO);
        Delete(pBtn);
    }

    void btn2_clicked()
    {
        pBtn2->SetText(L"alter");
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
        pBtn = new Button(3, 10, 10, 10);
        pBtn->SetTitle(L"버튼");
        pBtn->SetText(L"등록");
        pBtn->SetEnable(true);
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
    Palette ui(50, 120);
    if (!ui.Init(Theme::DARK_WHITE))
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
