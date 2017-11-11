#include <iostream>
#include <queue>
#include <iterator>
#include <vector>

using namespace std;

const int H      = 8;          // ширина рабочего поля
const int W      = 8;          // высота рабочего поля
const int WALL   = 1;          // непроходимая ячейка
const int BLANK  = 0;          // свободная непомеченная ячейка

struct Point {
    int x;
    int y;
};

queue<Point> path;      // координаты ячеек, входящих в путь
int len;                       // длина пути
queue<Point> wave;

int grid[W][H] = { { 0, 0, 0, 0, 1, 0, 0, 0 } ,
                   { 0, 0, 1, 0, 1, 0, 1, 0 } ,
                   { 0, 0, 1, 0, 1, 0, 1, 0 } ,
                   { 0, 0, 1, 0, 1, 0, 1, 0 } ,
                   { 0, 0, 1, 0, 1, 0, 1, 0 } ,
                   { 0, 0, 1, 0, 1, 0, 1, 0 } ,
                   { 0, 0, 1, 0, 0, 0, 0, 0 } ,
                   { 0, 0, 1, 0, 0, 0, 0, 0 }
                 };                // рабочее поле

int hx[4] = {-1, +1,  0,  0 };
int hy[4] = { 0,  0, -1, +1 };
int mark = -1;

int getGridVal(Point pos)
{
    return grid[pos.x][pos.y];
}

void setGridVal(Point pos, int val)
{
    grid[pos.x][pos.y] = val;
}

vector<Point> GetPath(Point endPoint)
{
    vector<Point> path;
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

bool CustomLee(Point beginPoint, Point endPoint)
{
    if(getGridVal(beginPoint) || getGridVal(endPoint))
        return false;
    wave.push(beginPoint);
    setGridVal(beginPoint, mark);
    while(!wave.empty()) {
        for(size_t i = 0; i < 4; ++i) {
            Point tmpPoint = { wave.front().x + hx[i], wave.front().y + hy[i] };
            if(getGridVal(tmpPoint) == 0 ) {
                if(tmpPoint.x >= 0 && tmpPoint.x < W && tmpPoint.y >= 0 && tmpPoint.y < H) {
                    wave.push(tmpPoint);
                    setGridVal(tmpPoint, getGridVal(wave.front()) - 1);
                    if(tmpPoint.x == endPoint.x && tmpPoint.y == endPoint.y) {
                        cout << "x:" << tmpPoint.x << " y:" << tmpPoint.y << " V:" << getGridVal(tmpPoint) << endl;
                        vector<Point> p = GetPath(tmpPoint);
                        for(size_t i = 0; i < p.size(); ++i) {
                            cout << getGridVal(p[i]) << " ";
                        }
                        cout << endl << endl;
                        return true;
                    }
                }
            }
        }
        wave.pop();
    }
    return false;
}


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
