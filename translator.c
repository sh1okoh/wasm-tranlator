#include <stdio.h>
#include <stdlib.h>

FILE *ifp, *ofp;
int main ( int argc, char *argv[] ) {
  unsigned char c;

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

  while ( fread(&c, sizeof(char), 1, ifp ) == 1) {
    fprintf( ofp, "\"%02X\",\n", c);
  }

  fclose( ifp );
  fclose( ofp );

  return 0;
}