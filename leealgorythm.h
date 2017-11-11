#ifndef LEEALGORYTHM_H
#define LEEALGORYTHM_H

#include <iostream>
#include <QVector>
#include <QQueue>
#include <QApplication>

struct Point {
    int x;
    int y;
};

class LeeAlgorythm
{

private:
    int H;          // ������ �������� ����
    int W;          // ������ �������� ����
    const int WALL  = 1;  // ������������ ������
    const int BLANK = 0;  // ��������� ������������ ������

    int len;                       // ����� ����
    QQueue<Point> wave;

    // ������� ����
    int **grid;

    int hx[4] = {-1, +1,  0,  0 };
    int hy[4] = { 0,  0, -1, +1 };
    int mark = -1;

    void GridInit();

public:
    LeeAlgorythm();
    LeeAlgorythm(int H, int W);
    //~LeeAlgorythm();

    int getGridVal(Point pos);
    void setGridVal(Point pos, int val);
    void setRect(Point pos, int w, int h);

    QVector<Point> GetPath(Point endPoint);
    bool CustomLee(Point beginPoint, Point endPoint);
    QVector<Point> path;      // ���������� �����, �������� � ����
};

#endif // LEEALGORYTHM_H
