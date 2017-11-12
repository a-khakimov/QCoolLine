#ifndef LEEALGORYTHM_H
#define LEEALGORYTHM_H

#include <iostream>
#include <QVector>
#include <QQueue>
#include <QApplication>
#include <QPoint>

class LeeAlgorythm
{

private:
    int W;                  // ������ �������� ����
    int H;                  // ������ �������� ����
    const int WALL  = 1;    // ������������ ������
    const int BLANK = 0;    // ��������� ������������ ������


    const int hx[4] = {-1, +1,  0,  0 };
    const int hy[4] = { 0,  0, -1, +1 };
    const int mark = -1;

public:
    LeeAlgorythm() {}
    ~LeeAlgorythm();

    int getGridVal(const QPoint &pos) const;
    void setGridVal(const QPoint &pos, const int &val);
    void setRect(const QPoint &pos, const int &w, const int &h);
    void SetSize(const size_t &W, const size_t &H);
    QVector<QPoint> GetPath(const QPoint &endPoint);
    bool CustomLee(const QPoint &, const QPoint &);

    QVector<QVector<int>> grid;
    QVector<QPoint> path;      // ���������� �����, �������� � ����
};

#endif // LEEALGORYTHM_H
