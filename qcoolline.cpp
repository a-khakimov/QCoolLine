#include "qcoolline.h"
#include <QDebug>
#include <QMouseEvent>
#include <QDateTime>

QCoolLine::QCoolLine()
{
    scene = new QGraphicsScene();

    scene->setSceneRect(0, 0, sceneX_sz, sceneY_sz);
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(sceneX_sz, sceneY_sz);

    LeeAlgorythm leeAlg(this->sceneX_sz, this->sceneY_sz);
    // leeAlg = LeeAlgorythm::LeeAlgorythm(this->sceneX_sz, this->sceneY_sz);

    // scene->addText("QCoolLine");

    this->mouse_es = set_first_point;

    for(size_t i = 0; i < 500; ++i)
        for(size_t j = 0; j < 500; ++j)
            grid[i][j] = qrand() % 10;

    Point point;
    qsrand(QDateTime::currentMSecsSinceEpoch() / 1000);
    for(int i = 0; i < 400; ++i) {
        point = { qrand() % (sceneX_sz - 1), qrand() % (sceneY_sz - 1) };
        int w = (qrand() % 20) + 4;
        int h = (qrand() % 20) + 4;
        leeAlg.setRect(point, w, h);
        scene->addRect(point.x, point.y, w, h, QPen(Qt::black), QBrush(Qt::lightGray));
    }

    Point pb = {0, 0};
    Point pe = {499, 499};
    leeAlg.CustomLee(pb, pe);

    for(int i = 0; i < leeAlg.path.size(); i++)
         scene->addEllipse(leeAlg.path.at(i).x, leeAlg.path.at(i).y, 1, 1, QPen(Qt::red));
}


void QCoolLine::mousePressEvent(QMouseEvent *mouse_event)
{
    qDebug() << mouse_event->pos();

    switch (mouse_es) {
    case set_first_point:
        scene->clear();
        //scene->addEllipse(mouse_event->x(), mouse_event->y(), 1, 1, QPen());
        point1 = mouse_event->pos();
        mouse_es = set_second_point;
        break;

    case set_second_point:
        // This piece of code will help me determine the presence of elements on the scene
        qDebug() << "There are" << items(mouse_event->pos()).size() << "items at position" << mapToScene(mouse_event->pos());

        //scene->addEllipse(mouse_event->x(), mouse_event->y(), 1, 1, QPen());
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

