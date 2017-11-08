#ifndef QCOOLLINE_H
#define QCOOLLINE_H

#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>


enum mouse_event_state{
    set_first_point = 0,
    set_second_point,
    delete_line
};

class QCoolLine : public QGraphicsView
{
    Q_OBJECT

public:
    QCoolLine();

    QGraphicsScene *scene;

private:
    mouse_event_state mouse_es;
    QPoint point1, point2;
    QLine line;

public slots:
    void mousePressEvent(QMouseEvent *mouse_event);

};



#endif // QCOOLLINE_H
