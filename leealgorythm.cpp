#include "leealgorythm.h"

LeeAlgorythm::LeeAlgorythm()
{

}

#include <iostream>

using namespace std;


const int W      = 10;          // ширина рабочего поля
const int H      = 10;         // высота рабочего поля
const int WALL   = -1;         // непроходимая ячейка
const int BLANK  = -2;         // свободная непомеченная ячейка

int px[W * H], py[W * H];      // координаты ячеек, входящих в путь
int len;                       // длина пути
int grid[H][W];                // рабочее поле

// Перед вызовом lee() массив grid заполнен значениями WALL и BLANK

bool lee(int ax, int ay, int bx, int by)   // поиск пути из ячейки (ax, ay) в ячейку (bx, by)
{
    int dx[4] = {1, 0, -1, 0};   // смещения, соответствующие соседям ячейки
    int dy[4] = {0, 1, 0, -1};   // справа, снизу, слева и сверху
    int d, x, y, k;
    bool stop;

    if (grid[ay][ax] == WALL || grid[by][bx] == WALL)
        return false;  // ячейка (ax, ay) или (bx, by) - стена

    // распространение волны
    d = 0;
    grid[ay][ax] = 0;            // стартовая ячейка помечена 0
    do {
        stop = true;               // предполагаем, что все свободные клетки уже помечены
        for ( y = 0; y < H; ++y )
            for ( x = 0; x < W; ++x )
                if ( grid[y][x] == d )                         // ячейка (x, y) помечена числом d
                {
                    for ( k = 0; k < 4; ++k )                    // проходим по всем непомеченным соседям
                    {
                        int iy=y + dy[k], ix = x + dx[k];
                        if ( iy >= 0 && iy < H && ix >= 0 && ix < W && grid[iy][ix] == BLANK )
                        {
                            stop = false;              // найдены непомеченные клетки
                            grid[iy][ix] = d + 1;      // распространяем волну
                        }
                    }
                }
        d++;
    } while ( !stop && grid[by][bx] == BLANK );

    if (grid[by][bx] == BLANK)
        return false;  // путь не найден

    // восстановление пути
    len = grid[by][bx];            // длина кратчайшего пути из (ax, ay) в (bx, by)
    x = bx;
    y = by;
    d = len;
    while ( d > 0 )
    {
        px[d] = x;
        py[d] = y;                   // записываем ячейку (x, y) в путь
        d--;
        for (k = 0; k < 4; ++k)
        {
            int iy=y + dy[k], ix = x + dx[k];
            if ( iy >= 0 && iy < H && ix >= 0 && ix < W && grid[iy][ix] == d)
            {
                x = x + dx[k];
                y = y + dy[k];           // переходим в ячейку, которая на 1 ближе к старту
                break;
            }
        }
    }
    px[0] = ax;
    py[0] = ay;                    // теперь px[0..len] и py[0..len] - координаты ячеек пути
    return true;
}
#if 0
int main(int argc, char *argv[])
{
    for(size_t i = 0; i < W; ++i)
        for(size_t j = 0; j < H; ++j)
            grid[i][j] = -2;

    for(size_t i = 0; i < W; ++i) {
        for(size_t j = 0; j < H; ++j)
            cout << grid[i][j] << " ";
        cout << endl;
    }

    for(size_t i = 0; i < W * 5; ++i)
        cout << px[i] << " ";
    cout << endl;

    for(size_t i = 0; i < W * 5; ++i)
        cout << py[i] << " ";
    cout << endl;

    lee(1, 1, 5, 4);

    for(size_t i = 0; i < W; ++i) {
        for(size_t j = 0; j < H; ++j)
            cout << grid[i][j] << " ";
        cout << endl;
    }

    for(size_t i = 0; i < W * 5; ++i)
        cout << px[i] << " ";
    cout << endl;

    for(size_t i = 0; i < W * 5; ++i)
        cout << py[i] << " ";
    cout << endl;

    return 0;
}
#endif
