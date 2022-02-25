#include "MessageBox.h"
#include "Palette.h"
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <wchar.h>

class KolangForm1 : public Form
{
public:
    KolangForm1()
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
        pBtn->_click = bind(&KolangForm1::btn1_clicked, this);
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

    virtual ~KolangForm1() {}

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

class KolangForm2 : public Form
{
public:
    KolangForm2()
    {
        pBtn = new Button(3, 10, 10, 10);
        pBtn->SetTitle(L"버튼");
        pBtn->SetText(L"등록");
        pBtn->SetEnable(true);
        pBtn->_click = bind(&KolangForm2::btn1_clicked, this);
        Add(pBtn);
    }
    virtual ~KolangForm2() {}

    void btn1_clicked()
    {
        int ret = MessageBox(L"test", L"BTS2를 아시나요?", MB_TYPE_YESNO);
    }

private:
    Button *pBtn;
};

class EngForm1 : public Form
{
public:
    EngForm1()
    {
        TextBox *box = new TextBox(3, 30, 15, 80);
        box->SetText(L"test");
        box->SetBox(true);
        Add(box);

        ProgressBar *prs = new ProgressBar(3, 25, 20, 20);
        prs->SetTitle(L"test2");
        prs->SetPercent(100);
        Add(prs);

        pBtn = new Button(3, 10, 21, 5);
        pBtn->SetTitle(L"a");
        pBtn->SetText(L"1");
        pBtn->_click = bind(&EngForm1::btn1_clicked, this);
        Add(pBtn);

        CheckBox *check = new CheckBox(1, 10, 5, 30);
        check->SetText(L"hihihihi");
        Add(check);

        Radio *radio = new Radio(1, 10, 6, 30);
        radio->SetText(L"hihihihi222");
        Add(radio);

        BarChart *bar = new BarChart(10, 20, 2, 80);
        bar->SetTitle(L"test3");
        bar->SetDatas({
            1.0,
            2.0,
            3.0,
            2.0,
        });
        bar->SetLabels({
            L"test4",
            L"test4",
            L"test4",
            L"4test4번",
        });
        Add(bar);

        Table *table = new Table(20, 30, 5, 50);
        table->SetTitle(L"test4");
        table->SetRows({
            {L"test4", L"test4"},
            {L"test4", L"test4"},
        });
        Add(table);

        Input *input = new Input(1, 10, 30, 12);
        Add(input);

        List *list = new List(10, 30, 2, 0);
        list->SetTitle(L"test4");
        list->SetRows({
            L"test4",
            L"test4",
            L"test4",
            L"test4",
            L"test4",
            L"test4",
            L"test4",
            L"test4",
            L"test4",
            L"test4",
            L"test4",
            L"test4",
            L"test4",
            L"test4",
            L"test4",
            L"test4",
            L"test4",
            L"test4",
            L"test4",
            L"test4",
            L"test4",
            L"test4",
            L"test4",
            L"test4",
            L"test4",
        });
        Add(list);
    }

    virtual ~EngForm1() {}

    void btn1_clicked()
    {
        int ret = MessageBox(L"test4", L"test4 test4?", MB_TYPE_YESNO);
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

class EngForm2 : public Form
{
public:
    EngForm2()
    {
        pBtn = new Button(3, 10, 10, 10);
        pBtn->SetTitle(L"btn1_clicked");
        pBtn->SetText(L"btn1_clicked");
        pBtn->SetEnable(true);
        pBtn->_click = bind(&EngForm2::btn1_clicked, this);
        Add(pBtn);
    }
    virtual ~EngForm2() {}

    void btn1_clicked()
    {
        int ret = MessageBox(L"btn1_clicked", L"btn1_clicked", MB_TYPE_YESNO);
    }

private:
    Button *pBtn;
};

int main(void)
{
    Palette ui(50, 120);
    if (!ui.Init(Theme::VSCODE_DARK))
    {
        cout << "ncurses init Fail" << endl;
        return 1;
    }

    KolangForm1 *ko_form1 = new KolangForm1;
    ko_form1->_text = L"test";
    ui.Add(ko_form1);
    KolangForm2 *ko_form2 = new KolangForm2;
    ui.Add(ko_form2);
    EngForm1 *eng_form1 = new EngForm1;
    eng_form1->_text = L"test";
    ui.Add(eng_form1);
    EngForm2 *eng_form2 = new EngForm2;
    ui.Add(eng_form2);
    // ui.Delete(eng_form2);
    ui.PollEvent();
}
