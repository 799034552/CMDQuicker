//stable.h
#if defined __cplusplus
#include <iostream>
#include <vector>
#include <QApplication>
#include <QtCore>
#include <QtGui>
#include <QTimer>
#include <QThread>
#include <windows.h>
#if (QT_VERSION > QT_VERSION_CHECK(5,0,0))
#include <QtWidgets>
#endif

#define  BOOL_VERIFY(emStatus_bool,switch_bool) \
if (emStatus_bool == true){return true;}\
else{return false;}
#define  NULL_VERIFY(emStatus_null,switch_null) \
if (emStatus_null != NULL){return true;}\
else{return false;}
#define AppPath         qApp->applicationDirPath()
#define TIMEMS          qPrintable(QTime::currentTime().toString("HH:mm:ss zzz"))
#define TIME            qPrintable(QTime::currentTime().toString("HHmmss"))
#define QDATE           qPrintable(QDate::currentDate().toString("yyyy-MM-dd"))
#define QTIME           qPrintable(QTime::currentTime().toString("HH-mm-ss-zzz"))
#define DATETIME        qPrintable(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"))
#define STRDATETIME     qPrintable(QDateTime::currentDateTime().toString("yyyy-MM-dd-HH-mm-ss"))
#define STRDATETIMEMS   qPrintable(QDateTime::currentDateTime().toString("yyyy-MM-dd-HH-mm-ss-zzz"))
#pragma execution_character_set("utf-8")
#endif
