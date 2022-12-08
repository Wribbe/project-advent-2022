#include <stdio.h>

#include "lib/lib.h"


size_t
first(char * input)
{
  return 0;
}


int
main(void)
{
  char * input_1 = read("inputs/04_test.txt");
  printf("Answer #1: %zu\n", first(input_1));
  free(input_1);
}
