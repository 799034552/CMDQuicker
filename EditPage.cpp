#include "EditPage.h"
#include <fstream>
#include "cmd.h"
EditPage::EditPage(const QString &title, QWidget *parent)
    :SlidePage(title, parent, 1, 0, QRect(20,30,20,30))
{
    QHBoxLayout *main_layout = new QHBoxLayout();
    addLayout(main_layout, 1);
    QVBoxLayout *left_layout = new QVBoxLayout();
    QVBoxLayout *right_layout = new QVBoxLayout();
    main_layout->addLayout(left_layout, 3);
    main_layout->addLayout(right_layout, 1);
    //左边栏
    editor = new QTextEdit();
    left_layout->addWidget(editor);


    //右边栏
    input_box = new InputBox(2, "在此输入名称", 3, 13);
    input_box->setMinimumSize(0, 40);
    input_box->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    QPushButton *btn = new QPushButton("confirm");
    btn->setStyleSheet("QPushButton{outline: none;padding-left:10px;padding-right:10px;font-size: 18px;background-color: rgb(240, 240, 240);border-radius: 6px;font-family: Corbel;}\nQPushButton:Hover{background-color: rgb(223, 249, 255)}\nQPushButton:pressed{background-color: #2196F3}");
    btn->setMinimumSize(0, 30);
    btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QPushButton *cancel = new QPushButton("cancel");
    cancel->setStyleSheet("QPushButton{outline: none;padding-left:10px;padding-right:10px;font-size: 18px;background-color: rgb(240, 240, 240);border-radius: 6px;font-family: Corbel;}\nQPushButton:Hover{background-color: #EF5350}\nQPushButton:pressed{background-color: #EF5350}");
    cancel->setMinimumSize(0, 30);
    cancel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    right_layout->setContentsMargins(10,0,10,0);
    right_layout->addWidget(input_box);
    right_layout->addWidget(btn);
    right_layout->addWidget(cancel);
    right_layout->addStretch();
    right_layout->setSpacing(10);

    editor->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    editor->setStyleSheet("QTextEdit{font-family: Corbel;font-size: 18px;border: 2px solid #0984e3;background-color: rgb(255,255,255); border-radius: 8px;padding-left:20px;padding-top:20px;padding-right:20px;padding-bottom:20px;}");
    editor->setContentsMargins(20,20,20,20);
//    end_add();

    connect(btn, &QPushButton::clicked, this , [=]{
        if(editing_w == nullptr)
        {
            string title = input_box->text().toStdString();
            if (title == "")
                return;
            auto split_text = editor->document()->toPlainText().split("\n");
            file_data.push_back(vector<string>());
            file_data.back().push_back(title);
            for(const auto &x: split_text)
            {
                file_data.back().push_back(x.toStdString());
            }
            for(const auto &x: file_data)
            {
                for(const auto &y: x)
                {
                   qDebug()<<QString::fromUtf8(y);
                }
            }
            write_back();
            emit add_commit();
            slide_out();
        }
        else
        {
            string title = input_box->text().toStdString();
            if (title == "")
                return;
            auto split_text = editor->document()->toPlainText().split("\n");
            vector<string> tmp;
            tmp.push_back(title);
            for(const auto &x: split_text)
            {
                tmp.push_back(x.toStdString());
            }
            emit edit_commit(editing_w, tmp);
            slide_out();
        }

    });
    connect(cancel, &QPushButton::clicked, this , [=]{
        slide_out();
    });

//    connect(editor, &QTextEdit::textChanged,this , [=](){

//        std::ofstream out_file("F:\\c\\C++\\QT\\cmd_quicker\\build-CMDQuick-Desktop_Qt_6_3_2_MinGW_64_bit-Debug\\data.conf", std::ios::out);
//        std::string tmp = editor->document()->toPlainText().toStdString();
//        qDebug()<<tmp.find("\n")<<"\n";
//        str_replace(tmp, "\n", "$$$#n");
//        out_file<<tmp;
//        out_file.close();
//    });
}

void EditPage::set_contain(QString title, QString contain, QWidget *w)
{
    editing_w = w;
    editor->setText(contain);
    input_box->set_text(title);
}
void EditPage::slide_in(bool is_max, QString title, QString contain, QWidget *w)
{
    set_contain(title, contain, w);
    SlidePage::slide_in(is_max);
}
