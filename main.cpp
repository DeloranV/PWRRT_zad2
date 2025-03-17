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

// Szukanie pierwszego punktu
void firstCoordinate(Point points[], int pointsElements) {
    double minY = points[0].y;
    int minIndex = 0;
    for (int i = 1; i < pointsElements; i++) {
        double y = points[i].y;
        if ((y < minY) || (minY == y && points[i].x < points[minIndex].x)) {
            minY = points[i].y;
            minIndex = i;
        }
    }
    swapPoints(&points[0], &points[minIndex]);
}

int main() {
    Point points[] = {{2, 3}, {1, 0}, {1, 2}, {5, 3},
                {2.5, 2}, {-1, 2}, {4, -1}, {3, 1}};

    int pointsElements = sizeof(points) / sizeof(Point);

    for (Point p : points) {
        std::cout << p.x << ' ' << p.y << std::endl;
    }

    std::cout << std::endl;

    firstCoordinate(points, pointsElements);

    for (Point p : points) {
        std::cout << p.x << ' ' << p.y << std::endl;
    }

    return 0;
}
