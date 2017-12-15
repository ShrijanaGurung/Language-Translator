main ( ) { 
matrix m [ 5: 5 ] i: j = i * j ;
matrix n [ 5: 5 ] i: j = i + j ;
matrix a [ 5: 5] i:j = 0;
matrix b [ 5: 5] i:j = 0;

int i ;
i = 0;
int j ;
j = 0;

while (i < 5) {
while (j < 5) {
a[i:j] = i * j / 3;
b[i:j] = i * j / 5;
j=j+1;
}
i=j+1;
}


print("a\n");
repeat (i = 0 to 4 ) {
  repeat ( j = 0 to 4 ) {
    print ( a[i:j] ) ;
    print ("  ");
  }
  print ( "\n" ) ;
}
print("b\n");
repeat (i = 0 to 4 ) {
  repeat ( j = 0 to 4 ) {
    print ( b[i:j] ) ;
    print ("  ");
  }
  print ( "\n" ) ;
}
}
