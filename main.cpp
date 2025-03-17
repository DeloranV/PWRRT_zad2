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
Point firstPoint;
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
    firstPoint = points[0];
}

// Oblicza kwadrat odległości między punktami
double calculateDistanceSquared(Point c1, Point c2) {
    return (c1.x - c2.x) * (c1.x - c2.x) + (c1.y - c2.y) * (c1.y - c2.y);
}


// Kierunek obrotu do każdego z porównywanych punktów
// 0 -> Kolinearne, 1 -> Zgodny z ruchem zegara, 2 -> Przeciwny ruchowi zegara
int getTurnDirection(Point p, Point q, Point r) {
    double value = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (value == 0) return 0;
    if (value > 0) return 1;
    return 2;
}

// Klucz sortowania dla funkcji qsort - sortuje według kąta względem pierwszego punktu
int compareCoordinates(const void *c1,  const void *c2) {
    const Point *point1 = static_cast<const Point*>(c1);
    const Point *point2 = static_cast<const Point*>(c2);

    int direction = getTurnDirection(firstPoint, *point1, *point2);

    if (direction == 0) {
        if (calculateDistanceSquared(firstPoint, *point2) >= calculateDistanceSquared(firstPoint, *point1)) return -1;
        return 1;
    }
    if (direction == 2) return -1;
    return 1;
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
    qsort(&points[1], pointsElements - 1, sizeof(Point), compareCoordinates);

    for (Point p : points) {
        std::cout << p.x << ' ' << p.y << std::endl;
    }

    return 0;
}
