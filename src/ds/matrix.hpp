#ifndef SRC_DS_MATRIX_HPP
#define SRC_DS_MATRIX_HPP

#include <algorithm>
#include <cstddef>

// See explanation for template classes and friend functions here:
// http://web.mst.edu/~nmjxv3/articles/templates.html
template <typename T>
class Matrix;

template <typename T>
bool operator==(const Matrix<T>& lhs, const Matrix<T>& rhs);


// TODO: Implement ruel of 5.
// TODO: Implement slice operator.
template <typename T>
class Matrix {
private:
    T* mat;
public:
    size_t rows;
    size_t cols;

    // Initialize matrix of row x col with indeterminate value.
    Matrix(size_t rows_, size_t cols_);
    // Initialize matrix of row x col with def value.
    Matrix(size_t rows_, size_t cols_, T def);
    // Copy constructor.
    Matrix(const Matrix<T>& other);
    // Assignment. Only valid if the two matrices have the same dimension.
    void operator=(const Matrix<T>& other);
    // Deallocate array.
    ~Matrix();
    // Get/Set element at row r, col c.
    T& operator()(size_t r, size_t c);

    friend bool operator== <T>(const Matrix<T>& lhs, const Matrix<T>& rhs);
};

template <typename T>
Matrix<T>::Matrix(size_t rows_, size_t cols_) 
    : rows(rows_)
    , cols(cols_) 
{
    mat = new T[rows * cols];
}

template <typename T>
Matrix<T>::Matrix(size_t rows_, size_t cols_, T def) 
    : Matrix(rows_, cols_) 
{
    std::fill_n(mat, rows * cols, def);
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T>& other) 
    : Matrix(other.rows, other.cols)
{
    std::copy_n(other.mat, rows * cols, mat);
}

template <typename T>
Matrix<T>::~Matrix() {
    delete[] mat;
}

template <typename T>
void Matrix<T>::operator=(const Matrix<T>& other) {
    if (rows != other.rows) throw "Matrices have diffeernt row dimensions.";
    if (cols != other.cols) throw "Matrices have different column dimensions.";

    std::copy_n(mat, rows * cols, other.mat);
}


template <typename T>
T& Matrix<T>::operator()(size_t r, size_t c) {
    // Check if in bounds (no need to check for negative since size_t is
    // unsigned).
    if (r >= rows) throw "Row index out of bounds";
    if (c >= cols) throw "Column index out of bounds";

    return mat[r * cols + c];
}

template <typename T>
bool operator==(const Matrix<T>& lhs, const Matrix<T>& rhs) {
    // Checks if the two matrices have different dimensions. If so, return false.
    if (lhs.rows != rhs.rows || lhs.cols != rhs.cols) return false;

    // Check if there's a different element. If so, return false.
    for (int i = 0; i < lhs.rows * lhs.cols; ++i)
        if (lhs.mat[i] != rhs.mat[i]) return false;

    // Otherwise, return true.
    return true;
}

#endif /* SRC_DS_MATRIX_HPP */

