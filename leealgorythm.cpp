#include "leealgorythm.h"

void LeeAlgorythm::SetSize(size_t W, size_t H)
{
    this->W = W;
    this->H = H;

    grid.resize(W*2);
    for(size_t w = 0; w < this->H; ++w)
        grid[w].resize(H*2);

    for(size_t h = 0; h < this->H; ++h)
        for(size_t w = 0; w < this->W; ++w)
            grid[h][w] = 0;

}

int LeeAlgorythm::getGridVal(QPoint pos) {
    return grid[pos.x()][pos.y()];
}

void LeeAlgorythm::setGridVal(QPoint pos, int val) {
    this->grid[pos.x()][pos.y()] = val;
}

void LeeAlgorythm::setRect(QPoint pos, int w, int h)
{
    for(int i = pos.x(); i < pos.x() + w; ++i) {
        for(int j = pos.y(); j < pos.y() + h; ++j) {
            if(i < W && j < H) {
                QPoint p;
                p.setX(i);
                p.setY(j);
                setGridVal(p, 1);
            }
        }
    }
}

QVector<QPoint> LeeAlgorythm::GetPath(QPoint endPoint) {
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

bool LeeAlgorythm::CustomLee(QPoint beginPoint, QPoint endPoint) {
    if(getGridVal(beginPoint) || getGridVal(endPoint))
        return false;
    wave.push_back(beginPoint);
    setGridVal(beginPoint, mark);
    while(!wave.empty()) {
        for(size_t i = 0; i < 4; ++i) {
            QPoint tmpPoint;
            tmpPoint.setX(wave.front().x() + hx[i]);
            tmpPoint.setY(wave.front().y() + hy[i]);
            if(tmpPoint.x() >= 0 && tmpPoint.x() < W && tmpPoint.y() >= 0 && tmpPoint.y() < H) {
                if(getGridVal(tmpPoint) == 0 ) {
                    wave.push_back(tmpPoint);
                    setGridVal(tmpPoint, getGridVal(wave.front()) - 1);
                    if(tmpPoint.x() == endPoint.x() && tmpPoint.y() == endPoint.y()) {
                        this->path = GetPath(tmpPoint);
                        wave.clear();
                        return true;
                    }
                }
            }
        }
        wave.pop_front();
    }
    return false;
}
