#include "matrix.h"

#include <vector>
#include <iostream>

using namespace task;

class Matrix
{
public:
    
    Matrix()
    {
        rows = 1;
        cols = 1;
        double mat[rows][cols] = {1};
        return this;
    }
    
    ~Matrix()
    {
        delete rows;
        delete cols;
        delete[] mat;
    }
    
    
    Matrix(size_t rows, size_t cols)
    {
        rows = rows;
        cols = cols;
        if (rows == cols)
            double mat[rows][cols] = {1};
        else
        {
            double mat[rows][cols] = {0};
            for (int r = 0; r < rows; ++ r) 
            {
                for int (int c = 0; c < cols; ++ c)
                {
                    if (r == c)
                        mat[r][c] = 1;
                }
            }
        }
        return this;
    }
    
    
    Matrix(const Matrix& copy)
    {
        rows = copy.rows;
        cols = copy.cols;
        mat = new double[rows][cols];
        
        for (int r = 0; r < rows; ++ r) 
        {
            for int (int c = 0; c < cols; ++ c)
            {
                if (r == c)
                    mat[r][c] = copy[r][c];
                else
                    mat[r][c] = copy[r][c];
            }
        }
        return this;
    }
    
    
    Matrix& operator=(const Matrix& a)
    {
        if (&a == *this) 
            return *this;
            
        delete rows;
        delete cols;
        delete[] mat;
        
        mat = a.mat;
        rows = a.rows;
        cols = a.cols;
        
        return *this;
    }
    
    
    double& get(size_t row, size_t col)
    {
        return mat[row][col];
    }
    
    
    const double& get(size_t row, size_t col) const
    {
        return mat[row][col];
    }
    
    
    void set(size_t row, size_t col, const double& value)
    {
        mat[row][col] = value;
    }
    
    
    void resize(size_t new_rows, size_t new_cols)
    {
        double new_mat[new_rows][new_cols] = {0};
        
        for (int r = 0; r < new_rows; ++ r) 
        {
            for int (int c = 0; c < new_cols; ++ c)
            {
                if (r <= rows & c <= cols)
                    new_mat[r][c] = mat[r][c];
            }
        }
        delete rows;
        delete cols;
        delete[] mat;
        
        rows = new_rows;
        cols = new_cols;
        mat = new_mat;
    }
    
    
    
    class Row {
        
        friend class Matrix;
        
    public:
        
        int& operator[](int col)
        {
            return parent.mat[row][col];
        }
        
        int& operator[](int col) const
        {
            return parent.mat[row][col];
        }
        
    private:
    
        Row(Matrix &parent_, int row_) : parent(parent_), row(row_) {}

        Matrix& parent;
        int row;
    };
    
    
    Row& operator[](size_t row)
    {
        Row curRow = Row(mat, row);
        return curRow[];
    }
    
    Row& operator[](size_t row) const
    {
        Row curRow = Row(mat, row);
        return curRow[];
    }
    
    Matrix operator+(const Matrix& a) const
    {
        if (a.rows != rows | a.cols != cols)
            throw OutOfBoundsException();
        
        Matrix newMat = Matrix(rows, cols);
        
        for (int r = 0; r < rows; ++ r) 
        {
            for int (int c = 0; c < cols; ++ c)
            {
                newMat.mat[r][c] = this.mat[r][c] + a.mat[r][c];
            }
        }
        
        return newMat;
    }
    
    
    Matrix& operator+=(const Matrix&a)
    {
        return *this = *this + a;
    }
    
    Matrix operator-(const Matrix& a) const
    {
        if (a.rows != rows | a.cols != cols)
            throw OutOfBoundsException();
        
        Matrix newMat = Matrix(rows, cols);
        
        for (int r = 0; r < rows; ++ r) 
        {
            for int (int c = 0; c < cols; ++ c)
            {
                newMat.mat[r][c] = this.mat[r][c] - a.mat[r][c];
            }
        }
        
        return newMat;
    }
    
    
    Matrix& operator-=(const Matrix&a)
    {
        return *this = *this - a;
    }
    
    
    
    Matrix operator*(const Matrix& a) const
    {
        if (cols != a.rows)
            throw SizeMismatchException();
        
        Matrix newMat = Matrix(rows, a.cols);
        
        for (int r = 0; r < rows; ++ r) 
        {
            for int (int c = 0; c < a.cols; ++ c)
            {
                for (int k = 0; k < a.rows; ++ k)
                {
                    newMat.mat[r][c] += this.mat[r][k] * a.mat[k][c];
                }
            }
        }
        
        return newMat;
    }
    
    
    Matrix& operator*=(const Matrix&a)
    {
        return *this = *this * a;
    }
    
    
    
    Matrix operator*(const double& a) const
    {
        Matrix newMat = Matrix(rows, cols);
        
        for (int r = 0; r < rows; ++ r) 
        {
            for int (int c = 0; c < cols; ++ c)
            {
                newMat.mat[r][c] = this.mat[r][c] * a;
            }
        }
        
        return newMat;
    }
    
    
    Matrix& operator*=(const double& number)
    {
        return *this = *this * number;
    }
    
    
    Matrix operator-() const
    {
        return *this = *this * 1;
    }
    
    
    Matrix operator+() const
    {
        return *this;
    }
    
    
    /* formula for finding determinant taken from tutorialspoint.com*/
    double det() const
    {
        if(rows != cols)
            throw SizeMismatchException();
            
        int det = 0;
        int submatrix[rows][cols];
        if (rows == 2)
            return ((matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]));
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
                       submatrix[subi][subj] = matrix[i][j];
                       subj++;
                    }
                    subi++;
                }
                det = det + (pow(-1, x) * matrix[0][x] * determinant( submatrix, rows - 1 ));
            }
        }
        return det;
    }
    
    
    void transpose()
    {
        Matrix transp = Matrix(cols, rows);
        
        for (int r = 0; r < rows; ++ r) 
        {
            for int (int c = 0; c < cols; ++ c)
            {
                transp.mat[c][r] = this.mat[r][c];
            }
        }
        
        *this = transp;
    }
    
    
    Matrix transposed() const
    {
        Matrix transp = Matrix(cols, rows);
        
        for (int r = 0; r < rows; ++ r) 
        {
            for int (int c = 0; c < cols; ++ c)
            {
                transp.mat[c][r] = this.mat[r][c];
            }
        }
        
        return transp;
    }
    
    
    double trace() const
    {
        if (row != col)
            throw SizeMismatchException();
            
        double trac = 0;
        
        for (int r = 0; r < rows; ++ r) 
        {
            trac += mat[r][c];
        }
        
        return trac;
    }
    
    
    std::vector<double> getRow(size_t row)
    {
        std::vector<double> rower;
        
        for (int c = 0; c < cols; c++)
            rower.push_back(mat[row][c]);
            
        return rower;
    }
    
    std::vector<double> getColumn(size_t column)
    {
        std::vector<double> columner;
        
        for (int r = 0; r < rows; c++)
            columner.push_back(mat[r][column]);
            
        return columner;
    }
    
    
    bool operator==(const Matrix& a) const
    {
        if (col != a.col | row != a.row)
            return false;
        
        for (int r = 0; r < rows; ++ r) 
        {
            for int (int c = 0; c < cols; ++ c)
            {
                if (mat[r][c] != a.mat[r][c])
                    return false;
            }
        }
        return true;
    }
    
    
    bool operator!=(const Matrix& a) const
    {
        return !(this == a);   
    }
    
};



