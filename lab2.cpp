#include <iostream>
using namespace std;

class vect {
public:
    int dim;
    double* b;
    static int count;
    int num;

    // Конструктор
    vect(int dim = 0) : dim(dim), num(++count) {
        b = new double[dim];
        cout << "Создан объект vect #" << num << endl;
    }

    // Деструктор
    ~vect() {
        delete[] b;
        cout << "Удалён объект vect #" << num << endl;
    }

    // Оператор присваивания
    vect& operator=(const vect& v) {
        if (this != &v) {
            delete[] b;
            dim = v.dim;
            b = new double[dim];
            for (int i = 0; i < dim; ++i) {
                b[i] = v.b[i];
            }
            cout << "Присвоение vect #" << num << " -> vect #" << v.num << endl;
        }
        return *this;
    }

    // Прочие операторы
    vect operator+(const vect& v) const {
        vect res(dim);
        for (int i = 0; i < dim; ++i) {
            res.b[i] = b[i] + v.b[i];
        }
        cout << "Сложение vect #" << num << " + vect #" << v.num << endl;
        return res;
    }

    vect operator-(const vect& v) const {
        vect res(dim);
        for (int i = 0; i < dim; ++i) {
            res.b[i] = b[i] - v.b[i];
        }
        cout << "Вычитание vect #" << num << " - vect #" << v.num << endl;
        return res;
    }

    vect operator-() const {
        vect res(dim);
        for (int i = 0; i < dim; ++i) {
            res.b[i] = -b[i];
        }
        cout << "Отрицание vect #" << num << endl;
        return res;
    }

    double operator*(const vect& v) const {
        double res = 0;
        for (int i = 0; i < dim; ++i) {
            res += b[i] * v.b[i];
        }
        cout << "Скалярное произведение vect #" << num << " * vect #" << v.num << endl;
        return res;
    }
};

int vect::count = 0;

class matr {
public:
    int dim;
    double* a;
    static int count;
    int num;

    // Конструктор
    matr(int dim = 0) : dim(dim), num(++count) {
        a = new double[dim * dim];
        cout << "Создан объект matr #" << num << endl;
    }

    // Деструктор
    ~matr() {
        delete[] a;
        cout << "Удалён объект matr #" << num << endl;
    }

    // Оператор присваивания
    matr& operator=(const matr& m) {
        if (this != &m) {
            delete[] a;
            dim = m.dim;
            a = new double[dim * dim];
            for (int i = 0; i < dim * dim; ++i) {
                a[i] = m.a[i];
            }
            cout << "Присвоение matr #" << num << " -> matr #" << m.num << endl;
        }
        return *this;
    }

    // Прочие операторы (пример для сложения)
    matr operator+(const matr& m) const {
        matr res(dim);
        for (int i = 0; i < dim * dim; ++i) {
            res.a[i] = a[i] + m.a[i];
        }
        cout << "Сложение matr #" << num << " + matr #" << m.num << endl;
        return res;
    }
};

int matr::count = 0;

int main() {
    vect v1(3), v2(3);
    matr m1(3), m2(3);

    vect v3 = v1 + v2;
    matr m3 = m1 + m2;

    return 0;
}
