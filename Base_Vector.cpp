#include "Base_Vector.h"
#include <iomanip>

// ========================================================================================================================================== constructors and destructor
Base_Vector::Base_Vector(size_t length, data_type init_value) : values{nullptr}, length{length} { // default constructor
    if(length == 0){
        std::cerr << "\nBase_Vector must be at least of length 1... \n";
        throw Base_Vector();
    }
    
    values = new data_type[length];
    
    for(size_t i{} ; i < length ; i++)
        values[i] = init_value;
}

Base_Vector::Base_Vector(std::initializer_list<data_type> init_list) : Base_Vector( init_list.size() ){ // initailizer list constructor
    for(size_t i{} ; i < length ; i++)
        values[i] = *(init_list.begin() + i);
}

Base_Vector::Base_Vector(const Base_Vector &source) : values{nullptr}, length{source.length}{ // copy constructor
    values = new data_type[length];
    for(size_t i{} ; i < length ; i++)
        values[i] = source.values[i];
}

Base_Vector::Base_Vector(Base_Vector &&source) : values{source.values}, length{source.length} { // move constructor
    source.values = nullptr;
}

Base_Vector::~Base_Vector(){ // destructor
    delete[] values;
}

// ========================================================================================================================================== values insertion methods
void Base_Vector::insert_value(data_type value, size_t pos){ // insert value
    if(pos > length){
        std::cerr << "\nInvalid position during value insertion... \n";
        throw Base_Vector();
    }
    Base_Vector temp(*this); // hold current values
    delete[] values;
    values = new data_type[++length]; // increase length by 1
    for(size_t i{}, j{} ; i < length ; i++){
        if(i == pos)
            values[i] = value;
        else
            values[i] = temp.values[j++];
    }
}

void Base_Vector::delete_value(size_t pos){ // delete value
    if(pos > length - 1){
        std::cerr << "\nInvalid position during value deletion... \n";
        throw Base_Vector();
    }
    Base_Vector temp(*this); // hold current values
    delete[] values;
    values = new data_type[--length]; // decrease length by 1
    for(size_t i{}, j{} ; i < length ; j++){
        if(j != pos)
            values[i++] = temp.values[j];
    }
}

// ========================================================================================================================================== display and insertion operator
std::ostream &operator<<(std::ostream &os, const Base_Vector &base_vector){ // stream insertion operator (friend function)
    os << std::setprecision(3) << std::fixed;
    for(size_t i{} ; i < base_vector.length ; i++){
        os << ((base_vector.values[i] < 0) ? "" : " ");
        os << base_vector.values[i] << " ";
    }
    return os;
}

void Base_Vector::display() const{ // display method
    std::cout << (*this);
}

// ========================================================================================================================================== operators
Base_Vector &Base_Vector::operator=(const Base_Vector &source){ // copy assignment
    if(&source == this)
        return *this;
    delete[] values;
    length = source.length;
    values = new data_type[length];
    for(size_t i{} ; i < length ; i++)
        values[i] = source.values[i];
    return *this;
}

Base_Vector &Base_Vector::operator=(Base_Vector &&source){ // move assignment
    if(this == &source)
        return *this;
    delete[] values;
    length = source.length;
    values = source.values;
    source.values = nullptr;
    return *this;
}

data_type &Base_Vector::operator[](size_t i) const{ // subscript operator
    if(i > length){
        std::cerr << "\nIndex out of bounds... \n";
        throw Base_Vector();
    }
    return values[i];
}

Base_Vector Base_Vector::operator-() const{ // minus operator
    Base_Vector negation(*this);
    for(size_t i{} ; i < length ; i++)
        negation[i] = -negation[i];
    return negation;
}

void Base_Vector::operator+=(data_type k){ // += double
    for(size_t i{} ; i < length ; i++)
        values[i] += k;
}

void Base_Vector::operator+=(const Base_Vector &base_vector){ // += base_vector
    if(length != base_vector.length){
        std::cerr << "\nCannot add Base_Vectors of different sizes... \n";
        throw Base_Vector();
    }
    for(size_t i{} ; i < length ; i++)
        values[i] += base_vector[i];
}

Base_Vector Base_Vector::operator+(data_type k) const{ // + double
    Base_Vector sum(*this);
    sum += k;
    return sum;
}

Base_Vector Base_Vector::operator+(const Base_Vector &base_vector) const{ // + base_vector
    Base_Vector sum(*this);
    sum += base_vector;
    return sum;
}

void Base_Vector::operator-=(data_type k){ // -= double
    for(size_t i{} ; i < length ; i++)
        values[i] -= k;
}

void Base_Vector::operator-=(const Base_Vector &base_vector){ // -= base_vector
    if(length != base_vector.length){
        std::cerr << "\nCannot subtract Base_Vectors of different sizes... \n";
        throw Base_Vector();
    }
    for(size_t i{} ; i < length ; i++)
        values[i] -= base_vector[i];
}

Base_Vector Base_Vector::operator-(data_type k) const{ // - double
    Base_Vector difference(*this);
    difference -= k;
    return difference;
}

Base_Vector Base_Vector::operator-(const Base_Vector &base_vector) const{ // - base_vector
    Base_Vector difference(*this);
    difference -= base_vector;
    return difference;
}

void Base_Vector::operator*=(data_type k){ // *= double
    for(size_t i{} ; i < length ; i++)
        values[i] *= k;
}

Base_Vector Base_Vector::operator*(data_type k) const{ // * double
    Base_Vector product(*this);
    product *= k;
    return product;
}

Base_Vector operator*(data_type k, const Base_Vector &base_vector){ // double * base_vector (friend function)
    return base_vector * k;
}

void Base_Vector::operator/=(data_type k){ // /= double
    if(k == 0){
        std::cerr << "\nCannot divide by 0... \n";
        throw Base_Vector();
    }
    for(size_t i{} ; i < length ; i++)
        values[i] /= k;
}

Base_Vector Base_Vector::operator/(data_type k) const{ // / double
    Base_Vector quotient(*this);
    quotient /= k;
    return quotient;
}

// ========================================================================================================================================== other mathematical operations
Base_Vector Base_Vector::element_wise_product(const Base_Vector &left_vector, const Base_Vector &right_vector){ // hadamard product, or element wise product (static member function)
    if(left_vector.length != right_vector.length){
        std::cerr << "\nElement wise product possible only for vectors of the same size... \n";
        throw Base_Vector();
    }
    Base_Vector product{left_vector};
    for(size_t i{} ; i < left_vector.length ; i++)
        product[i] *= right_vector[i];
    return product;
}