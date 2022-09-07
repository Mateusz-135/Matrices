#ifndef _BASE_VECTOR_H_
#define _BASE_VECTOR_H_

// Base_Vector is the base class of the Base_Matrice class
// Base_Vector holds the pointer to the sequence of double values and provides all necessary functionalities for the vectors

#include <iostream>

typedef double data_type;

class Base_Vector
{
protected:
    data_type* values;
    size_t length;
    
public:
// ========================================================================================================================================== constructors and destructor
    Base_Vector(size_t length = 1, data_type init_value = 0); // default constructor
    Base_Vector(std::initializer_list<data_type> init_list); // initailizer list constructor
    Base_Vector(const Base_Vector &source); // copy constructor
    Base_Vector(Base_Vector &&source); // move constructor
    ~Base_Vector(); // destructor
    
// ========================================================================================================================================== getters and setters
    size_t get_length() const { return length; } // get length
    
// ========================================================================================================================================== values insertion methods
    void insert_value(data_type value, size_t pos); // insert value
    void delete_value(size_t pos); // delete value
    
// ========================================================================================================================================== display method and insertion operator
    friend std::ostream &operator<<(std::ostream &os, const Base_Vector &base_vector); // stream insertion operator (friend function)
    void display() const; // display method

// ========================================================================================================================================== operators
    Base_Vector &operator=(const Base_Vector &source); // copy assignment
    Base_Vector &operator=(Base_Vector &&source); // move assignment
    
    data_type &operator[](size_t i) const; // subscript operator
    Base_Vector operator-() const; // minus operator

    void operator+=(data_type k); // += double
    void operator+=(const Base_Vector &base_vector); // += base_vector
    Base_Vector operator+(data_type k) const; // + double
    Base_Vector operator+(const Base_Vector &base_vector) const; // + base_vector
    
    void operator-=(data_type k); // -= double
    void operator-=(const Base_Vector &base_vector); // -= base_vector
    Base_Vector operator-(data_type k) const; // - double
    Base_Vector operator-(const Base_Vector &base_vector) const; // - base_vector
    
    void operator*=(data_type k); // *= double
    Base_Vector operator*(data_type k) const; // * double
    friend Base_Vector operator*(data_type k, const Base_Vector &base_vector); // double * base_vector (friend function)
    
    void operator/=(data_type k); // /= double
    Base_Vector operator/(data_type k) const; // / double
    
// ========================================================================================================================================== other mathematical operations
    static Base_Vector element_wise_product(const Base_Vector &left_vector, const Base_Vector &right_vector); // hadamard product, or element wise product (static function)
};

#endif // _BASE_VECTOR_H_
