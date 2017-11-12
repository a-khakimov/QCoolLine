#include "leealgorythm.h"

void LeeAlgorythm::SetSize(const size_t &W, const size_t &H) {
    this->W = W;
    this->H = H;

    grid.resize(this->W);
    for(size_t w = 0; w < this->W; ++w)
        grid[w].resize(this->H);
}

LeeAlgorythm::~LeeAlgorythm() {

}

int LeeAlgorythm::getGridVal(const QPoint &pos) const {
    return grid[pos.x()][pos.y()];
}

void LeeAlgorythm::setGridVal(const QPoint &pos, const int &val) {
    this->grid[pos.x()][pos.y()] = val;
}

void LeeAlgorythm::setRect(const QPoint &pos, const int &w, const int &h) {
    for(int i = pos.x(); i < pos.x() + w; ++i) {
        for(int j = pos.y(); j < pos.y() + h; ++j) {
            if(i < W && j < H) {
                QPoint p(i, j);
                setGridVal(p, 1);
            }
        }
    }
}

QVector<QPoint> LeeAlgorythm::GetPath(const QPoint &endPoint) {
    QVector<QPoint> path;
    path.push_back(endPoint);
    int max_val = getGridVal(path.back());
    while(max_val < -1) {
        for(size_t i = 0; i < 4; ++i) {
            QPoint tmpPoint = { path.back().x() + hx[i], path.back().y() + hy[i] };
            if(tmpPoint.x() >= 0 && tmpPoint.x() < W && tmpPoint.y() >= 0 && tmpPoint.y() < H) {
                if(max_val < getGridVal(tmpPoint) && getGridVal(tmpPoint) < 0 ) {
                    max_val = getGridVal(tmpPoint);
                    path.push_back(tmpPoint);
                }
            }
        }
    }
    return path;
}

bool LeeAlgorythm::CustomLee(const QPoint &beginPoint, const QPoint &endPoint) {
    if(getGridVal(beginPoint) || getGridVal(endPoint))
        return false;
    QQueue<QPoint> wave;
    wave.push_back(beginPoint);
    setGridVal(beginPoint, mark);
    while(!wave.empty()) {
        for(size_t i = 0; i < 4; ++i) {
            QPoint tmpPoint(wave.front().x() + hx[i], wave.front().y() + hy[i]);
            if(tmpPoint.x() >= 0 && tmpPoint.x() < W && tmpPoint.y() >= 0 && tmpPoint.y() < H) {
                if(getGridVal(tmpPoint) == 0 ) {
                    wave.push_back(tmpPoint);
                    setGridVal(tmpPoint, getGridVal(wave.front()) - 1);
                    if(tmpPoint.x() == endPoint.x() && tmpPoint.y() == endPoint.y()) {
                        this->path = GetPath(tmpPoint);
                        return true;
                    }
                }
            }
        }
        wave.pop_front();
    }
    return false;
}
