#include "lib/lib.h"


#include <string.h>


int
first(char * input)
{
  return 0;
}


int
second(char * input)
{
  return 0;
}


int
main(void)
{
  char * input_first = read("inputs/03_test.txt");
  printf("Result #1: %d\n", first(input_first));

  char * input_second = read("inputs/03_test.txt");
  printf("Result #2: %d\n", second(input_second));

  free(input_first);
  free(input_second);
}
