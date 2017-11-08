#include "qcoolline.h"
#include <QDebug>
#include <QMouseEvent>

QCoolLine::QCoolLine()
{
    scene = new QGraphicsScene();

    size_t sceneX_sz = 500;
    size_t sceneY_sz = 500;

    scene->setSceneRect(0, 0, sceneX_sz, sceneY_sz);
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(sceneX_sz, sceneY_sz);

    scene->addText("QCoolLine");

    this->mouse_es = set_first_point;
}


void QCoolLine::mousePressEvent(QMouseEvent *mouse_event)
{
    qDebug() << mouse_event->pos();

    switch (mouse_es) {
    case set_first_point:
        scene->clear();
        scene->addEllipse(mouse_event->x(), mouse_event->y(), 1, 1, QPen());
        point1 = mouse_event->pos();
        mouse_es = set_second_point;
        break;

    case set_second_point:
        // This piece of code will help me determine the presence of elements on the scene
        qDebug() << "There are" << items(mouse_event->pos()).size() << "items at position" << mapToScene(mouse_event->pos());

        scene->addEllipse(mouse_event->x(), mouse_event->y(), 1, 1, QPen());
        point2 = mouse_event->pos();
        line.setPoints(point1, point2);
        scene->addLine(line, QPen());
        mouse_es = set_first_point;
        break;
#if 0
    case delete_line:
        qDebug() << "delete_line";
        this->mouse_es = set_first_point;
        break;
#endif
    }
}

