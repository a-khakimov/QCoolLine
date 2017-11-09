#include "leealgorythm.h"

LeeAlgorythm::LeeAlgorythm()
{

}

#include <iostream>

using namespace std;


const int W      = 10;          // ������ �������� ����
const int H      = 10;         // ������ �������� ����
const int WALL   = -1;         // ������������ ������
const int BLANK  = -2;         // ��������� ������������ ������

int px[W * H], py[W * H];      // ���������� �����, �������� � ����
int len;                       // ����� ����
int grid[H][W];                // ������� ����

// ����� ������� lee() ������ grid �������� ���������� WALL � BLANK

bool lee(int ax, int ay, int bx, int by)   // ����� ���� �� ������ (ax, ay) � ������ (bx, by)
{
    int dx[4] = {1, 0, -1, 0};   // ��������, ��������������� ������� ������
    int dy[4] = {0, 1, 0, -1};   // ������, �����, ����� � ������
    int d, x, y, k;
    bool stop;

    if (grid[ay][ax] == WALL || grid[by][bx] == WALL)
        return false;  // ������ (ax, ay) ��� (bx, by) - �����

    // ��������������� �����
    d = 0;
    grid[ay][ax] = 0;            // ��������� ������ �������� 0
    do {
        stop = true;               // ������������, ��� ��� ��������� ������ ��� ��������
        for ( y = 0; y < H; ++y )
            for ( x = 0; x < W; ++x )
                if ( grid[y][x] == d )                         // ������ (x, y) �������� ������ d
                {
                    for ( k = 0; k < 4; ++k )                    // �������� �� ���� ������������ �������
                    {
                        int iy=y + dy[k], ix = x + dx[k];
                        if ( iy >= 0 && iy < H && ix >= 0 && ix < W && grid[iy][ix] == BLANK )
                        {
                            stop = false;              // ������� ������������ ������
                            grid[iy][ix] = d + 1;      // �������������� �����
                        }
                    }
                }
        d++;
    } while ( !stop && grid[by][bx] == BLANK );

    if (grid[by][bx] == BLANK)
        return false;  // ���� �� ������

    // �������������� ����
    len = grid[by][bx];            // ����� ����������� ���� �� (ax, ay) � (bx, by)
    x = bx;
    y = by;
    d = len;
    while ( d > 0 )
    {
        px[d] = x;
        py[d] = y;                   // ���������� ������ (x, y) � ����
        d--;
        for (k = 0; k < 4; ++k)
        {
            int iy=y + dy[k], ix = x + dx[k];
            if ( iy >= 0 && iy < H && ix >= 0 && ix < W && grid[iy][ix] == d)
            {
                x = x + dx[k];
                y = y + dy[k];           // ��������� � ������, ������� �� 1 ����� � ������
                break;
            }
        }
    }
    px[0] = ax;
    py[0] = ay;                    // ������ px[0..len] � py[0..len] - ���������� ����� ����
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
