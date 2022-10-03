#ifndef AICON_H
#define AICON_H

#include<QLabel>
#include <QPixmap>
#include <QTransform>
#include <QQuickWidget>
#include <memory.h>
using std::shared_ptr;


class AIcon : public QLabel
{
    Q_OBJECT
    Q_PROPERTY(double rotate_angle READ get_rotation WRITE set_rotation)
public:
    AIcon(const QString &url, const int &width = 26, const int &height = 26, bool is_animate=true);
protected:
    double get_rotation() {return rotation;}
    void set_rotation(double n_r) {rotation = n_r; update();}
private:
    double rotation = 0;
    shared_ptr<QPropertyAnimation> animation = nullptr;
    QColor normal_color = QColor(0,0,0,0);
    QColor *bg_color = nullptr;
    QColor hover_color = QColor(240, 240, 240, 200);
    int radius = 5;
    float size_rate = 1;
    shared_ptr<QPixmap> pic = nullptr;

    void paintEvent(QPaintEvent* event) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
   signals:
    void click();

};

#endif // AICON_H
