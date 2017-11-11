#ifndef LEEALGORYTHM_H
#define LEEALGORYTHM_H

#include <iostream>
#include <QVector>
#include <QQueue>
#include <QApplication>
#include <QPoint>

/*
struct Point {
    int x;
    int y;
};
*/
class LeeAlgorythm
{

private:
    int W;          // ������ �������� ����
    int H;          // ������ �������� ����
    const int WALL  = 1;  // ������������ ������
    const int BLANK = 0;  // ��������� ������������ ������

    QQueue<QPoint> wave;

    int hx[4] = {-1, +1,  0,  0 };
    int hy[4] = { 0,  0, -1, +1 };
    int mark = -1;

public:
    LeeAlgorythm() {}
    //~LeeAlgorythm();

    int getGridVal(QPoint pos);
    void setGridVal(QPoint pos, int val);
    void setRect(QPoint pos, int w, int h);
    void SetSize(size_t W, size_t H);

    QVector<QVector<int>> grid;
    QVector<QPoint> GetPath(QPoint endPoint);
    bool CustomLee(QPoint beginPoint, QPoint endPoint);
    QVector<QPoint> path;      // ���������� �����, �������� � ����
};

#endif // LEEALGORYTHM_H
