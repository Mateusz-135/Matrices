#ifndef _BASE_MATRIX_H_
#define _BASE_MATRIX_H_

// Base_Matrix holds the pointer to the sequence of Base_Vectors, as well as variables holding size information
// Base_Matrix is the class that provides a foundation of the Matrice and Vector classes
// Base_Matrix provides all the common functionalities of Matrice and Vector

#include <iostream>
#include "Base_Vector.h"

typedef double data_type;

class Base_Matrix{
protected:
    Base_Vector* rows_of_values;
    size_t columns;
    size_t rows;
    
public:
// ========================================================================================================================================== constructors and destructor
    Base_Matrix(size_t columns = 1, size_t rows = 1, data_type init_value = 0); // default constructor
    Base_Matrix(const std::initializer_list<Base_Vector> &init_list); // initializer list constructor
    Base_Matrix(const Base_Matrix &source); // copy constructor
    Base_Matrix(Base_Matrix &&source); // move contructor
    virtual ~Base_Matrix();
    
// ========================================================================================================================================== getters and setters
    virtual size_t get_columns() const{ return columns; }
    virtual size_t get_rows() const{ return rows; }
    virtual Base_Vector* get_ptr() { return rows_of_values; };
    virtual void set_ptr(Base_Vector* ptr) { rows_of_values = ptr; };
    
// ========================================================================================================================================== values insertion methods
    virtual void insert_row(const Base_Vector &row, size_t pos); // insert row
    virtual void delete_row(size_t pos); // delete row
    
    virtual void insert_column(const Base_Vector &column, size_t pos); // insert column
    virtual void delete_column(size_t pos); // delete column
    
// ========================================================================================================================================== display method and insertion operator
    friend std::ostream &operator<<(std::ostream &os, const Base_Matrix &base_matrix); // stream insertion operator (friend function)
    virtual void display() const; // display method

// ========================================================================================================================================== operators
    virtual Base_Matrix &operator=(const Base_Matrix &source); // copy assignment
    virtual Base_Matrix &operator=(Base_Matrix &&source); // move assignment
    
    virtual Base_Vector &operator[](size_t r) const; // subscript operator
    virtual Base_Matrix operator-() const; // minus operator
    
    virtual void operator+=(data_type k); // += double
    virtual void operator+=(const Base_Matrix &base_matrix); // += base_matrix
    virtual Base_Matrix operator+(data_type k) const; // + double
    virtual Base_Matrix operator+(const Base_Matrix &base_matrix) const; // + base_matrix
    
    virtual void operator-=(data_type k); // -= double
    virtual void operator-=(const Base_Matrix &base_matrix); // -= base_matrix
    virtual Base_Matrix operator-(data_type k) const; // - double
    virtual Base_Matrix operator-(const Base_Matrix &base_matrix) const; // - base_matrix

    virtual void operator*=(data_type k); // *= double
    virtual Base_Matrix operator*(data_type k) const; // * double
    friend Base_Matrix operator*(data_type k, const Base_Matrix &base_matrix); // double * base_matrix (friend function)
    friend Base_Matrix operator*(const Base_Matrix &left_matrice, const Base_Matrix &right_matrice); // base_matrix * base_matrix, matrix multiplication (friend function)
    virtual void operator*=(const Base_Matrix &base_matrix); // *= base_matrix, matrix multiplication
    
    virtual void operator/=(data_type k); // /= double
    virtual Base_Matrix operator/(data_type k) const; // / double
    
// ========================================================================================================================================== other mathematical operations
    static Base_Matrix element_wise_product(const Base_Matrix &left_vector, const Base_Matrix &right_vector); // hadamard product, or element wise product (static function)
    virtual Base_Matrix transpone() const; // transpone
};

#endif // _BASE_MATRIX_H_