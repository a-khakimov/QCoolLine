#include "leealgorythm.h"

using namespace std;

LeeAlgorythm::LeeAlgorythm()
{

}

LeeAlgorythm::LeeAlgorythm(int H, int W){
    this->H = H;
    this->W = W;

    grid = new int*[H];
    for(size_t h = 0; h < this->H; ++h)
        grid[h] = new int[W];

    for(size_t h = 0; h < this->H; ++h)
        for(size_t w = 0; w < this->W; ++w)
            grid[h][w] = 0;
}

int LeeAlgorythm::getGridVal(Point pos) {
    //if(pos.x > 0 && pos.x < W)
      //  if(pos.y > 0 && pos.y < H)
            return grid[pos.x][pos.y];
}

void LeeAlgorythm::setGridVal(Point pos, int val) {
    //if(pos.x > 0 && pos.x < W)
      //  if(pos.y > 0 && pos.y < H)
            this->grid[pos.x][pos.y] = val;
}

void LeeAlgorythm::setRect(Point pos, int w, int h)
{
    for(int i = pos.x; i < pos.x + w; ++i) {
        for(int j = pos.y; j < pos.y + h; ++j) {
            if(i < W && j < H) {
                Point p = { i, j };
                setGridVal(p, 1);
            }
        }
    }
}
/*
void LeeAlgorythm::GridInit() {


}*/

QVector<Point> LeeAlgorythm::GetPath(Point endPoint) {
    QVector<Point> path;
    path.push_back(endPoint);
    int max_val = getGridVal(path.back());
    while(max_val < -1) {
        for(size_t i = 0; i < 4; ++i) {
            Point tmpPoint = { path.back().x + hx[i], path.back().y + hy[i] };
            if(tmpPoint.x >= 0 && tmpPoint.x < W && tmpPoint.y >= 0 && tmpPoint.y < H) {
                if(max_val < getGridVal(tmpPoint) && getGridVal(tmpPoint) < 0 ) {
                    max_val = getGridVal(tmpPoint);
                    path.push_back(tmpPoint);
                }
            }
        }
    }
    return path;
}

bool LeeAlgorythm::CustomLee(Point beginPoint, Point endPoint) {
    if(getGridVal(beginPoint) || getGridVal(endPoint))
        return false;
    wave.push_back(beginPoint);
    setGridVal(beginPoint, mark);
    while(!wave.empty()) {
        for(size_t i = 0; i < 4; ++i) {
            Point tmpPoint = { wave.front().x + hx[i], wave.front().y + hy[i] };
            if(tmpPoint.x >= 0 && tmpPoint.x < W && tmpPoint.y >= 0 && tmpPoint.y < H) {
                if(getGridVal(tmpPoint) == 0 ) {
                    wave.push_back(tmpPoint);
                    setGridVal(tmpPoint, getGridVal(wave.front()) - 1);
                    if(tmpPoint.x == endPoint.x && tmpPoint.y == endPoint.y) {
                        // cout << "x:" << tmpPoint.x << " y:" << tmpPoint.y << " V:" << getGridVal(tmpPoint) << endl;
                        this->path = GetPath(tmpPoint);
                        /*
                        for(size_t i = 0; i < p.size(); ++i) {
                            cout << getGridVal(p[i]) << " ";
                        }
                        cout << endl << endl;
                        */
                        return true;
                    }
                }
            }
        }
        wave.pop_front();
    }
    return false;
}

/*
int main()
{
    Point p1 = {0, 0};
    Point p2 = {7, 7};
    CustomLee(p1, p2);

    for(size_t i = 0; i < W; ++i) {
        for(size_t j = 0; j < H; ++j)
            cout << grid[i][j] << " ";
        cout << endl;
    }

    return 0;
}
*/
