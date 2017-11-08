#include <QApplication>
#include "qcoolline.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoolLine coolline;
    coolline.show();

    return a.exec();
}
