#include <stdio.h>
#include <stdlib.h>

FILE *ifp, *ofp;
int main ( int argc, char *argv[] ) {
  unsigned char c, sec;
  int sec_siz;

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

  for (sec_siz = 8; sec_siz > 0; sec_siz-- ) {
    fread(&c, sizeof(char), 1, ifp);
  }


  while ( fread(&c, sizeof(char), 1, ifp ) == 1) {
    sec = c;
    fread( &c, sizeof(char), 1, ifp);
    sec_siz = c & 0x7F;
    if ((c & 0x80) != 0) {
      fread( &c, sizeof(char), 1, ifp);
      sec_siz = (((int)c & 0x7F) << 7) | sec_siz;
      if ((c & 0x80) != 0) {
        fread( &c, sizeof(char), 1, ifp);
        sec_siz = (((int)c & 0x7F) << 14) | sec_siz;
        if ((c & 0x80) != 0) {
          fread( &c, sizeof(char), 1, ifp);
          sec_siz = (((int)c & 0x7F) << 21) | sec_siz;
        }
      }
    }
    if ( sec != 0x0A) {
      for (; sec_siz > 0; sec_siz-- ) {
        fread(&c, sizeof(char), 1, ifp);
      }
    } else { // Code section
      fread(&c, sizeof(char), 1, ifp);
      for (; sec_siz > 0; sec_siz-- ) {
        fread(&c, sizeof(char), 1, ifp);
        fprintf( ofp, "\"%02X\",\n", c);
      }
    }
  }

  fclose( ifp );
  fclose( ofp );

  return 0;
}