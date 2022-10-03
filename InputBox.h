#ifndef INPUTBOX_H
#define INPUTBOX_H
#include "customer_signal.h"
class InputBox : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(double m_bg_width MEMBER bg_width NOTIFY bg_width_change)
public:
    InputBox(float radius = 3,const QString &PlaceholderText = "",const qreal border_margin = 5,const int &font_size = 15);
    double bg_width = 0;
    QString text() {return editor->text();}
    void set_text(QString &x) {editor->setText(x);}
protected:
    void resizeEvent(QResizeEvent *event);
private:
    float radius;
    QWidget *background;
    QPropertyAnimation* slide_in;
    QPropertyAnimation* slide_out;
    cus_QLineEdit *editor;
    int font_size;
signals:
    void bg_width_change();
    void text_change(const QString &);
};

#endif // INPUTBOX_H
