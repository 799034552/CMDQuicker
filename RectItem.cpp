#include "RectItem.h"

RectItem::RectItem(QString name)
{
    setAttribute(Qt::WA_StyledBackground);
    layout = new QVBoxLayout();
    this->setLayout(layout);
    title = new QLabel(name);
    title->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    title->setAlignment(Qt::AlignCenter);
    title->setWordWrap(true);
    title->setStyleSheet("font-size:20px; font-family: Microsoft Sans Serif; font-weight:bold; background-color: none");
    layout->addWidget(title);

    this->setStyleSheet("QWidget{border-radius: 15px; background-color: rgb(240,240,240);} QWidget:Hover{background-color: rgb(241, 246, 249);}");

    indicator.reset(new QWidget(this));
    longger_ani.reset(new QPropertyAnimation(indicator.get(), "geometry", this));
    longger_ani->setDuration(200);
    shortter_ani.reset(new QPropertyAnimation(indicator.get(), "geometry", this));
    shortter_ani->setDuration(200);


    //编辑框外包装
    QWidget *last_line = new QWidget();
    last_line->setStyleSheet("background:none");
    QHBoxLayout *editor_h_laytor = new QHBoxLayout();
    last_line->setLayout(editor_h_laytor);
    layout->addWidget(last_line);

    //编辑框内包装
    //编辑框
    editor_warper = new cus_QWidget();
    editor_warper->setContentsMargins(0,10,0,10);
    QHBoxLayout *editor_laytor = new QHBoxLayout();
    editor.reset(new QLabel());
    editor->setPixmap(QPixmap(":/assert/icons/editor.svg"));
    editor->setScaledContents(true);
    editor->setAlignment(Qt::AlignCenter);
    editor->setStyleSheet("background-color:none");
    editor_laytor->addWidget(editor.get());
    editor_laytor->setAlignment(Qt::AlignCenter);

    editor_warper->setLayout(editor_laytor);
    editor_laytor->setContentsMargins(0,0,0,0);
    QGraphicsDropShadowEffect *windowShadow = new QGraphicsDropShadowEffect(this);
    windowShadow->setBlurRadius(10);
    windowShadow->setColor(QColor(0, 0, 0));
    windowShadow->setOffset(0, 0);
    editor_warper->setGraphicsEffect(windowShadow);

    //编辑框
    deler_warper = new cus_QWidget();
    deler_warper->setContentsMargins(0,10,0,10);
    editor_laytor = new QHBoxLayout();
    deler.reset(new QLabel());
    deler->setPixmap(QPixmap(":/assert/icons/delete.svg"));
    deler->setScaledContents(true);
    deler->setAlignment(Qt::AlignCenter);
    deler->setStyleSheet("background-color:none");
    editor_laytor->addWidget(deler.get());
    editor_laytor->setAlignment(Qt::AlignCenter);

    deler_warper->setLayout(editor_laytor);
    editor_laytor->setContentsMargins(0,0,0,0);
    windowShadow = new QGraphicsDropShadowEffect(this);
    windowShadow->setBlurRadius(10);
    windowShadow->setColor(QColor(0, 0, 0));
    windowShadow->setOffset(0, 0);
    deler_warper->setGraphicsEffect(windowShadow);



    editor_h_laytor->addWidget(editor_warper);
    editor_h_laytor->addWidget(deler_warper);
    editor_h_laytor->setSpacing(20);
    editor_h_laytor->setAlignment(Qt::AlignCenter);

    opacity_effect = new QGraphicsOpacityEffect(last_line);
    opacity_effect->setOpacity(0);
    last_line->setGraphicsEffect(opacity_effect);
    connect(this, &RectItem::opacity_change, this, [=]{
        opacity_effect->setOpacity(this->opcaity);
    });

    // 选择启动方式
    bg = new QWidget(this);
    bg->lower();
    bg->setStyleSheet("QWidget{background-color: rgba(0,0,0,0)}");
    QHBoxLayout *start_fun = new QHBoxLayout();
    start_fun->setContentsMargins(0,0,0,0);
    start_fun->setSpacing(0);
    bg->setLayout(start_fun);
    left_btn = new QPushButton("可\n视\n启\n动");
    right_btn = new QPushButton("不\n可\n视\n启\n动");
    start_fun->addWidget(left_btn);
    start_fun->addWidget(right_btn);
    left_btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    right_btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    left_btn->setStyleSheet("QPushButton{background-color: #39BAE8; border-radius: 15px; margin-right:-30px;text-align: left;padding-left:30px;font-size:20px;color:white}");
    right_btn->setStyleSheet("QPushButton{background-color: #B9EDF8; border-radius: 15px; margin-left:-30px;text-align: right;;padding-right:30px;font-size:20px;color:white}");

    QSizePolicy sp_retain = left_btn->sizePolicy();
    sp_retain.setRetainSizeWhenHidden(true);
    left_btn->setSizePolicy(sp_retain);
    sp_retain = right_btn->sizePolicy();
    sp_retain.setRetainSizeWhenHidden(true);
    right_btn->setSizePolicy(sp_retain);
    sp_retain = bg->sizePolicy();
    sp_retain.setRetainSizeWhenHidden(true);
    bg->setSizePolicy(sp_retain);
    left_btn->hide();
    right_btn->hide();
//    bg->hide();



    // 动画
    fade_in = new QPropertyAnimation(this, "m_opacity");
    fade_in->setDuration(200);
    fade_in->setStartValue(0);
    fade_in->setEndValue(0.99);

    connect(this, &RectItem::size_change, this, [=]{
        this->move(QPoint(_size.x(), _size.y()));
        this->setFixedSize(_size.size());
    });
    connect(deler_warper, &cus_QWidget::click_event, this, [=](){
        emit delete_event(this);
    });
    connect(editor_warper, &cus_QWidget::click_event, this, [=](){
        emit edit_event(this);
    });
    indicator->raise();
}

void RectItem::resizeEvent(QResizeEvent *event)
{
    indicator->resize(this->width() * 0.1, 6);
    indicator->move(this->width() * 0.45, this->height() - 21);
    indicator->setStyleSheet("border-radius:3px;background-color:#afafaf");
    layout->setContentsMargins(5,5,5, 30);
    editor_warper->setFixedSize(this->width() * 0.15, this->height() * 0.2);
    deler_warper->setFixedSize(this->width() * 0.15, this->height() * 0.2);
    int w = std::min(editor_warper->width(), editor_warper->height());
    editor->setFixedSize(w * 0.8, w * 0.8);
    deler->setFixedSize(w * 0.8, w * 0.8);
//    editor_warper->setStyleSheet(QString::asprintf("QWidget{border-radius:%fpx; background-color: rgb(245,245,245);} QWidget:hover {background-color: rgb(159, 234, 255);} QPushButton:pressed {background-color: rgb(245,245,245);};",(w * 0.15)));
    editor_warper->setStyleSheet(QString::asprintf("QWidget{border-radius:%fpx; background-color: rgb(245,245,245);} QWidget:hover {background-color: rgb(159, 234, 255);} QPushButton:pressed {background-color: rgb(245,245,245);};",(w * 0.15)));
    deler_warper->setStyleSheet(QString::asprintf("QWidget{border-radius:%fpx; background-color: #EF5350;} QWidget:hover {background-color: #E53935;}",(w * 0.15)));
    bg->resize(this->size());
}

void RectItem::enterEvent(QEnterEvent *event)
{
    if (shortter_ani->state() == QPropertyAnimation::Running)
        shortter_ani->stop();
    if (longger_ani->state() == QPropertyAnimation::Running)
        longger_ani->stop();
    longger_ani->setStartValue(indicator->geometry());
    longger_ani->setEndValue(QRectF(this->width() * 0.2, this->height() - 21, this->width() * 0.6, 6));
    longger_ani->start();
    indicator->setStyleSheet("QWidget{border-radius:3px;background-color:#0078d4}");
    fade_in->start();
    bg->show();
}
void RectItem::leaveEvent(QEvent* event)
{
    if (longger_ani->state() == QPropertyAnimation::Running)
        longger_ani->stop();
    if (shortter_ani->state() == QPropertyAnimation::Running)
        shortter_ani->stop();
    if (fade_in->state() == QPropertyAnimation::Running)
        fade_in->stop();
    shortter_ani->setStartValue(indicator->geometry());
    shortter_ani->setEndValue(QRectF(this->width() * 0.45, this->height() - 21, this->width() * 0.1, 6));
    shortter_ani->start();
    indicator->setStyleSheet("QWidget{border-radius:3px;background-color:#afafaf}");
    this->opcaity = 0.01;
//    emit this->opacity_change();
    opacity_effect->setOpacity(this->opcaity);
//    left_btn->hide();
//    right_btn->hide();
    bg->hide();
}
void RectItem::mouseMoveEvent(QMouseEvent *event)
{
    if(event->pos().x() < this->width() / 2)
    {
        left_btn->show();
        right_btn->hide();
    }
    else
    {
        right_btn->show();
        left_btn->hide();
    }

}
void RectItem::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->pos().x() <0 || event->pos().x() > this->width() || event->pos().y() < 0 || event->pos().y() > this->height())
        return;
    if(event->pos().x() < this->width() / 2)
        emit click_event(this, true);
    else
        emit click_event(this, false);


}
