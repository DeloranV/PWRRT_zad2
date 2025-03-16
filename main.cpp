#include <iostream>

struct Point {
    double x, y;
};

// Zamiana punktów w tablicy
void swapPoints(Point *c1, Point *c2) {
    Point temp = *c1;
    *c1 = *c2;
    *c2 = temp;
}

int main() {
    Point points[] = {{2, 3}, {1, 0}, {1, 2}, {5, 3},
                           {2.5, 2}, {-1, 2}, {4, -1}, {3, 1}};

    int pointsElements = sizeof(points) / sizeof(Point);

    for (Point p : points) {
        std::cout << p.x << ' ' << p.y << std::endl;
    }

    std::cout << std::endl;

    swapPoints(&points[0], &points[pointsElements - 1]);

    for (Point p : points) {
        std::cout << p.x << ' ' << p.y << std::endl;
    }

    return 0;
}
