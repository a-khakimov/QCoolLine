#ifndef QCOOLLINE_H
#define QCOOLLINE_H

#include <QObject>
#include <QCoreApplication>
#include <QGraphicsProxyWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDebug>
#include <QMouseEvent>
#include <QDateTime>

#include <QPushButton>
#include <QSpinBox>
#include <QLabel>

#include "leealgorythm.h"

enum mouse_event_state {
    set_first_point = 0,
    set_second_point,
    delete_line
};

class QCoolLine : public QGraphicsView
{
    Q_OBJECT

public:
    QCoolLine();
    ~QCoolLine();
    QGraphicsScene *scene;

private:
    mouse_event_state mouse_es;
    QPoint point1, point2;
    QLine line;

    QPushButton *btnuser;
    QSpinBox *boxQuantity, *boxSize, *boardSizeX, *boardSizeY;
    QLabel *boxQuantityLabel, *boxSizeLabel, *boardSizeXLabel, *boardSizeYLabel;

    LeeAlgorythm *leeAlg;
    QVector<QVector<int>> grid;

    size_t sceneX_sz = 500;
    size_t sceneY_sz = 500;
    size_t box_quantity = 100;
    size_t box_size = 30;

    void setWidgets();
    void sceneInit(const size_t &szX, const size_t &szY);
    void setRects(const size_t &quantity, const size_t &box_size);

public slots:
    void mousePressEvent(QMouseEvent *mouse_event);
    void buttonPressHandle();
};



#endif // QCOOLLINE_H
