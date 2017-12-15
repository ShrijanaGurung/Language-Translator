#include <iostream>
 #include "include/Matrix.h"
 #include <math.h>
 using namespace std;
 int main() {
matrix m (5,5); 
 for( int i=0;i < 5;i++) { 
 for(int j = 0;j< 5;j++) { *(  m.access(i,j)) = i*j ;
}} matrix n (5,5); 
 for( int i=0;i < 5;i++) { 
 for(int j = 0;j< 5;j++) { *(  n.access(i,j)) = i+j ;
}} matrix a (5,5); 
 for( int i=0;i < 5;i++) { 
 for(int j = 0;j< 5;j++) { *(  a.access(i,j)) = 0 ;
}} matrix b (5,5); 
 for( int i=0;i < 5;i++) { 
 for(int j = 0;j< 5;j++) { *(  b.access(i,j)) = 0 ;
}} int i;
 i = 0 ;
 int j;
 j = 0 ;
 while(i<5){ while(j<5){ *(a .access( i , j )) = i*j/3 ;
 *(b .access( i , j )) = i*j/5 ;
 j = j+1 ;
  } i = j+1 ;
  } cout << "a\n" ;
 for ( i = 0 ; i <= 4 ; i++  ) { for ( j = 0 ; j <= 4 ; j++  ) { cout << *(a.access(i,j)) ;
 cout << "  " ;
  } cout << "\n" ;
  } cout << "b\n" ;
 for ( i = 0 ; i <= 4 ; i++  ) { for ( j = 0 ; j <= 4 ; j++  ) { cout << *(b.access(i,j)) ;
 cout << "  " ;
  } cout << "\n" ;
  } }
