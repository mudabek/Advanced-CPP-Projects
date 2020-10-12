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
    mat = new double[rows * cols];
    
    for (int i = 0; i < rows * cols; ++ i)
    {
        mat[i] = 1;
    }
}

task::Matrix::~Matrix()
{
    delete [] mat;
}


task::Matrix::Matrix(size_t rows, size_t cols)
{
    this->rows = rows;
    this->cols = cols;
    mat = new double[rows * cols];
    
    for (int r = 0; r < rows; ++ r)
    {
        for (int c = 0; c < cols; ++ c)
        {
            if (r == c || rows == cols)
                mat[cols * r + c] = 1.0;
            else
                mat[cols * r + c] = 0.0;
        }
    }
}


task::Matrix::Matrix(const task::Matrix& copy)
{
    rows = copy.rows;
    cols = copy.cols;
    mat = new double[rows * cols];
    
    for (int i = 0; i < rows * cols; ++ i)
    {
        mat[i] = copy.mat[i];
    }
    
}



task::Matrix &task::Matrix::operator=(const task::Matrix& a)
{
    if (a == *this)
        return *this;
    
    
    delete[] mat;

    rows = a.rows;
    cols = a.cols;
    
    mat = new double[rows * cols];
    
    for (int i = 0; i < rows * cols; ++ i)
        mat[i] = a.mat[i];
    
    return *this;
}

void task::Matrix::checkDim (size_t row, size_t col)
{
    if (row > (rows - 1) || row < 0 || col > (cols - 1) || col < 0)
        throw OutOfBoundsException();
}

void task::Matrix::checkDim (size_t row, size_t col) const
{
    if (row > (rows - 1) || row < 0 || col > (cols - 1) || col < 0)
        throw OutOfBoundsException();
}


double& task::Matrix::get(size_t row, size_t col)
{
    checkDim(row, col);   
    return mat[cols * row + col];
}


const double& task::Matrix::get(size_t row, size_t col) const
{
    checkDim(row, col);
    return mat[cols * row + col];
}


void task::Matrix::set(size_t row, size_t col, const double& value)
{
    checkDim(row, col);
    mat[cols * row + col] = value;
}


void task::Matrix::resize(size_t new_rows, size_t new_cols)
{
    double* temp_mat;
    temp_mat = new double[new_rows * new_cols];
    
    for (int r = 0; r < new_rows; ++ r)
    {
        for (int c = 0; c < new_cols; ++ c)
        {
            if (r < rows & c < cols) 
            {
                temp_mat[new_cols * r + c] = mat[new_rows * r + c]; 
            }
            else
                temp_mat[new_cols * r + c] = 0;
        }
    }
    

    delete [] mat;
    mat = temp_mat;
    rows = new_rows;
    cols = new_cols;
}


double* task::Matrix::operator[](size_t row)
{
    if ((row < 0) || (row > rows - 1))
        throw OutOfBoundsException();
        

    double* pRow = mat + row * cols;
    return pRow;
}

const double* task::Matrix::operator[](size_t row) const
{
    if ((row < 0) || (row > rows - 1))
        throw OutOfBoundsException();
        
    const double* pRow = mat + row * cols;
    
    return pRow;
}


task::Matrix task::Matrix::operator+(const task::Matrix& a) const
{
    if (a.rows != rows | a.cols != cols)
        throw SizeMismatchException();

    Matrix newMat = Matrix(rows, cols);

    for (int k = 0; k < rows * cols; ++ k)
        newMat.mat[k] = mat[k] + a.mat[k];

    return newMat;
}


task::Matrix &task::Matrix::operator+=(const task::Matrix&a)
{
    return *this = *this + a;
}

task::Matrix task::Matrix::operator-(const task::Matrix& a) const
{
    if (a.rows != rows | a.cols != cols)
        throw SizeMismatchException();

    Matrix newMat = Matrix(rows, cols);

    for (int k = 0; k < rows * cols; ++ k)
        newMat.mat[k] = mat[k] - a.mat[k];

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

    Matrix newMat = Matrix(rows, a.cols);
    double val;

    for (int r = 0; r < rows; ++ r)
    {
        for (int c = 0; c < a.cols; ++ c)
        {
            val = 0;
            for (int k = 0; k < cols; ++ k)
            {
            
                val += mat[r * cols + k] * a.mat[k * a.cols + c];
            }
            newMat.mat[a.cols * r + c] = val;
        }
    }

    return newMat;
}


task::Matrix &task::Matrix::operator*=(const task::Matrix&a)
{
    if (cols != a.rows)
        throw SizeMismatchException();
    return *this = *this * a;
}



task::Matrix task::Matrix::operator*(const double& a) const
{
    Matrix newMat = Matrix(rows, cols);
    double val;
    
    for (int k = 0; k < rows * cols; ++ k)
    {
        newMat.mat[k] = mat[k] * a;
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


double task::Matrix::Minor(double row_, double col_) const
{
  int    minCol = 0;
  Matrix minMat = Matrix(rows-1, cols-1);
  double result = 0;
  int    minRow = 0;

  for (int row = 0; row < rows; ++row)
  {
    if (row != row_)
    {
      for (int col = 0; col < cols; ++col)
      {
        if  (col != col_)
        {
          minMat[minRow][minCol] = (*this)[row][col];
          ++minCol;
        }
      }
      ++minRow;
      minCol = 0;
    }
  }

  result = minMat.det();

  return result;
}


bool WithinTolerance(double arg1, double arg2, double tol)
{
  bool test;

  if (tol == 0.0)
  {
    std::numeric_limits<double> lim;

    double eps = lim.min();

    tol = eps;
  }

  test = fabs(arg1 - arg2) <= tol;

  return test;
}




double task::Matrix::det() const
{
    if (rows != cols)
    {
        throw SizeMismatchException();
    }

    double cofactor;
    int col = 0;
    bool done = false;;
    int maxZeroRow = 0;
    double minor = 0.0;;
    int prevZeroCnt = 0;
    double result = 0.0;
    int row = 0;
    double sign = 0.0;
    int zeroCnt = 0;

    
    if (rows == 1)
    {
        result = *mat;
        done = true;
    }

    if (!done)
    {
        if (rows == 2)
        {
            result = (*this)[0][0] * (*this)[1][1] - (*this)[0][1] * (*this)[1][0];
            done = true;
        }
    }

    if (!done)
    {
        for (row = 0; row < rows; ++row)
        {
            zeroCnt = 0.0;
            for (col = 0; col < cols; ++col)
            {
                if (WithinTolerance((*this)[row][col],  0.0, 0.0))
                {
                    ++zeroCnt;
                }
            }
            if (zeroCnt == cols)
            {
                result = 0.0;
                done = true;
                break;
            }
            else if (zeroCnt > prevZeroCnt)
            {
                maxZeroRow = row;
                prevZeroCnt = zeroCnt;
            }
        }

        row = maxZeroRow;

    } 
    
    if (!done)
    {
        for (col = 0; col < cols; ++col)
        {
            if (!WithinTolerance(mat[row*cols+col], 0.0, 0.0))
            {
                sign = (row + col) % 2 == 0 ? 1.0 : -1.0;

                minor = this->Minor(row, col);

                cofactor = sign * mat[row*cols+col] * minor;

                result += cofactor;
            }
        }
    } 

    return result;
}

void task::Matrix::transpose()
{
    task::Matrix transp = task::Matrix(cols, rows);
    for (int r = 0; r < rows; ++ r)
    {
        for (int c = 0; c < cols; ++ c)
        {
            transp.set(c, r, this->get(r, c));
        }
    }

    delete [] mat;
    mat = transp.mat;
    rows = transp.rows;
    cols = transp.cols;
}


task::Matrix task::Matrix::transposed() const
{
    task::Matrix transp = task::Matrix(cols, rows);

    for (int r = 0; r < rows; ++ r)
    {
        for (int c = 0; c < cols; ++ c)
        {
            transp.set(c, r, this->get(r, c));
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
        trac += this->get(r, r);
    }

    return trac;
}


std::vector<double> task::Matrix::getRow(size_t row)
{
    std::vector<double> rower;

    for (int c = 0; c < cols; ++ c)
        rower.push_back(this->get(row, c));

    return rower;
}

std::vector<double> task::Matrix::getColumn(size_t column)
{
    std::vector<double> columner;

    for (int r = 0; r < rows; ++ r)
        columner.push_back(this->get(r, column));

    return columner;
}


bool task::Matrix::operator==(const task::Matrix& a) const
{
    if (cols != a.cols || rows != a.rows)
        return false;

    for (int k = 0; k < rows * cols; ++ k)
    {
        if (abs(mat[k] - a.mat[k]) > EPS)
            return false;
    }
    return true;
}


bool task::Matrix::operator!=(const task::Matrix& a) const
{
    return !(*this == a);
}





std::ostream& operator<<(std::ostream& output, const task::Matrix& matrix)
{
    for (int k = 0; k < matrix.rows * matrix.cols; ++ k)
        output << matrix.mat[k] << " ";

    output << std::endl;

    return output;
}
    
    

std::istream& operator>>(std::istream& input, task::Matrix& matrix)
{
    int rw, cln;

    input >> rw >> cln;
    
    delete [] matrix.mat;
    matrix.mat = new double[rw * cln];
    matrix.rows = rw;
    matrix.cols = cln;
    
    for (int k = 0; k < rw * cln; ++ k)
        input >> matrix.mat[k];
    
    return input;
}


task::Matrix operator*(const double& a, const task::Matrix& b)
{
    task::Matrix newMat = task::Matrix(b.rows, b.cols);

    for (int r = 0; r < b.rows; ++ r)
    {
        for (int c = 0; c < b.cols; ++ c)
        {
            newMat.set(r, c, a * b.get(r, c));
        }
    }
    return newMat;
}
}


