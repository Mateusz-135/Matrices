#include "Matrix.h"
#include <time.h>
#include <array>
#include <cmath>

// ========================================================================================================================================== constructors and destructor
Matrix::Matrix(size_t columns, size_t rows, data_type init_value) : Base_Matrix(columns, rows, init_value){ // default constructor
}

Matrix::Matrix(const std::initializer_list<Base_Vector> &init_list) : Base_Matrix(init_list){ // initializer list constructor
}

Matrix::Matrix(const Matrix &source) : Base_Matrix(source){ // copy constructor
}

Matrix::Matrix(Matrix &&source) : Base_Matrix(source){ // move contructor
}

Matrix::~Matrix(){
}

Matrix::Matrix(const Base_Matrix &source) : Base_Matrix(source){ // copy constructor
}

Matrix::Matrix(Base_Matrix &&source) : Base_Matrix(source){ // move contructor
}

// ========================================================================================================================================== operators
Matrix& Matrix::operator=(const Base_Matrix &source){ // copy assignment, copies from Base_Matrix
    if(this == &source)
        return *this;
    rows = source.get_rows();
    columns = source.get_columns();
    delete[] rows_of_values;
    rows_of_values = new Base_Vector[rows];
    for(size_t r{} ; r < rows ; r++)
        rows_of_values[r] = source[r];
    return *this;
}

Matrix& Matrix::operator=(Base_Matrix &&source){ // move assignment
    if(this == &source)
        return *this;
    rows = source.get_rows();
    columns = source.get_columns();
    delete[] rows_of_values;
    rows_of_values = source.get_ptr();
    source.set_ptr(nullptr);
    return *this;
}

// ========================================================================================================================================== other mathematical operations
Matrix Matrix::identity_matrix(size_t n){
    Matrix temp(n, n, 0);
    for(size_t r{} ; r < temp.rows ; r++)
        temp[r][r] = 1;
    return temp;
}

Matrix Matrix::invert() const{ // matrix inversion using Gauss elimination algorithm
    if(columns != rows){
        std::cerr << "\nOnly square matrixs can be inverted... \n";
        throw Matrix();
    }
    if(this->determinant() == 0){
        std::cerr << "\nInverted matrix does not exist, determinant is equal to 0... \n";
        throw Matrix();
    }
    Matrix left_augmented(*this);
    Matrix right_augmented(Matrix::identity_matrix(rows));
    
    for(size_t r{} ; r < rows ; r++){
        right_augmented[r] /= left_augmented[r][r];
        left_augmented[r] /= left_augmented[r][r];
        
        for(size_t c{r + 1} ; c < rows ; c++){
            right_augmented[c] -= right_augmented[r] * left_augmented[c][r];
            left_augmented[c] -= left_augmented[r] * left_augmented[c][r];
        }
    }
    
    for(size_t r{rows - 2 + 1} ; r >= 1 ; r--){ // addition of +1 because size_t is unsigned and cannot be lower than 0
        for(size_t c{rows - 1} ; c > r - 1 ; c--){
            right_augmented[r - 1] -= right_augmented[c] * left_augmented[r - 1][c];
            left_augmented[r - 1] -= left_augmented[c] * left_augmented[r - 1][c];
        }
    }
    return right_augmented;
}

std::pair<Matrix, Matrix> Matrix::LU_decomposition(const Matrix &matrix){ // returns the lower and upper matrix from the given argument
    if(matrix.columns != matrix.rows){
        std::cerr << "\nOnly square matrixs can be LU decomposed... \n";
        throw Matrix();
    }
    
    Matrix U(matrix);
    Matrix L(Matrix::identity_matrix(matrix.rows));
    
    size_t column_shift{0};
    
    for(size_t r{} ; r + column_shift < matrix.rows ; r++){ // this loop tries to eliminate 0s from the main diagonal, and fids the shift value
        size_t row_shift{1};
        bool do_column_shift{true};
        bool stop_column_shift{false};
        while(U[r][r + column_shift] == 0 && r + row_shift < matrix.rows){
            if(U[r + row_shift][r + column_shift] != 0){
                Base_Vector temp{U[r]};
                U[r] = U[r + row_shift];
                U[r + row_shift] = temp;
            }
            row_shift++;
        }
        if(U[r][r + column_shift] != 0)
            do_column_shift = false;
        else
            stop_column_shift = true;
        if(do_column_shift && !stop_column_shift){
            column_shift++;
            r = -1; // -1 because the loop will add 1 at the end
        }
    }
    
    for(size_t r{} ; r + column_shift < matrix.rows ; r++){ // elimination
        for(size_t c{r + 1} ; c < matrix.rows ; c++){
            if(U[r][r + column_shift] != 0){
                data_type f{U[c][r + column_shift] / U[r][r + column_shift]};
                L[c][r] = f;
                U[c] -= U[r] * f;
            }
        }
    }
    return {L, U};
}

data_type Matrix::determinant() const{ // returns the determinant value, calculated using LU decopmposition
    if(columns != rows){
        std::cerr << "\nDeterminant can be calculated for square matrices only... \n";
        throw Matrix();
    }
    auto LU{Matrix::LU_decomposition(*this)};
    data_type det{1};
    for(size_t r{} ; r < rows ; r++)
        det *= LU.second[r][r];
    return det;
}

// ========================================================================================================================================== random generation
Matrix Matrix::generate_random(size_t columns, size_t rows, data_type lower_limit, data_type upper_limit, data_type precission){ // random Matrix of given size generator
    if(precission == 0){
        std::cerr << "\nPrecission cannot be equal to 0... \n";
        throw Matrix();
    }
    if(upper_limit < lower_limit){
        std::cerr << "\nUpper limit cannot be smaller than lower limit... \n";
        throw Matrix();
    }
    
    upper_limit /= precission; // dividing by precision to achieve random fractions
    lower_limit /= precission;
    int random_remainder{static_cast<int>(std::ceil((upper_limit - lower_limit + 1)))}; // random numbers are the remainders of dividing rand() by this number
    
    if(random_remainder > static_cast<int>(RAND_MAX)){
        std::cerr << "\nRandom matrix generator range is too big, ((upper_limit - lower_limit) / precission) value is too big... \n";
        throw Matrix();
    }
    
    Matrix random(columns, rows);
    srand(time(nullptr));
    
    for(size_t r{} ; r < random.rows ; r++)
        for(size_t c{} ; c < random.columns ; c++){
            random[r][c] = rand() % random_remainder + lower_limit; // upper_limit is subtracted to achieve negative numbers
            random[r][c] *= precission; // back to given precission
        }
    return random;
}








//if(matrix.columns != matrix.rows){
//        std::cerr << "\nOnly square matrixs can be LU decomposed... \n";
//        throw Matrix();
//    }
//    
//    Matrix U(matrix);
//    Matrix L(Matrix::identity_matrix(matrix.rows));
//    
//    size_t column_shift{0};
//    size_t second_column_shift{0};
//    
//    for(size_t r{} ; r + column_shift < matrix.rows ; r++){ // this loop tries to eliminate 0s from the main diagonal, and fids the shift value
//        size_t row_shift{1};
//        bool do_column_shift{true};
//        bool stop_column_shift{false};
//        while(U[r][r + column_shift] == 0 && r + row_shift < matrix.rows){
//            if(U[r + row_shift][r + column_shift] != 0){
//                Base_Vector temp{U[r]};
//                U[r] = U[r + row_shift];
//                U[r + row_shift] = temp;
//            }
//            row_shift++;
//        }
//        if(U[r][r + column_shift] != 0)
//            do_column_shift = false;
//        else
//            stop_column_shift = true;
//        if(do_column_shift && !stop_column_shift){
//            column_shift++;
//            r = -1; // -1 because the loop will add 1 at the end
//        }
//    }
//    
//    bool repeat{};
//    
//    for(size_t r{} ; r + column_shift + second_column_shift < matrix.rows ; r++){ // elimination
//        for(size_t c{r + 1} ; c < matrix.rows ; c++){
//            if(U[r][r + column_shift + second_column_shift] != 0){
//                data_type f{U[c][r + column_shift + second_column_shift] / U[r][r + column_shift + second_column_shift]};
//                L[c][r] = f;
//                U[c] -= U[r] * f;
//            }
//            else{
//                second_column_shift++;
//                repeat = true;
//                for(size_t test{} ; test < matrix.rows ; test++){ // check if entire column is made of 0s
//                    if(U[test][r + column_shift - 1 + second_column_shift] != 0){
//                        repeat = false;
//                        second_column_shift--;
//                        break;
//                    }
//                }
//            }
//        }
//        if(repeat){
//            repeat = false;
//            r--;
//        }
//    }
//    return {L, U};