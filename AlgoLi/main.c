#include <stdio.h>
#include <locale.h>
#include <math.h>

#define ROWS 10
#define COLS 10

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    float x;
    float y;
} Point1;

int pole[ROWS][COLS] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

int error(Point p) {
    return (p.x >= 0 && p.y >= 0 && p.y < ROWS && p.x < COLS && pole[p.x][p.y] == 0);
}

void lee(Point start, Point end) {
    float copy[ROWS][COLS];
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            copy[i][j] = -1;
        }
    }
    copy[start.x][start.y] = 0;

    Point queue[ROWS * COLS];
    int front = 0, rear = 0;
    queue[rear++] = start;

    Point1 var[] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

    while (front != rear) {
        Point current = queue[front++];

        for (int i = 0; i < 4; i++) {
            Point next = { current.x + var[i].x, current.y + var[i].y };

            float T = 1.0;
            if (i % 2 == 0) {
                T = 0.4;
            }

            if (error(next)) {
                if (copy[next.x][next.y] == -1 || copy[next.x][next.y] > copy[current.x][current.y] + T) {
                    copy[next.x][next.y] = copy[current.x][current.y] + T;
                    queue[rear++] = next;

                    if (next.x == end.x && next.y == end.y) {
                        printf("=================Ìåòêè ïîñëå ëè:=================\n");
                        for (int i = 0; i < ROWS; i++) {
                            for (int j = 0; j < COLS; j++) {
                                printf("%.1f\t", copy[i][j]);
                            }
                            printf("\n");
                        }

                        printf("Êðàò÷àéøåå ðàññòîÿíèå äî òî÷êè (%d,%d): %.1f\n", end.x, end.y, copy[end.x][end.y]);
                        return;
                    }
                }
            }
        }
    }

    printf("Ïóòü äî òî÷êè (%d,%d) íå íàéäåí\n", end.x, end.y);
}

int main() {
    setlocale(LC_ALL, "Rus");
    Point start = { 0, 0 };
    Point end = { 9, 9 };
    lee(start, end);
    return 0;
}
