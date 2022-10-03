#ifndef CUSTOMER_SIGNAL_H
#define CUSTOMER_SIGNAL_H
#include <QLineEdit>
class cus_QLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    using QLineEdit::QLineEdit;
protected:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent* event) override;
    void focusInEvent(QFocusEvent *e) override;
    void focusOutEvent(QFocusEvent *e) override;

signals:
    void mouse_enter();
    void mouse_leave();
    void focus_in();
    void focus_out();

};

class cus_QWidget: public QWidget
{
    Q_OBJECT
public:
    cus_QWidget() {setAttribute(Qt::WA_StyledBackground);}
private:
    bool is_press = false;
protected:
    void mousePressEvent(QMouseEvent *event) {is_press = true;};
    void mouseReleaseEvent(QMouseEvent *event) {if (is_press) {is_press = false; emit click_event();}};
signals:
    void click_event();
};

class cus_QPushButton: public QPushButton
{
    Q_OBJECT
public:
    using QPushButton::QPushButton;
protected:
    void enterEvent(QEnterEvent *event){this->show();};
    void leaveEvent(QEvent* event) {this->hide();};
};

#endif // CUSTOMER_SIGNAL_H
