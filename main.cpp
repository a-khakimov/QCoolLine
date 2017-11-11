#include <QApplication>
#include "qcoolline.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoolLine coolline;

    return a.exec();
}

