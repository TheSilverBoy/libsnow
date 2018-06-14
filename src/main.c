#include "PKMN/PKMN.h"
#include <stdio.h>

extern void
SharedLibraryFunction();

int
main(int argc, char** argv)
{
  SharedLibraryFunction();
  printf("Hello, world!\n");
  return 0;
}
