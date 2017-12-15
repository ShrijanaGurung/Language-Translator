main () { 
  matrix m = matrix_read ( "./samples/my_code.dat" ) ;
  matrix n = matrix_read ( "./samples/my_code2.dat" ) ;
  matrix a [ 3: 5] i:j = 0;
  matrix b [ 3: 3] i:j = 0;
  a = m * b;
  print ( a );
  int rows;
  rows = n_rows(m);
  
  int cols;
  cols = n_cols(m);
  int i;
  int j;
  int count;
  count = 0;
  while (count < 2){
    repeat (i = 0 to rows - 1){
    repeat (j = 0 to cols - 1){
      m [i : j ] = m [i : j ] * 2;
  }
  }
  count = count + 1;
  }
     
  print ( "New m:\n" ) ;
  print ( m );
  b = m * n;
  print ( "b:\n" ) ;
  print ( b );
}



