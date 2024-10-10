#include <iostream>
using namespace std;

template <class T>
class Matrix
{
    template <class U>
    friend ostream &operator<<(ostream &, const Matrix<U> &);

public:
    Matrix(int r = 0, int c = 0); // constructor
    Matrix(const Matrix<T> &m);   // copy constructor
    ~Matrix() { delete[] element; }
    int Rows() const { return rows; }
    int Columns() const { return cols; }
    T &operator()(int i, int j) const;
    Matrix<T> &operator=(const Matrix<T> &m);
    Matrix<T> operator+() const;
    Matrix<T> operator+(const Matrix<T> &m) const;
    Matrix<T> operator-() const;
    Matrix<T> operator-(const Matrix<T> &m) const;
    Matrix<T> operator*(const Matrix<T> &m) const;
    Matrix<T> &operator+=(const T &x);

private:
    int rows, cols;
    T *element;
};

template <class T>
Matrix<T>::Matrix(int r, int c)
{
    rows = r;
    cols = c;
    element = new T[r * c];
}

template <class T>
Matrix<T>::Matrix(const Matrix<T> &m)
{
    rows = m.rows;
    cols = m.cols;
    element = new T[rows * cols];
    for (int i = 0; i < rows * cols; i++)
        element[i] = m.element[i];
}

template <class T>
Matrix<T> &Matrix<T>::operator=(const Matrix<T> &m)
{
    if (this != &m)
    {
        delete[] element;
        rows = m.rows;
        cols = m.cols;
        element = new T[rows * cols];
        for (int i = 0; i < rows * cols; i++)
        {
            element[i] = m.element[i];
        }
    }
    return *this;
}

template <class T>
T &Matrix<T>::operator()(int i, int j) const
{
    return element[(i - 1) * cols + j - 1];
}

template <class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &m) const
{
    Matrix<T> w(rows, cols);
    for (int i = 0; i < rows * cols; i++)
        w.element[i] = element[i] + m.element[i];
    return w;
}

template <class T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &m) const
{
    Matrix<T> w(rows, cols);
    for (int i = 0; i < rows * cols; i++)
        w.element[i] = element[i] - m.element[i];
    return w;
}

template <class T>
Matrix<T> Matrix<T>::operator-() const
{
    Matrix<T> w(rows, cols);
    for (int i = 0; i < rows * cols; i++)
        w.element[i] = -element[i];
    return w;
}

template <class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &m) const
{
    Matrix<T> w(rows, m.cols);
    int ct = 0, cm = 0, cw = 0;
    for (int i = 1; i <= rows; i++)
    {
        for (int j = 1; j <= m.cols; j++)
        {
            T sum = element[ct] * m.element[cm];
            for (int k = 2; k <= cols; k++)
            {
                ct++;
                cm += m.cols;
                sum += element[ct] * m.element[cm];
            }
            w.element[cw++] = sum;
            ct -= cols - 1;
            cm = j;
        }
        ct += cols;
        cm = 0;
    }
    return w;
}

template <class T>
Matrix<T> &Matrix<T>::operator+=(const T &x)
{
    for (int i = 0; i < rows * cols; i++)
        element[i] += x;
    return *this;
}

template <class T>
ostream &operator<<(ostream &out, const Matrix<T> &x)
{
    int k = 0;
    for (int i = 0; i < x.rows; i++)
    {
        for (int j = 0; j < x.cols; j++)
            out << x.element[k++] << "  ";
        out << endl;
    }
    return out;
}

int main()
{
    // Buat matriks pertama A dengan ukuran 2x2
    Matrix<int> A(2, 2);
    A(1, 1) = 1;
    A(1, 2) = 2;
    A(2, 1) = 3;
    A(2, 2) = 4;

    // Buat matriks kedua B dengan ukuran 2x2
    Matrix<int> B(2, 2);
    B(1, 1) = 5;
    B(1, 2) = 6;
    B(2, 1) = 7;
    B(2, 2) = 8;

    // Lakukan penjumlahan matriks A + B
    Matrix<int> C = A + B;

    // Cetak hasil penjumlahan
    cout << "Matriks A:" << endl;
    cout << A;
    cout << "Matriks B:" << endl;
    cout << B;
    cout << "Hasil penjumlahan A + B:" << endl;
    cout << C;

    return 0;
}
