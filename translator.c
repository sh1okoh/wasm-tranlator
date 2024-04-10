#include <stdio.h>
#include <stdlib.h>

FILE *ifp, *ofp;
int main ( int argc, char *argv[] ) {
  if ( argc != 3 ) {
    printf("Error: translator <input file> <output file>\n");
    exit(0);
  }

  if ((ifp = fopen(argv[1], "rb")) == NULL) {
    printf("Error: \"%s\" does not exist.\n", argv[1]);
    exit(0);
  }

  if ((ofp = fopen(argv[2], "w")) == NULL) {
    printf("Error: \"%s\" cannot be open.\n", argv[2]);
    exit(0);
  }

  fclose( ifp );
  fclose( ofp );

  // Read the input file and write to the output file
  // char c;
  // while ((c = fgetc(ifp)) != EOF) {
  //   fputc(c, ofp);
  // }
  return 0;
}