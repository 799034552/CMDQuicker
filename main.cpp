#include "mainwindow.h"
#include <QApplication>
#include <QQuickWindow>
int main(int argc, char *argv[])
{
//    QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGL);
    setbuf(stdout, NULL);
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowFlag(Qt::FramelessWindowHint); //设置为无边框
    w.setAttribute(Qt::WA_TranslucentBackground); //没有设置背景的给他变为透明的
    w.show();
    return a.exec();
}
