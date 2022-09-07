#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "Base_Matrix.h"

// Vector is a sub class of Base_Matrix that has almost no additional functionalities
// Vector is basically a matrice that has one dimension equal to 1, and it is being checked so that the Vector has one dimension equal to 1

// Both Matrice and Vector classes are provided with copy and move constructor and assignment operators for copying Base_Matrix objects
// this solves the problem of assigning results of operations on Matrices and Vectors to instances of these classes
// this solution allowed me to resign from making the Base_Matrix an abstract class

class Vector : public Base_Matrix{
public:
// ========================================================================================================================================== constructors and destructor
    Vector(size_t columns = 1, size_t rows = 1, data_type init_value = 0); // default constructor
    Vector(const std::initializer_list<Base_Vector> &init_list); // initializer list constructor
    Vector(const Vector &source); // copy constructor
    Vector(Vector &&source); // move contructor,  moves Base_Matrix object
    virtual ~Vector();
    
    Vector(const Base_Matrix &source); // copy constructor, copies from Base_Matrix
    Vector(Base_Matrix &&source); // move contructor, moves Base_Matrix object
    
// ========================================================================================================================================== values insertion methods
    virtual void insert_row(const Base_Vector &row, size_t pos); // insert row
    virtual void delete_row(size_t pos); // delete row
    
    virtual void insert_column(const Base_Vector &column, size_t pos); // insert column
    virtual void delete_column(size_t pos); // delete column

// ========================================================================================================================================== operators
    virtual Vector& operator=(const Base_Matrix &source); // copy assignment, copies from Base_Matrix
    virtual Vector& operator=(Base_Matrix &&source); // move assignment,  moves Base_Matrix object
    
//========================================================================================================================================== random generation
    static Vector generate_random(size_t length, data_type upper_limit = 10, data_type lower_limit = -10, data_type precission = 0.1); // random Vector of given length generator

private:
// ========================================================================================================================================== validation methods
    void validate_vector_size() const; // this method checks whether at least one dimension is equal to 1
};

#endif // _VECTOR_H_
