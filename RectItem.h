#ifndef RECTITEM_H
#define RECTITEM_H
#include <QWidget>
#include <memory>
#include "customer_signal.h"
class RectItem: public QWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal m_opacity MEMBER opcaity NOTIFY opacity_change)
    Q_PROPERTY(QRect m_size MEMBER _size NOTIFY size_change)
public:
    qreal opcaity = 1;
    QRect _size;
    RectItem(QString name);
    void set_title(const QString &_title) {title->setText(_title);}
private:
    QLabel *title = nullptr;
    QVBoxLayout *layout = nullptr;
    cus_QWidget *editor_warper = nullptr;
    cus_QWidget *deler_warper = nullptr;
    bool is_press = false;
    QWidget *bg = nullptr;
    QPushButton *left_btn = nullptr;
    QPushButton *right_btn = nullptr;

    QGraphicsOpacityEffect *opacity_effect = nullptr;
    QPropertyAnimation * fade_in = nullptr;
    std::shared_ptr<QWidget> indicator = nullptr;
    std::shared_ptr<QLabel> editor = nullptr;
    std::shared_ptr<QLabel> deler = nullptr;
    std::shared_ptr<QPropertyAnimation> longger_ani = nullptr;
    std::shared_ptr<QPropertyAnimation> shortter_ani = nullptr;
    void resizeEvent(QResizeEvent *event) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent* event) override;
    void mousePressEvent(QMouseEvent *event) {is_press = true;};
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

signals:
    void opacity_change();
    void click_event(QWidget *, bool is_show);
    void edit_event(QWidget *);
    void delete_event(QWidget *);
    void size_change();
};

#endif // RECTITEM_H
