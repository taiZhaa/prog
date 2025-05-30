#include <iostream>
using namespace std;

class vect {
public:
    int dim;
    double* b;
    static int count;
    int num;

    vect(int dim = 0) : dim(dim), num(++count) {
        b = new double[dim];
        cout << "Создан объект vect #" << num << endl;
    }

    ~vect() {
        delete[] b;
        cout << "Удалён объект vect #" << num << endl;
    }

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

    vect operator*(double k) const {
        vect res(dim);
        for (int i = 0; i < dim; ++i) {
            res.b[i] = k * b[i];
        }
        cout << "Умножение vect #" << num << " на скаляр " << k << endl;
        return res;
    }
};

int vect::count = 0;

class matr {
public:
    int dim;
    double** a;
    static int count;
    int num;

    matr(int dim = 0) : dim(dim), num(++count) {
        a = new double*[dim]; // Исправлено на массив указателей
        for (int i = 0; i < dim; ++i) {
            a[i] = new double[dim]; // Выделяем память для каждой строки
        }
        cout << "Создан объект matr #" << num << endl;
    }

    ~matr() {
        for (int i = 0; i < dim; ++i) {
            delete[] a[i]; // Освобождаем каждую строку
        }
        delete[] a; // Освобождаем массив указателей
        cout << "Удалён объект matr #" << num << endl;
    }

    matr& operator=(const matr& m) {
        if (this != &m) {
            for (int i = 0; i < dim; ++i) {
                delete[] a[i]; // Освобождаем старые строки
            }
            delete[] a; // Освобождаем массив указателей

            dim = m.dim;
            a = new double*[dim]; // Выделяем память для нового массива указателей
            for (int i = 0; i < dim; ++i) {
                a[i] = new double[dim]; // Выделяем память для каждой строки
                for (int j = 0; j < dim; ++j) {
                    a[i][j] = m.a[i][j]; // Копируем данные
                }
            }
            cout << "Присвоение matr #" << num << " -> matr #" << m.num << endl;
        }
        return *this;
    }

    matr operator+(const matr& m) const {
        matr res(dim);
        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < dim; ++j) {
                res.a[i][j] = a[i][j] + m.a[i][j];
            }
        }
        cout << "Сложение matr #" << num << " + matr #" << m.num << endl;
        return res;
    }

    matr operator-(const matr& m) const {
        matr res(dim);
        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < dim; ++j) {
                res.a[i][j] = a[i][j] - m.a[i][j];
            }
        }
        cout << "Вычитание matr #" << num << " - matr #" << m.num << endl;
        return res;
    }

    matr operator-() const {
        matr res(dim);
        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < dim; ++j) {
                res.a[i][j] = -a[i][j];
            }
        }
        cout << "Отрицание matr #" << num << endl;
        return res;
    }

    double operator*(const matr& m) const {
        double res = 0;
        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < dim; ++j) {
                res += a[i][j] * m.a[i][j];
            }
        }
        cout << "Скалярное произведение matr #" << num << " * matr #" << m.num << endl;
        return res;
    }

    matr operator*(double k) const {
        matr res(dim);
        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < dim; ++j) {
                res.a[i][j] = k * a[i][j];
            }
        }
        cout << "Умножение matr #" << num << " на скаляр " << k << endl;
        return res;
    }

    vect operator*(const vect& v) const {
        vect res(dim);
        for (int i = 0; i < dim; ++i) {
            res.b[i] = 0;
            for (int j = 0; j < dim; ++j) {
                res.b[i] += a[i][j] * v.b[j];
            }
        }
        cout << "Умножение matr #" << num << " на vect #" << v.num << endl;
        return res;
    }
};

int matr::count = 0;

int main() {
    vect v1(3), v2(3);
    matr m1(3), m2(3);

    vect v3 = v1 + v2;
    vect v4 = v1 - v2;
    vect v5 = -v1;
    double dot_product_v = v1 * v2;
    vect v6 = v1 * 2.0;
    vect v7 = v1;

    matr m3 = m1 + m2;
    matr m4 = m1 - m2;
    matr m5 = -m1;
    double dot_product_m = m1 * m2;
    matr m6 = m1 * 2.0;
    matr m7 = m1;
    vect v8 = m1 * v1;

    return 0;
}
