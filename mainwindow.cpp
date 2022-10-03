#include "mainwindow.h"
#include <stdlib.h>
#include "RectItem.h"
#include<windows.h>
#include <shellapi.h>
#include "ui_mainwindow.h"
#include "AIcon.h"
#include "SlidePage.h"
#include "AboutItem.h"
#include "RectItem.h"
#include "cmd.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    cmd_init();
    Init(); //初始化外观和组件
}

void MainWindow::Init()
{
    //添加组件
    add_wight();

    // 设置背景
    ui->main_weight->setStyleSheet(QString::asprintf("QWidget#main_weight{background-color:#00FFFFFF;border:1.5px solid #686868;border-radius: %dpx;background-color: %s;}", BORDER_RADIUS, BG_COLOR));

    // 设置阴影
    QGraphicsDropShadowEffect *windowShadow = new QGraphicsDropShadowEffect(this);
    windowShadow->setBlurRadius(30);
    windowShadow->setColor(QColor(0, 0, 0));
    windowShadow->setOffset(0, 0);
    ui->main_weight->setGraphicsEffect(windowShadow);



    //设置信号与槽
    connect(ui->close_btn, &QPushButton::clicked, this,[=](){this->close();});
    connect(ui->min_btn, &QPushButton::clicked, this,[=](){this->showMinimized();});
    connect(ui->max_btn, &QPushButton::clicked, this,[=](){max_btn_click();});
}

void MainWindow::add_wight() {

    // logo栏
    QWidget *logo = new QWidget();
    QHBoxLayout *HLayout = new QHBoxLayout();
    QLabel *logo_text = new QLabel("CmdQuicker");
    QFont titleFont = QFont("Microsoft Sans Serif", 20);
    logo_text->setFont(titleFont);
    logo_text->setStyleSheet("color: rgb(100,100,100);font-weight: lighter;border-style:none;border-width:0px;margin-left:1px;");
    AIcon *setting = new AIcon(QString(":/assert/icons/settings.svg"));

    connect(setting, &AIcon::click, this, [=](){
        about_page->resize(ui->main_weight->size());
        about_page->slide_in(is_max);
    });
    QPushButton *create_new_btn = new QPushButton();
    create_new_btn->setText("create new");
    create_new_btn->setStyleSheet("QPushButton{outline: none;padding-left:10px;padding-right:10px;font-size: 18px;background-color: rgb(240, 240, 240);border-radius: 6px;font-family: Corbel;}\nQPushButton:Hover{background-color: rgb(223, 249, 255)}\nQPushButton:pressed{background-color: #2196F3}");
    create_new_btn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    connect(create_new_btn, &QPushButton::clicked, this, [=](){
        edit_page->resize(ui->main_weight->size());
        edit_page->slide_in(is_max);
    });


    HLayout->addWidget(logo_text);
    HLayout->addWidget(setting);
    HLayout->addStretch(1);
    HLayout->addWidget(create_new_btn,1);
    logo->setLayout(HLayout);
    logo->setMaximumHeight(50);
    ui->display_layout->addWidget(logo);


    // 内容栏
//    scroll_contain = new QScrollArea();
//    GRidWidget *contain = new GRidWidget(1);
//    QVBoxLayout *VLayout = new QVBoxLayout();
//    HLayout = new QHBoxLayout();
//    VLayout->addLayout(HLayout);
//    contain->setLayout(VLayout);
//    VLayout->setContentsMargins(0,0,0,0);
//    HLayout->setContentsMargins(0,0,0,0);
//    scroll_contain->setWidget(contain);
//    contain->setStyleSheet("background-color:red;");
//    scroll_contain->setStyleSheet("background-color:blue;border:none");
//    scroll_contain->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    scroll_contain->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    contain->resize(600,700);

    scroll_contain = new QScrollArea();
    contain = new GRidWidget(1, 200, 400, 10);


    scroll_contain->setWidget(contain);
    contain->setStyleSheet("background-color:none;");
    scroll_contain->setStyleSheet("background-color:rgb(251, 251, 251);border:none");
    scroll_contain->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scroll_contain->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    contain->resize(600,700);


    for(auto &x: file_data)
    {
        item_add(x);
    }

//    RectItem *test_rect = new RectItem(QString("启动服务器"));
//    test_rect->setParent(contain);
//    contain->add_widget(test_rect);

//    RectItem *test_rect1 = new RectItem(QString("启动服务器"));
//    test_rect1->setParent(contain);
//    contain->add_widget(test_rect1);

//    RectItem *test_rect2 = new RectItem(QString("启动服务器"));
//    test_rect2->setParent(contain);
//    contain->add_widget(test_rect2);

//    RectItem *test_rect3 = new RectItem(QString("启动服务器"));
//    test_rect3->setParent(contain);
//    contain->add_widget(test_rect3);

//    RectItem *test_rect4 = new RectItem(QString("启动服务器"));
//    test_rect4->setParent(contain);
//    contain->add_widget(test_rect4);

//    RectItem *test_rect5 = new RectItem(QString("启动服务器"));
//    test_rect5->setParent(contain);
//    contain->add_widget(test_rect5);


//    test_rect->resize(300,300);



//    RectItem *test_rect = new RectItem(QString("启动服务器"));
//    HLayout->addWidget(test_rect);

    // 滑动窗口
    about_page.reset(new SlidePage("About", ui->main_weight));
    about_page->setMouseTracking(true);
    about_page->addWidget(new AboutItem("author", "string"));
    about_page->addWidget(new AboutItem("version", "0.1"));
    about_page->end_add();
    about_page->raise();
    about_page->hide();

    //搜索框
    QHBoxLayout *search_layout = new QHBoxLayout();
    InputBox *input_box = new InputBox();
    input_box->setMinimumSize(300, 50);
    input_box->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    search_layout->addStretch(1);
    search_layout->addWidget(input_box, 5);
    search_layout->addStretch(1);
    ui->display_layout->addLayout(search_layout);
    ui->display_layout->addWidget(scroll_contain);



    //编辑页
    edit_page.reset(new EditPage("EDIT", ui->main_weight));
    edit_page->setMouseTracking(true);
    edit_page->raise();
    edit_page->hide();

    //border栏
    border.reset(new QWidget(this));
    border->move(ui->main_weight->pos() - QPoint(1, 1));
    border->resize(ui->main_weight->size() + QSize(2, 2));
    QString borderStyle;
    borderStyle = "background-color:#00FFFFFF;border:1.5px solid #686868; border-radius:" + QString::asprintf("%d", BORDER_RADIUS) + "px";
    border->setStyleSheet(borderStyle);
    border->setAttribute(Qt::WA_TransparentForMouseEvents);
    border->show();

    //设置信号与槽
    connect(input_box, &InputBox::text_change, this, &MainWindow::text_change);
    connect(edit_page.get(), &EditPage::add_commit, this, [=]{
        item_add(file_data.back());
        contain->anim_adjust();
    });
    connect(edit_page.get(), &EditPage::edit_commit, this, [=](QWidget *w, vector<string> v) {
        int i = find_item_i(w);
        file_data[i].assign(v.begin(), v.end());
        static_cast<RectItem*>(w)->set_title(QString::fromUtf8(v[0]));
        write_back();
    });

}

void MainWindow::resizeEvent(QResizeEvent *event)
{
//    printf("main_widt_resize: %d, %d\n", ui->main_weight->width(), ui->main_weight->height());
     about_page->resize(ui->main_weight->size());
     edit_page->resize(ui->main_weight->size());
     QPainterPath path;
     path.addRoundedRect(ui->main_weight->rect(), BORDER_RADIUS , BORDER_RADIUS);
     QRegion mask(path.toFillPolygon().toPolygon());
     ui->main_weight->setMask(mask);
     border->move(ui->main_weight->pos() - QPoint(1, 1));
     border->resize(ui->main_weight->size() + QSize(2, 2));
     contain->setMinimumSize(scroll_contain->size());
     contain->resize(scroll_contain->width(), contain->height());
//     qDebug()<<this->size();
}
void MainWindow::showEvent(QShowEvent *event)
{
    about_page->resize(ui->main_weight->size());
    edit_page->resize(ui->main_weight->size());
    QPainterPath path;
    path.addRoundedRect(ui->main_weight->rect(), BORDER_RADIUS -3, BORDER_RADIUS -3);
    QRegion mask(path.toFillPolygon().toPolygon());
    ui->main_weight->setMask(mask);
    border->move(ui->main_weight->pos() - QPoint(1, 1));
    border->resize(ui->main_weight->size() + QSize(2, 2));
    contain->resize(scroll_contain->width(), contain->height());
    this->resize(928, 607);

}

void MainWindow::run_cmd(QString cmd) {
//    std::system(cmd.toStdString().c_str());
//    printf("sfa");
}
void MainWindow::max_btn_click() {
    if ((is_max = !is_max))
    {
        ui->verticalLayout->setContentsMargins(0,0,0,0);
        ui->main_weight->setStyleSheet(QString::asprintf("QWidget#main_weight{border-radius: 0px;background-color: %s;}", BG_COLOR));
        this->showMaximized();
        this->border->hide();

        QPainterPath path;
        path.addRoundedRect(ui->main_weight->rect(), 0, 0);
        QRegion mask(path.toFillPolygon().toPolygon());
        ui->main_weight->setMask(mask);
    }
    else
    {
        ui->verticalLayout->setContentsMargins(30,30,30,30);
        ui->main_weight->setStyleSheet(QString::asprintf("QWidget#main_weight{border-radius: %dpx;background-color: %s;}", BORDER_RADIUS, BG_COLOR));
        this->border->show();
        this->showNormal();

        QPainterPath path;
        path.addRoundedRect(ui->main_weight->rect(), BORDER_RADIUS -3, BORDER_RADIUS -3);
        QRegion mask(path.toFillPolygon().toPolygon());
        ui->main_weight->setMask(mask);
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        is_press.reset(new QPoint((event->globalPosition() - this->frameGeometry().topLeft()).toPoint()));
        width_size = this->size();
    }
}
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(is_max) return;
//    printf("%d\n", abs(event->pos().y() - ui->main_weight->pos().y() - ui->main_weight->height()));
    if (is_press) {
        if (mouse_state == M_NONE)
            this->move((event->globalPosition() - *is_press).toPoint()); //窗口移动
        else
        {
            auto d = (event->globalPosition() - this->frameGeometry().topLeft()).toPoint() - *is_press;
            if(mouse_state & M_LEFT) {
                this->move(event->globalPosition().x() - is_press->x(), this->frameGeometry().y());
                this->resize(-d.x() + this->width(), this->height());
            }
            if(mouse_state & M_TOP) {
                this->move(this->frameGeometry().x(), event->globalPosition().y() - is_press->y());
                this->resize(this->width(), -d.y() + this->height());
            }
            if(mouse_state & M_RIGHT) {
                this->resize(d.x() + width_size.width(), this->height());
            }
            if(mouse_state & M_BOTTOM) {
                this->resize(this->width(), d.y() + width_size.height());
            }
        }

    }
   else {
        mouse_state = M_NONE;
        if (abs(event->pos().y() - ui->main_weight->pos().y() - ui->main_weight->height()) < 5)
            mouse_state |= M_BOTTOM;
        if (abs(event->pos().y() - ui->main_weight->pos().y()) < 5)
            mouse_state |= M_TOP;
        if (abs(event->pos().x() - ui->main_weight->pos().x()) < 5)
            mouse_state |= M_LEFT;
        if (abs(event->pos().x() - ui->main_weight->pos().x() - ui->main_weight->width()) < 5)
            mouse_state |= M_RIGHT;
        if (mouse_state == last_mouse_s) return;
        last_mouse_s = mouse_state;
        switch (mouse_state) {
            case M_NONE:
                setCursor(Qt::ArrowCursor); break;

            case M_TOP:
            case M_BOTTOM:
                setCursor(Qt::SizeVerCursor); break;

            case M_LEFT:
            case M_RIGHT:
                setCursor(Qt::SizeHorCursor); break;

            case M_TOP|M_RIGHT:
            case M_BOTTOM|M_LEFT:
                setCursor(Qt::SizeBDiagCursor); break;

            case M_TOP|M_LEFT:
            case M_BOTTOM|M_RIGHT:
                setCursor(Qt::SizeFDiagCursor); break;
        }
    }

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::text_change(const QString &s)
{
    for(int i = 0; i < file_data.size(); ++i)
    {
        qDebug()<<s<<"  "<<QString::fromUtf8(file_data[i][0]);
        if(file_data[i][0].find(s.toStdString()) != string::npos)
            contain->set_is_show(i, true);
        else
            contain->set_is_show(i, false);
    }
    contain->anim_adjust();
}

void MainWindow::cmd_init()
{
    cmdInit();
}
// 添加应用
void MainWindow::item_add(vector<string> &v)
{
    RectItem *test_rect = new RectItem(QString::fromUtf8(v[0]));
    test_rect->setParent(contain);
    contain->add_widget(test_rect);
    connect(test_rect, &RectItem::click_event, this, &MainWindow::item_click);
    connect(test_rect, &RectItem::edit_event, this, &MainWindow::item_edit);
    connect(test_rect, &RectItem::delete_event, this, &MainWindow::item_delete);
}
void MainWindow::item_click(QWidget* w, bool is_show)
{
    int i = find_item_i(w);
    run_text(file_data[i], is_show);
//    qDebug()<<QString::fromUtf8(file_data[i][0])<<is_show<<"click";
}
void MainWindow::item_edit(QWidget* w)
{
    int i = find_item_i(w);
    qDebug()<<QString::fromUtf8(file_data[i][0])<<"edit";
    string tmp = "";
    if (file_data[i].size() > 1)
    {
        int j = 1;
        for(; j < file_data[i].size() - 1; ++j) {
            tmp += file_data[i][j] + "\n";
        }
        tmp +=file_data[i][j];
    }
    edit_page->slide_in(is_max,QString::fromUtf8(file_data[i][0]), QString::fromUtf8(tmp), w);
}
void MainWindow::item_delete(QWidget* w)
{
    int i = find_item_i(w);
    contain->delete_widget(i);
    file_data.erase(file_data.begin()+i, file_data.begin()+i+1);
    write_back();
}
int MainWindow::find_item_i(QWidget *w)
{
    for(int i = 0; i < contain->widget_list.size(); ++i)
    {
        if (contain->widget_list[i].first == w)
            return i;
    }
    return -1;
}


