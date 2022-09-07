#include "Base_Matrix.h"

// ========================================================================================================================================== constructors and destructor
Base_Matrix::Base_Matrix(size_t columns, size_t rows, data_type init_value) : rows_of_values{nullptr}, columns{columns}, rows{rows}{ // default constructor
    if(columns < 1 || rows < 1){
        std::cerr << "\nDimensions cannot be smaller than 1... \n";
        throw Base_Matrix();
    }
    rows_of_values = new Base_Vector[rows];
    for(size_t r{} ; r < rows ; r++)
        rows_of_values[r] = Base_Vector(columns, init_value);
}

Base_Matrix::Base_Matrix(const std::initializer_list<Base_Vector> &init_list) : Base_Matrix(init_list.begin()[0].get_length(), init_list.size()){ // initializer list constructor
    for(const auto &vec : init_list){
        if(vec.get_length() != columns){
            std::cerr << "\nLengths of the initializer lists vectors are not equal... \n";
            throw Base_Matrix();
        }
    }
    for(size_t r{} ; r < rows ; r++)
        rows_of_values[r] = init_list.begin()[r];
}

Base_Matrix::Base_Matrix(const Base_Matrix &source) : Base_Matrix(source.columns, source.rows){ // copy constructor
    for(size_t r{} ; r < rows ; r++)
        rows_of_values[r] = source.rows_of_values[r];
}

Base_Matrix::Base_Matrix(Base_Matrix &&source) : rows_of_values{source.rows_of_values}, columns{source.columns}, rows{source.rows}{ // move contructor
    source.rows_of_values = nullptr;
}

Base_Matrix::~Base_Matrix(){
    delete[] rows_of_values;
}

// ========================================================================================================================================== values insertion methods
void Base_Matrix::insert_row(const Base_Vector &row, size_t pos){ // insert row
    if(pos > rows){
        std::cerr << "\nInvalid position during row insertion... \n";
        throw Base_Matrix();
    }
    else if(row.get_length() != columns){
        std::cerr << "\nRow must be the same length as the number of columns for insertion to succedd... \n";
        throw Base_Matrix();
    }
    Base_Matrix temp(*this);
    delete[] rows_of_values;
    rows_of_values = new Base_Vector[++rows]; // increase number of rows
    for(size_t r{}, i{}; r < rows ; r++){
        if(r != pos)
            rows_of_values[r] = temp[i++];
        else
            rows_of_values[r] = row;
    }
}

void Base_Matrix::delete_row(size_t pos){ // delete row
    if(pos > rows - 1){
        std::cerr << "\nInvalid position during row deletion... \n";
        throw Base_Matrix();
    }
    Base_Matrix temp(*this);
    delete[] rows_of_values;
    rows_of_values = new Base_Vector[--rows]; // decrease number of rows
    for(size_t r{}, i{}; r < rows ; i++){
        if(i != pos)
            rows_of_values[r++] = temp[i];
    }
}

void Base_Matrix::insert_column(const Base_Vector &column, size_t pos){ // insert column
    if(pos > columns){
        std::cerr << "\nInvalid position during column insertion... \n";
        throw Base_Matrix();
    }
    else if(column.get_length() != rows){
        std::cerr << "\nColumn must be the same length as the number of rows for insertion to succedd... \n";
        throw Base_Matrix();
    }
    
    columns++; // increase number of columns
    
    for(size_t r{} ; r < rows ; r++){
        rows_of_values[r].insert_value(column[r], pos);
    }
}

void Base_Matrix::delete_column(size_t pos){ // delete column
    if(pos > columns - 1){
        std::cerr << "\nInvalid position during column deletion... \n";
        throw Base_Matrix();
    }
    
    columns--; // decrease number of columns
    
    for(size_t r{} ; r < rows ; r++){
        rows_of_values[r].delete_value(pos);
    }
}

// ========================================================================================================================================== display method and insertion operator
std::ostream &operator<<(std::ostream &os, const Base_Matrix &base_matrix){ // stream insertion operator (friend function)
    for(size_t r{} ; r < base_matrix.rows ; r++)
        os << base_matrix.rows_of_values[r] << std::endl;
    return os;
}

void Base_Matrix::display() const{ // display method
    std::cout << *this;
}

// ========================================================================================================================================== operators
Base_Matrix &Base_Matrix::operator=(const Base_Matrix &source){ // copy assignment
    if(&source == this)
        return *this;
    delete[] rows_of_values;
    columns = source.columns;
    rows = source.rows;
    rows_of_values = new Base_Vector[rows];
    for(size_t r{} ; r < rows ; r++)
        rows_of_values[r] = source.rows_of_values[r];
    return *this;
}

Base_Matrix &Base_Matrix::operator=(Base_Matrix &&source){ // move assignment
    if(&source == this)
        return *this;
    delete[] rows_of_values;
    columns = source.columns;
    rows = source.rows;
    rows_of_values = source.rows_of_values;
    source.rows_of_values = nullptr;
    return *this;
}

Base_Vector &Base_Matrix::operator[](size_t r) const{ // subscript operator
    if(r > rows){
        std::cerr << "\nIndex out of bounds... \n";
        throw Base_Matrix();
    }
    return rows_of_values[r];
}

Base_Matrix Base_Matrix::operator-() const{ // minus operator
    Base_Matrix negation(*this);
    for(size_t r{} ; r < rows ; r++)
        negation[r] = -negation[r];
    return negation;
}

void Base_Matrix::operator+=(data_type k){ // += double
    for(size_t r{} ; r < rows ; r++)
        rows_of_values[r] += k;
}

void Base_Matrix::operator+=(const Base_Matrix &base_matrix){ // += base_matrix
    if(rows != base_matrix.rows || columns != base_matrix.columns){
        std::cerr << "\nCannot add Base_Matrixs of different sizes... \n";
        throw Base_Matrix();
    }
    for(size_t r{} ; r < rows ; r++)
        rows_of_values[r] += base_matrix[r];
}

Base_Matrix Base_Matrix::operator+(data_type k) const{ // + double
    Base_Matrix sum(*this);
    sum += k;
    return sum;
}

Base_Matrix Base_Matrix::operator+(const Base_Matrix &base_matrix) const{ // + base_matrix
    Base_Matrix sum(*this);
    sum += base_matrix;
    return sum;
}

void Base_Matrix::operator-=(data_type k){ // -= double
    for(size_t r{} ; r < rows ; r++)
        rows_of_values[r] -= k;
}

void Base_Matrix::operator-=(const Base_Matrix &base_matrix){ // -= base_matrix
    if(rows != base_matrix.rows || columns != base_matrix.columns){
        std::cerr << "\nCannot subtract Base_Matrixs of different sizes... \n";
        throw Base_Matrix();
    }
    for(size_t r{} ; r < rows ; r++)
        rows_of_values[r] -= base_matrix[r];
}
    
Base_Matrix Base_Matrix::operator-(data_type k) const{ // - double
    Base_Matrix sum(*this);
    sum -= k;
    return sum;
}
    
Base_Matrix Base_Matrix::operator-(const Base_Matrix &base_matrix) const{ // - base_matrix
    Base_Matrix sum(*this);
    sum -= base_matrix;
    return sum;
}

void Base_Matrix::operator*=(data_type k){ // *= double
    for(size_t r{} ; r < rows ; r++)
        rows_of_values[r] *= k;
}

Base_Matrix Base_Matrix::operator*(data_type k) const{ // * double
    Base_Matrix sum(*this);
    sum *= k;
    return sum;
}

Base_Matrix operator*(data_type k, const Base_Matrix &base_matrix){ // double * base_matrix (friend function)
    return base_matrix * k;
}

Base_Matrix operator*(const Base_Matrix &left_matrice, const Base_Matrix &right_matrice){ // base_matrix * base_matrix, matrix multiplication (friend function)
    if(left_matrice.columns != right_matrice.rows){
        std::cerr << "\nLeft side's amount of columns is not equal to right side's amount of rows... \n"; 
        throw Base_Matrix();
    }
    size_t result_columns = ( (left_matrice.columns < right_matrice.columns) ? left_matrice.columns : right_matrice.columns);
    size_t result_rows = ( (left_matrice.rows < right_matrice.rows) ? left_matrice.rows : right_matrice.rows);
    size_t iterations_per_element = left_matrice.columns; // iterations per result matrice element
    
    Base_Matrix product(result_columns, result_rows, 0);
    
    for(size_t i{} ; i < result_rows ; i++)
        for(size_t j{} ; j < result_columns ; j++)
            for(size_t k{} ; k < iterations_per_element ; k++)
                product[i][j] += left_matrice[i][k] * right_matrice[k][j];
    return product;
}

void Base_Matrix::operator*=(const Base_Matrix &base_matrix){ // *= base_matrix, matrix multiplication
    (*this) = (*this) * base_matrix;
}

void Base_Matrix::operator/=(data_type k){ // /= double
    if(k == 0){
        std::cerr << "\nCannot divide by 0... \n"; 
        throw Base_Matrix();
    }
    for(size_t r{} ; r < rows ; r++)
        rows_of_values[r] /= k;
}

Base_Matrix Base_Matrix::operator/(data_type k) const{ // / double
    Base_Matrix sum(*this);
    sum /= k;
    return sum;
}

// ========================================================================================================================================== other mathematical operations
Base_Matrix Base_Matrix::element_wise_product(const Base_Matrix &left_vector, const Base_Matrix &right_vector){ // hadamard product, or element wise product (static function)
    Base_Matrix product(left_vector);
    for(size_t r{} ; r < left_vector.rows ; r++)
        product[r] = Base_Vector::element_wise_product(left_vector[r], right_vector[r]);
    return product;
}

Base_Matrix Base_Matrix::transpone() const{ // transpone
    Base_Matrix transponed(rows, columns, 0); // rows and columns are switched
    for(size_t r{} ; r < rows ; r++)
        for(size_t c{} ; c < columns ; c++)
            transponed[c][r] = rows_of_values[r][c];
    return transponed;
}