#include <iostream>
#include <queue>

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

int grid[W][H] = { { 0, 0, 1, 0, 0, 0, 0, 0 } ,
                   { 0, 0, 1, 0, 1, 0, 0, 0 } ,
                   { 0, 0, 1, 0, 1, 0, 0, 0 } ,
                   { 0, 0, 1, 0, 1, 0, 0, 0 } ,
                   { 0, 0, 0, 0, 1, 0, 0, 0 } ,
                   { 0, 0, 0, 0, 1, 0, 0, 0 } ,
                   { 0, 0, 0, 0, 1, 0, 0, 0 } ,
                   { 0, 0, 0, 0, 1, 0, 0, 0 }
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


Point littleWave( Point pos )
{
    for(int i = 0; i < 4; ++i)
    {
        Point tmpPoint = { pos.x + hx[i], pos.y + hy[i] };
        if(getGridVal(tmpPoint) == 0 &&
                pos.x + hx[i] >= 0 &&
                pos.x + hy[i] < W &&
                pos.y + hy[i] >= 0 &&
                pos.y + hy[i] < H)
        {
            wave.push(tmpPoint);
            setGridVal(tmpPoint, getGridVal(pos) - 1);
        }
    }
}

bool CustomLee(Point beginPoint, Point endPoint)
{
    if(getGridVal(beginPoint) || getGridVal(endPoint))
        return false;

    wave.push(beginPoint);


    setGridVal(beginPoint, mark);

    cout << (wave.front()).x << endl;
    cout << (wave.front()).y << endl;

    bool stop = true;
    while(stop)
    {
        for(int i = 0; i < 4; ++i)
        {
            Point tmpPoint = { (wave.front()).x + hx[i], (wave.front()).y + hy[i] };
            if(tmpPoint.x == endPoint.x && tmpPoint.y == endPoint.y)
                stop = false;
            if(getGridVal(tmpPoint) == 0 &&
                    (wave.front()).x + hx[i] >= 0 &&
                    (wave.front()).x + hy[i] < W &&
                    (wave.front()).y + hy[i] >= 0 &&
                    (wave.front()).y + hy[i] < H)
            {
                wave.push(tmpPoint);
                //wave.pop();
                setGridVal(tmpPoint, getGridVal((wave.front())) - 1);
                stop = true;
            }
        }
        cout << wave.empty() << endl;
    }
    cout << "CustomLee" << endl;
}


int main()
{
    Point p1 = {0, 0};
    Point p2 = {2, 3};
    CustomLee(p1, p2);

    for(size_t i = 0; i < W; ++i) {
        for(size_t j = 0; j < H; ++j)
            cout << grid[i][j] << " ";
        cout << endl;
    }

    return 0;
}
