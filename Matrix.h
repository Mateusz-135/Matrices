#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "Base_Matrix.h"

// Matrix is a sub class of Base_Class, that provides functionalities for Matrixs that are supposed to have both dimensions bigger than 1 (Matrix can be used as a "Vector", withou being a Vector)
// Matrix provides all the funtionalities that would be impossible for the 1 dimensional Vector (for example Matrix inversion)

// Both Matrix and Vector classes are provided with copy and move constructor and assignment operators for copying Base_Matrix objects
// this solves the problem of assigning results of operations on Matrices and Vectors to instances of these classes
// this solution allowed me to resign from making the Base_Matrix an abstract class

class Matrix : public Base_Matrix{  
public:
// ========================================================================================================================================== constructors and destructor
    Matrix(size_t columns = 1, size_t rows = 1, data_type init_value = 0); // default constructor
    Matrix(const std::initializer_list<Base_Vector> &init_list); // initializer list constructor
    Matrix(const Matrix &source); // copy constructor
    Matrix(Matrix &&source); // move contructor
    virtual ~Matrix();
    
    Matrix(const Base_Matrix &source); // copy constructor, copies from Base_Matrix
    Matrix(Base_Matrix &&source); // move contructor, moves Base_Matrix object
    
// ========================================================================================================================================== operators
    virtual Matrix& operator=(const Base_Matrix &source); // copy assignment, copies from Base_Matrix
    virtual Matrix& operator=(Base_Matrix &&source); // move assignment, moves Base_Matrix object

// ========================================================================================================================================== other mathematical operations
    static Matrix identity_matrix(size_t n); // creates an identity matrix of size n (square matrix with ones at the main diagonal) (static function)
    virtual Matrix invert() const; // matrix inversion using Gauss elimination algorithm
    static std::pair<Matrix, Matrix> LU_decomposition(const Matrix &matrix); // returns the lower and upper matrix from the given argument
    data_type determinant() const; // returns the determinant value, calculated using LU decopmposition
    
// ========================================================================================================================================== random generation
    static Matrix generate_random(size_t columns, size_t rows, data_type lower_limit = -10, data_type upper_limit = 10, data_type precission = 0.1); // random matrix of given size generator
};

#endif // _MATRIX_H_
