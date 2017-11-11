#include <QApplication>
#include "qcoolline.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
/*
    MainWindow widget;
    widget.show();
   */

    QVector<int> v1;
    v1.resize(10);
    v1[0] = 9;
    v1[1] = 3;
    v1[2] = 5;
    v1[3] = 13;

    QVector<int> v2;
    v2.resize(5);

    v2 = v1;
    qDebug() << v1 << v2;
    v1[0] = 1;
    qDebug() << v1 << v2;

    QCoolLine coolline;

    return a.exec();
}

