#include <iostream>
 #include "include/Matrix.h"
 #include <math.h>
 using namespace std;
 int main() {
matrix m ( matrix::matrix_read("./samples/my_code.dat"));
 matrix n ( matrix::matrix_read("./samples/my_code2.dat"));
 matrix a (3,5); 
 for( int i=0;i < 3;i++) { 
 for(int j = 0;j< 5;j++) { *(  a.access(i,j)) = 0 ;
}} matrix b (3,3); 
 for( int i=0;i < 3;i++) { 
 for(int j = 0;j< 3;j++) { *(  b.access(i,j)) = 0 ;
}} a = m*b ;
 cout << a ;
 int rows;
 rows = m.n_rows() ;
 int cols;
 cols = m.n_cols() ;
 int i;
 int j;
 int count;
 count = 0 ;
 while(count<2){ for ( i = 0 ; i <= rows-1 ; i++  ) { for ( j = 0 ; j <= cols-1 ; j++  ) { *(m .access( i , j )) = *(m.access(i,j))*2 ;
  }  } count = count+1 ;
  } cout << "New m:\n" ;
 cout << m ;
 b = m*n ;
 cout << "b:\n" ;
 cout << b ;
 }
