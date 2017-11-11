#include "qcoolline.h"


QCoolLine::QCoolLine()
{
    sceneInit(500, 500);


    leeAlg = new LeeAlgorythm();
    leeAlg->SetSize(this->sceneX_sz, this->sceneY_sz);
    setRects(box_quantity);

    setWidgets();
    this->show();
}


void QCoolLine::sceneInit(size_t szX, size_t szY)
{
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, szX, szY + 26);
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(szX, szY + 25);

    scene->addLine(0, szY, szX, szY, QPen(Qt::black));

    this->mouse_es = set_first_point;
}

void QCoolLine::setRects(size_t quantity)
{
    // Set rects
    QPoint point;
    qsrand(QDateTime::currentMSecsSinceEpoch() / 1000);
    for(size_t i = 0; i < quantity; ++i) {
        point.setX(qrand() % (sceneX_sz - 1));
        point.setY(qrand() % (sceneY_sz - 1));
        int w = (qrand() % 20) + 4;
        int h = (qrand() % 20) + 4;
        leeAlg->setRect(point, w, h);
        scene->addRect(point.x(), point.y(), w, h, QPen(Qt::black), QBrush(Qt::lightGray));
    }

    grid.resize(leeAlg->grid.size());
    for(size_t m = 0; m < leeAlg->grid.size(); ++m)
        grid[m].resize(leeAlg->grid[m].size());

    grid = leeAlg->grid;

}

void QCoolLine::setWidgets()
{
    QGraphicsProxyWidget *proxy;
    size_t spinbox_width(60);
    size_t label_width(30);

    // Box Quantity
    boxQuantityLabel = new QLabel;
    boxQuantityLabel->setText(" Qu:");
    boxQuantityLabel->setGeometry(QRect(100, 0, label_width, 25));
    proxy = this->scene->addWidget(boxQuantityLabel);
    proxy->setPos(0, sceneY_sz);

    boxQuantity = new QSpinBox;
    boxQuantity->setMaximum(1000);
    boxQuantity->setValue(box_quantity);
    boxQuantity->setGeometry(QRect(100, 0, spinbox_width, 25));
    proxy = this->scene->addWidget(boxQuantity);
    proxy->setPos(label_width, sceneY_sz);

    // Boxs size
    boxSizeLabel = new QLabel;
    boxSizeLabel->setText(" Sz:");
    boxSizeLabel->setGeometry(QRect(100, 0, label_width, 25));
    proxy = this->scene->addWidget(boxSizeLabel);
    proxy->setPos(label_width + spinbox_width, sceneY_sz);

    boxSize = new QSpinBox;
    boxSize->setMaximum(1000);
    boxSize->setValue(box_size);
    boxSize->setGeometry(QRect(200, 0, spinbox_width, 25));
    proxy = this->scene->addWidget(boxSize);
    proxy->setPos(label_width*2 + spinbox_width, sceneY_sz);

    // Board size (X)
    boardSizeXLabel = new QLabel;
    boardSizeXLabel->setText(" Bx:");
    boardSizeXLabel->setGeometry(QRect(100, 0, label_width, 25));
    proxy = this->scene->addWidget(boardSizeXLabel);
    proxy->setPos(label_width*2 + spinbox_width*2, sceneY_sz);

    boardSizeX = new QSpinBox;
    boardSizeX->setMaximum(1000);
    boardSizeX->setMinimum(500);
    boardSizeX->setValue(sceneX_sz);
    boardSizeX->setGeometry(QRect(300, 0, spinbox_width, 25));
    proxy = this->scene->addWidget(boardSizeX);
    proxy->setPos(label_width*3 + spinbox_width*2, sceneY_sz);

    // Board size (Y)
    boardSizeYLabel = new QLabel;
    boardSizeYLabel->setText(" By:");
    boardSizeYLabel->setGeometry(QRect(100, 0, label_width, 25));
    proxy = this->scene->addWidget(boardSizeYLabel);
    proxy->setPos(label_width*3 + spinbox_width*3, sceneY_sz);

    boardSizeY = new QSpinBox;
    boardSizeY->setMaximum(1000);
    boardSizeY->setMinimum(500);
    boardSizeY->setValue(sceneY_sz);
    boardSizeY->setGeometry(QRect(300, 0, spinbox_width, 25));
    proxy = this->scene->addWidget(boardSizeY);
    proxy->setPos(label_width*4 + spinbox_width*3, sceneY_sz);

    // Button
    btnuser = new QPushButton;
    btnuser->setGeometry(QRect(0, 0, sceneX_sz - (label_width*4 + spinbox_width*4), 25));
    btnuser->setText("Generate");
    proxy = this->scene->addWidget(btnuser);
    proxy->setPos(label_width*4 + spinbox_width*4, sceneY_sz);

    connect(btnuser, SIGNAL(clicked(bool)), this, SLOT(buttonPressHandle()));
}



void QCoolLine::mousePressEvent(QMouseEvent *mouse_event)
{
    //
    QPoint p = mouse_event->pos();
    if(p.y() < sceneY_sz) {
        switch (mouse_es) {
        case set_first_point:
            point1 = p;
            mouse_es = set_second_point;
            break;

        case set_second_point:
            point2 = p;

            leeAlg->grid = grid;
            if(leeAlg->CustomLee(point1, point2))
                for(int i = 0; i < leeAlg->path.size(); i++)
                    scene->addEllipse(leeAlg->path.at(i).x(), leeAlg->path.at(i).y(), 1, 1, QPen(Qt::red));

            mouse_es = set_first_point;

            leeAlg->path.clear();
            break;


#if 0
        case delete_line:
            this->mouse_es = set_first_point;
            break;

#endif
        }
    }
}

void QCoolLine::buttonPressHandle()
{
    leeAlg = new LeeAlgorythm();
    this->sceneX_sz = boardSizeX->value();
    this->sceneY_sz = boardSizeY->value();
    sceneInit(this->sceneX_sz, this->sceneY_sz);

    leeAlg->path.clear();
    leeAlg->SetSize(this->sceneX_sz, this->sceneY_sz);

    box_quantity = boxQuantity->value();
    setRects(box_quantity);
    setWidgets();
}

