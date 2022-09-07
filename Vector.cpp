#include "Vector.h"
#include <time.h>
#include <cmath>

// ========================================================================================================================================== constructors and destructor
Vector::Vector(size_t columns, size_t rows, data_type init_value) : Base_Matrix(columns, rows, init_value){ // default constructor
    validate_vector_size();
}

Vector::Vector(const std::initializer_list<Base_Vector> &init_list) : Base_Matrix(init_list){ // initializer list constructor
    validate_vector_size();
}

Vector::Vector(const Vector &source) : Base_Matrix(source){ // copy constructor
    validate_vector_size();
}

Vector::Vector(Vector &&source) : Base_Matrix(source){ // move contructor
    validate_vector_size();
}

Vector::~Vector(){
}

Vector::Vector(const Base_Matrix &source) : Base_Matrix(source){ // copy constructor, copies from Base_Matrix
}

Vector::Vector(Base_Matrix &&source) : Base_Matrix(source){ // move contructor, moves Base_Matrix object
}

// ========================================================================================================================================== values insertion methods
void Vector::insert_row(const Base_Vector &row, size_t pos){ // insert row
    Base_Matrix::insert_row(row, pos);
    validate_vector_size();
}

void Vector::delete_row(size_t pos){ // delete row
    Base_Matrix::delete_row(pos);
    validate_vector_size();
}

void Vector::insert_column(const Base_Vector &column, size_t pos){ // insert column
    Base_Matrix::insert_column(column, pos);
    validate_vector_size();
}

void Vector::delete_column(size_t pos){ // delete column
    Base_Matrix::delete_column(pos);
    validate_vector_size();
}

// ========================================================================================================================================== operators
Vector& Vector::operator=(const Base_Matrix &source){ // copy assignment, copies from Base_Matrix
    if(this == &source)
        return *this;
    rows = source.get_rows();
    columns = source.get_columns();
    
    validate_vector_size(); // check whether the copied Matrice is a vector, before messing with the pointers and data
    
    delete[] rows_of_values;
    rows_of_values = new Base_Vector[rows];
    for(size_t r{} ; r < rows ; r++)
        rows_of_values[r] = source[r];
    return *this;
}

Vector& Vector::operator=(Base_Matrix &&source){ // move assignment,  moves Base_Matrix object
    if(this == &source)
        return *this;
    rows = source.get_rows();
    columns = source.get_columns();
    
    validate_vector_size(); // check whether the moved Matrice is a vector, before messing with the pointers and data
    
    delete[] rows_of_values;
    rows_of_values = source.get_ptr();
    source.set_ptr(nullptr);
    return *this;
}

//========================================================================================================================================== random generation
Vector Vector::generate_random(size_t length, data_type upper_limit, data_type lower_limit, data_type precission){ // random Vector of given length generator
    if(precission == 0){
        std::cerr << "\nPrecission cannot be equal to 0... \n";
        throw Vector();
    }
    
    upper_limit /= precission; // dividing by precision to achieve random fractions
    lower_limit /= precission;
    int random_remainder{static_cast<int>(std::ceil((upper_limit - lower_limit + 1)))}; // random numbers are the remainders of dividing rand() by this number
    
    if(random_remainder > static_cast<int>(RAND_MAX)){
        std::cerr << "\nRandom vector generator range is too big, ((upper_limit - lower_limit) / precission) value is too big... \n";
        throw Vector();
    }
    
    Vector random(length);
    srand(time(nullptr));
    
    for(size_t r{} ; r < random.rows ; r++)
        for(size_t c{} ; c < random.columns ; c++){
            random[r][c] = rand() % random_remainder - upper_limit; // upper_limit is subtracted to achieve negative numbers
            random[r][c] *= precission; // back to given precission
        }
    return random;
}

// ========================================================================================================================================== validation methods
void Vector::validate_vector_size() const{ // this method checks whether at least one dimension is equal to 1
    if(rows != 1 && columns != 1){
        std::cerr << "\nVector must have either 1 row or 1 column...\n";
        throw Vector();
    }
}