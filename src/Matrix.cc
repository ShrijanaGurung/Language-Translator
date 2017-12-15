/*******************************************************************************
 * Name            : Matrix
 * Project         : fcal
 * Module          : matrix
 * Description     : Implementation file for Matrix class
 * Original Author : Luke Erlandson and Shrijana Gurung
 * Copyright       : Luke Erlandson and Shrijana Gurung
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/Matrix.h"
#include <cassert>
#include <fstream>
#include <iostream>

/*******************************************************************************
 * Constructors/Methods for our Matrix class
 ******************************************************************************/
/*!
 * Matrix Constructor
 */
matrix::matrix(int i, int j) : rows(i), cols(j) {
  data = reinterpret_cast<float *>(malloc(sizeof(int) * i * j));
}

/*!
 * Matrix Constructor
 */
matrix::matrix(const matrix &m) : rows(m.rows), cols(m.cols) {
  int i, j;
  data = reinterpret_cast<float *>(malloc(sizeof(int) * m.rows * m.cols));
  for (i = 0; i < rows; ++i) {
    for (j = 0; j < cols; ++j) {
      *(access(i, j)) = *(m.access(i, j));
    }
  }
}
/*!
 * Matrix destructor
*/
matrix::~matrix() { delete[] data; }

/*!
 * Copy assignment
 */
matrix &matrix::operator=(const matrix &b) {
  if ( rows == b.n_rows() && cols == b.n_cols() ) {
    data = new float[rows * cols];
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        *(access(i, j)) = *(b.access(i, j));
      }
    }
  } else { std::cout << "Incorrect matrix assignment\n"; }
  return *this;
}

/*
 * Matrix addition
 */
const matrix matrix::operator+(const matrix &b) const {
  int i, j;
  assert(b.n_rows() == rows);
  assert(b.n_cols() == cols);
  matrix c = *this;
  for (i = 0; i < rows; ++i) {
    for (j = 0; j < cols; ++j) {
      *c.access(i, j) += *(b.access(i, j));
    }
  }
  return c;
}
/*!
 * Matrix multiplication
 * */
const matrix matrix::operator*(const matrix &b) const {
  matrix c = matrix(rows, b.cols);
  double sum;
  if (cols == b.rows) {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < b.cols; j++) {
        sum = 0;
        for (int k = 0; k < b.rows; k++) {
          sum += *this->access(i, k) * *b.access(j, k);
        }
        *c.access(i, j) = sum;
      }
    }
  } else { std::cout << "Incorrect matrix multiplication\n"; }
  return c;
}

/*!
 * Matrix n_rows
 */
int matrix::n_rows() const { return rows; }

/*!
 * Matrix n_cols
 */
int matrix::n_cols() const { return cols; }

/*!
 * Matrix access
 */
float *matrix::access(const int i, const int j) const {
  return data + (i * cols) + j;
}

/*!
 * Matrix matrix_read
 */
matrix matrix::matrix_read(std::string filename) {
  std::ifstream in(filename.c_str());
  if (!in) {
    throw "File " + filename + " not found.";
  }

  int r;
  in >> r;
  int c;
  in >> c;

  matrix temp(r, c);
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      in >> *(temp.access(i, j));
    }
  }
  return temp;
}

/*!
 * Matrix ostream
*/
std::ostream &operator<<(std::ostream &os, const matrix &m) {
  os << m.rows << " " << m.cols << std::endl;
  for (int i = 0; i < m.rows; ++i) {
    for (int j = 0; j < m.cols; ++j) {
      os << *(m.access(i, j)) << "  ";
    }
    os << std::endl;
  }
  return os;
}

