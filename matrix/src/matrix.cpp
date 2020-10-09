#include "matrix.h"
#include "math.h"
#include <vector>
#include <iostream>



namespace task
{

    task::Matrix::Matrix()
    {
        rows = 1;
        cols = 1;
        mat[rows][cols] = {1};
    }
    
    task::Matrix::~Matrix()
    {
        for (int r = 0; r < rows; ++ r)
        {
            delete[] mat[r];
        }
        delete[] mat;
    }
    
    
    task::Matrix::Matrix(size_t rows, size_t cols)
    {
        this->rows = rows;
        this->cols = cols;
        if (rows == cols)
            mat[rows][cols] = {1};
        else
        {
            mat[rows][cols] = {0};
            for (int r = 0; r < rows; ++ r) 
            {
                for (int c = 0; c < cols; ++ c)
                {
                    if (r == c)
                        mat[r][c] = 1;
                }
            }
        }
    }
    
    
    task::Matrix::Matrix(const task::Matrix& copy)
    {
        mat = copy.mat;
        rows = copy.rows;
        cols = copy.cols;
    }
    
    
    
    task::Matrix &task::Matrix::operator=(const task::Matrix& a)
    {
        for (int r = 0; r < rows; ++ r)
        {
            delete[] mat[r];
        }
        delete[] mat;
        
        mat = a.mat;
        rows = a.rows;
        cols = a.cols;
        
        return *this;
    }
    
    
    double& task::Matrix::get(size_t row, size_t col)
    {
        return mat[row][col];
    }
    
    
    const double& task::Matrix::get(size_t row, size_t col) const
    {
        return mat[row][col];
    }
    
    
    void task::Matrix::set(size_t row, size_t col, const double& value)
    {
        mat[row][col] = value;
    }
    
    
    void task::Matrix::resize(size_t new_rows, size_t new_cols)
    {
        double **new_mat;
        new_mat[new_rows][new_cols] = {0};
        
        for (int r = 0; r < new_rows; ++ r) 
        {
            for (int c = 0; c < new_cols; ++ c)
            {
                if (r <= rows & c <= cols)
                    new_mat[r][c] = mat[r][c];
            }
        }
        
        rows = new_rows;
        cols = new_cols;
        mat = new_mat;
    }
    
    
    double* task::Matrix::operator[](size_t row)
    {
        double* pRow = *mat + row;
        return pRow;
    }
    
    const double* task::Matrix::operator[](size_t row) const
    {
        const double* pRow = *mat + row;
        return pRow;
    }
    
    
    task::Matrix task::Matrix::operator+(const task::Matrix& a) const
    {
        if (a.rows != rows | a.cols != cols)
            throw OutOfBoundsException();
        
        task::Matrix newMat = task::Matrix(rows, cols);
        
        for (int r = 0; r < rows; ++ r) 
        {
            for (int c = 0; c < cols; ++ c)
            {
                newMat.mat[r][c] = mat[r][c] + a.mat[r][c];
            }
        }
        
        return newMat;
    }
    
    
    task::Matrix &task::Matrix::operator+=(const task::Matrix&a)
    {
        return *this = *this + a;
    }
    
    task::Matrix task::Matrix::operator-(const task::Matrix& a) const
    {
        if (a.rows != rows | a.cols != cols)
            throw OutOfBoundsException();
        
        task::Matrix newMat = task::Matrix(rows, cols);
        
        for (int r = 0; r < rows; ++ r) 
        {
            for (int c = 0; c < cols; ++ c)
            {
                newMat.mat[r][c] = mat[r][c] - a.mat[r][c];
            }
        }
        
        return newMat;
    }
    
    
    task::Matrix& task::Matrix::operator-=(const task::Matrix&a)
    {
        return *this = *this - a;
    }
    
    
    
    task::Matrix task::Matrix::operator*(const task::Matrix& a) const
    {
        if (cols != a.rows)
            throw SizeMismatchException();
        
        task::Matrix newMat = task::Matrix(rows, a.cols);
        
        for (int r = 0; r < rows; ++ r) 
        {
            for (int c = 0; c < a.cols; ++ c)
            {
                for (int k = 0; k < a.rows; ++ k)
                {
                    newMat.mat[r][c] += mat[r][k] * a.mat[k][c];
                }
            }
        }
        
        return newMat;
    }
    
    
    task::Matrix &task::Matrix::operator*=(const task::Matrix&a)
    {
        return *this = *this * a;
    }
    
    
    
    task::Matrix task::Matrix::operator*(const double& a) const
    {
        task::Matrix newMat = task::Matrix(rows, cols);
        
        for (int r = 0; r < rows; ++ r) 
        {
            for (int c = 0; c < cols; ++ c)
            {
                newMat.mat[r][c] = mat[r][c] * a;
            }
        }
        
        return newMat;
    }
    
    
    task::Matrix &task::Matrix::operator*=(const double& number)
    {
        return *this = *this * number;
    }
    
    
    task::Matrix task::Matrix::operator-() const
    {
        Matrix newMat = *this * -1.0;
        return newMat;
    }
    
    
    task::Matrix task::Matrix::operator+() const
    {
        return *this;
    }
    
    /*
    double detHelper(double** task::Matrix, int n)
    {
        int det = 0;
        int task::Matrix[rows][cols];
        if (n == 2)
            return ((task::Matrix[0][0] * task::Matrix[1][1]) - (task::Matrix[1][0] * task::Matrix[0][1]));
        else 
        {
            for (int x = 0; x < n; x++) 
            {
                int subi = 0;
                for (int i = 1; i < n; i++) 
                {
                    int subj = 0;
                    for (int j = 0; j < n; j++) 
                    {
                       if (j == x)
                       continue;
                       task::Matrix[subi][subj] = task::Matrix[i][j];
                       subj++;
                    }
                    subi++;
                }
                det = det + (pow(-1, x) * task::Matrix[0][x] * detHelper(task::Matrix, n - 1));
            }
        }
        return det;  
    }
    
    
    /* formula for finding determinant taken from tutorialspoint.com*/
    /*
    double task::Matrix::det() const
    {
        if(rows != cols)
            throw SizeMismatchException();
            
        int det = 0;
        int task::Matrix[rows][cols];
        if (rows == 2)
            return ((mat[0][0] * mat[1][1]) - (mat[1][0] * mat[0][1]));
        else 
        {
            for (int x = 0; x < rows; x++) 
            {
                int subi = 0;
                for (int i = 1; i < rows; i++) 
                {
                    int subj = 0;
                    for (int j = 0; j < rows; j++) 
                    {
                       if (j == x)
                       continue;
                       task::Matrix[subi][subj] = mat[i][j];
                       subj++;
                    }
                    subi++;
                }
                det = det + (pow(-1, x) * mat[0][x] * detHelper(task::Matrix, rows - 1));
            }
        }
        return det;
    }
    */
    
    void task::Matrix::transpose()
    {
        task::Matrix transp = task::Matrix(cols, rows);
        
        for (int r = 0; r < rows; ++ r) 
        {
            for (int c = 0; c < cols; ++ c)
            {
                transp.mat[c][r] = mat[r][c];
            }
        }
        
        *this = transp;
    }
    
    
    task::Matrix task::Matrix::transposed() const
    {
        task::Matrix transp = task::Matrix(cols, rows);
        
        for (int r = 0; r < rows; ++ r) 
        {
            for (int c = 0; c < cols; ++ c)
            {
                transp.mat[c][r] = mat[r][c];
            }
        }
        
        return transp;
    }
    
    
    double task::Matrix::trace() const
    {
        if (rows != cols)
            throw SizeMismatchException();
            
        double trac = 0;
        
        for (int r = 0; r < rows; ++ r) 
        {
            trac += mat[r][r];
        }
        
        return trac;
    }
    
    
    std::vector<double> task::Matrix::getRow(size_t row)
    {
        std::vector<double> rower;
        
        for (int c = 0; c < cols; ++ c)
            rower.push_back(mat[row][c]);
            
        return rower;
    }
    
    std::vector<double> task::Matrix::getColumn(size_t column)
    {
        std::vector<double> columner;
        
        for (int r = 0; r < rows; ++ r)
            columner.push_back(mat[r][column]);
            
        return columner;
    }
    
    
    bool task::Matrix::operator==(const task::Matrix& a) const
    {
        if (cols != a.cols | rows != a.rows)
            return false;
        
        for (int r = 0; r < rows; ++ r) 
        {
            for (int c = 0; c < cols; ++ c)
            {
                if (mat[r][c] != a.mat[r][c])
                    return false;
            }
        }
        return true;
    }
    
    
    bool task::Matrix::operator!=(const task::Matrix& a) const
    {
        return !(*this == a);   
    }
    
    
    
    
    
    std::ostream& operator<<(std::ostream& output, const task::Matrix& matrix)
    {
        for (int r = 0; r < matrix.rows; ++ r)
        {
            for (int c = 0; c < matrix.cols; ++ c)
            {
                output << matrix.get(r, c) << " ";
            }
        }
        output << std::endl;
        
        return output;
    }
    
    
    std::istream& operator>>(std::istream& input, task::Matrix& matrix)
    {
        double temp;
        int rw, cln;
        
        input >> rw >> cln;
        
        for (int r = 0; r < rw; ++ r)
        {
            for (int c = 0; c < cln; ++ c)
            {
                input >> temp;
                matrix.set(r, c, temp);
            }
        }
    }
    
    
    task::Matrix operator*(const double& a, const task::Matrix& b)
    {
        task::Matrix newMat = task::Matrix(b.rows, b.cols);
        
        for (int r = 0; r < b.rows; ++ r) 
        {
            for (int c = 0; c < b.cols; ++ c)
            {
                newMat.mat[r][c] = b.mat[r][c] * a;
            }
        }
        return newMat;
    } 
    
}


