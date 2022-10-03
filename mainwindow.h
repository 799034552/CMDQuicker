#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColor>
#include <QString>
#include <QMouseEvent>
#include <QLabel>
#include<QPoint>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <memory>
#include <QGraphicsDropShadowEffect>
#include <Vector>
//#include <QOpenGLWidget>
#include "SlidePage.h"
#include "EditPage.h"
#include "InputBox.h"
#include <string>
#include <QDebug>
#include "GridWidget.h"
#include "cmd.h"
using std::shared_ptr;
using std::pair;
using std::string;
using std::vector;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    // 常量定义
    const char *BG_COLOR = "rgb(251,251,251)";
    static constexpr int BORDER_RADIUS = 20;
    enum {M_LEFT = 1, M_TOP= 1<<1, M_BOTTOM=1<<2, M_RIGHT=1<<3, M_NONE = 0};
    // 变量定义
    shared_ptr<QPoint> is_press = nullptr;
    int mouse_state = M_NONE, last_mouse_s = M_NONE;
    QSize width_size;
    bool is_max = false;
    shared_ptr<SlidePage> about_page = nullptr;
    shared_ptr<EditPage> edit_page = nullptr;
    shared_ptr<QWidget> border = nullptr;
    QScrollArea *scroll_contain = nullptr;
    GRidWidget *contain = nullptr;
    QWidget *contain_ = nullptr;


    // 外观函数
    void Init();
    void add_wight();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event) {is_press = nullptr;}
    void max_btn_click();
    void resizeEvent(QResizeEvent *event);
    void showEvent(QShowEvent *event);

    //业务函数
    QVector<QString> name_list;
    void run_cmd(QString cmd);
    void text_change(const QString &s);
    void cmd_init();

    void item_add(vector<string> &v);
    int find_item_i(QWidget *w);
private slots:
        void item_click(QWidget* w, bool is_show);
        void item_edit(QWidget* w);
        void item_delete(QWidget* w);


};
#endif // MAINWINDOW_H
