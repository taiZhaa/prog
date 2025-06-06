#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class BasePoint {
public:
    virtual void draw() const = 0;
    virtual void erase() = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void rotate(double angle) = 0;
    virtual ~BasePoint() {}
};

class Vertex : public BasePoint {
protected:
    double x, y;

public:
    Vertex(double x = 0, double y = 0) : x(x), y(y) {}

    void draw() const override {
        cout << "Вершина в (" << x << ", " << y << ")\n";
    }

    void erase() override {
        cout << "Стираю вершины в (" << x << ", " << y << ")\n";
    }

    void move(double dx, double dy) override {
        x += dx;
        y += dy;
    }

    void rotate(double angle) override {
        double rad = angle * M_PI / 180.0;
        double newX = x * cos(rad) - y * sin(rad);
        double newY = x * sin(rad) + y * cos(rad);
        x = newX;
        y = newY;
    }

    pair<double, double> getCoords() const {
        return { x, y };
    }
};

class Shape : public BasePoint {
protected:
    vector<Vertex> vertices;

public:
    Shape(const vector<Vertex>& verts) : vertices(verts) {}

    void draw() const override {
        cout << "Рисую фигуру с вершинами:\n";
        for (const auto& v : vertices)
            v.draw();
    }

    void erase() override {
        cout << "Стираю фигуру.\n";
    }

    void move(double dx, double dy) override {
        for (auto& v : vertices)
            v.move(dx, dy);
    }

    void rotate(double angle) override {
        for (auto& v : vertices)
            v.rotate(angle);
    }
};

class Line : public Shape {
public:
    Line(Vertex v1, Vertex v2) : Shape({ v1, v2 }) {}

    void draw() const override {
        cout << "Рисую линию:\n";
        Shape::draw();
    }
};

class Rectangle : public Shape {
public:
    Rectangle(Vertex v1, Vertex v2, Vertex v3, Vertex v4)
        : Shape({ v1, v2, v3, v4 }) {
    }

    void draw() const override {
        cout << "Рисую прямоугольник:\n";
        Shape::draw();
    }
};

class Square : virtual public Rectangle {
public:
    Square(Vertex v1, Vertex v2, Vertex v3, Vertex v4)
        : Rectangle(v1, v2, v3, v4) {
    }

    void draw() const override {
        cout << "Рисую квадрат:\n";
        Shape::draw();
    }
};

class Rhombus : public Shape {
public:
    Rhombus(Vertex v1, Vertex v2, Vertex v3, Vertex v4)
        : Shape({ v1, v2, v3, v4 }) {
    }

    void draw() const override {
        cout << "Рисую ромб:\n";
        Shape::draw();
    }
};

class Parallelogram : virtual public Rectangle, public Square {
public:
    Parallelogram(Vertex v1, Vertex v2, Vertex v3, Vertex v4)
        : Rectangle(v1, v2, v3, v4), Square(v1, v2, v3, v4) {
    }

    void draw() const override {
        cout << "Рисую параллелограмм:\n";
        Shape::draw();
    }
};

int main() {
    Vertex a(0, 0), b(2, 0), c(2, 2), d(0, 2);

    Line line(a, b);
    line.draw();
    line.move(1, 1);
    line.rotate(45);
    line.erase();

    Square square(a, b, c, d);
    square.draw();

    Parallelogram p(a, b, c, d);
    p.draw();

    BasePoint* ptr = &square;
    ptr->draw();

    return 0;
}
