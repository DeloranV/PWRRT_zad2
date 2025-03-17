#include <iostream>
#include <stack>
#include <cmath>
#include <fstream>
#include <string>
#include <sstream>

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
double calculateDistance(Point c1, Point c2) {
    return sqrt((c1.x - c2.x) * (c1.x - c2.x) + (c1.y - c2.y) * (c1.y - c2.y));
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
        if (calculateDistance(firstPoint, *point2) >= calculateDistance(firstPoint, *point1)) return -1;
        return 1;
    }
    if (direction == 2) return -1;
    return 1;
}

// Zwraca drugi od końca element na stosie
Point getSecondTop(std::stack<Point> &S) {
    Point topElement = S.top();
    S.pop();
    Point secondTop = S.top();
    S.push(topElement);
    return secondTop;
}

void convexHull(Point coordinates[], int pointsElements) {
    int updatedCount = 1;
    for (int i = 1; i < pointsElements; i++) {
        while (i < pointsElements - 1 && getTurnDirection(firstPoint, coordinates[i], coordinates[i + 1]) == 0)
            i++;
        coordinates[updatedCount] = coordinates[i];
        updatedCount++;
    }

    // Nie możemy wyznaczyć mając mniej niż 3 pkt
    if (updatedCount < 3) return;

    // Wrzucamy pierwsze 3 punkty na stos
    std::stack<Point> hull;
    hull.push(coordinates[0]);
    hull.push(coordinates[1]);
    hull.push(coordinates[2]);

    // Sprawdzamy pozostałe punkty pod kątem kierunku kąta do nich, ściągamy ze stosu zgodne z ruchem zegara
    for (int i = 3; i < updatedCount; i++) {
        while (hull.size() > 1 && getTurnDirection(getSecondTop(hull), hull.top(), coordinates[i]) != 2)
            hull.pop();
        hull.push(coordinates[i]);
    }

    // Wyświelt punkty
    while (!hull.empty()) {
        Point c = hull.top();
        std::cout << c.x << " " << c.y << std::endl;
        hull.pop();
    }
}

// Wczytanie pierwszej linii z pliku - ilości punktów
bool readFirstLine(const std::string& filename, int& pointsElements) {
    std::ifstream fileInput(filename);
    if (!fileInput) {
        std::cerr << "Błąd podczas otwierania pliku!" << std::endl;
        return false;
    }
    std::string line;
    if (!std::getline(fileInput, line)) {
        std::cerr << "Plik jest pusty!" << std::endl;
        return false;
    }
    std::istringstream iss(line);
    if (!(iss >> pointsElements)) {
        std::cerr << "Błąd podczas wczytywania linii!" << std::endl;
        return false;
    }
    return true;
}

// Wczytanie pozostałych linii z pliku - punkty
int readPoints(const std::string& filename, Point points[], int maxSize) {
    std::ifstream fileInput(filename);
    if (!fileInput) {
        std::cerr << "Błąd podczas otwierania pliku!" << std::endl;
        return 0;
    }

    std::string line;
    if (!std::getline(fileInput, line)) {
        return 0;
    }

    int count = 0;
    while (std::getline(fileInput, line) && count < maxSize) {
        std::istringstream iss(line);
        if (iss >> points[count].x >> points[count].y) {
            count++;
        }
    }

    return count;
}

int main() {
    // Point points[] = {{2, 3}, {1, 0}, {1, 2}, {5, 3},
    //             {2.5, 2}, {-1, 2}, {4, -1}, {3, 1}};

    int pointsElements;
    std::string fileName;

    std::cout << "Wpisz nazwe pliku z danymi wejsciowymi" << std::endl;
    std::cin >> fileName;

    readFirstLine(fileName, pointsElements);
    Point pointsFile[pointsElements];
    readPoints("input.txt", pointsFile, pointsElements);

    std::cout << pointsElements << std::endl;

    // for (Point p : pointsFile) {
    //     std::cout << p.x << " " << p.y << std::endl;
    // }

    firstCoordinate(pointsFile, pointsElements);
    qsort(&pointsFile[1], pointsElements - 1, sizeof(Point), compareCoordinates);
    convexHull(pointsFile, pointsElements);

    // int pointsElements = sizeof(points) / sizeof(Point);
    //
    // for (Point p : points) {
    //     std::cout << p.x << ' ' << p.y << std::endl;
    // }
    //
    // std::cout << std::endl;
    //
    //
    //
    //
    // for (Point p : points) {
    //     std::cout << p.x << ' ' << p.y << std::endl;
    // }
    //
    // std::cout << std::endl;
    //
    //

    return 0;
}
