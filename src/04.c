#include <stdio.h>

#include "lib/lib.h"


int
next_range(char ** input, size_t range[4])
{
  char * char_p = *input;
  // Format: N1-N2,N3-N4\n
  for (int ii=0; ii<4; ii++) {
    range[ii] = strtoul(char_p, &char_p, 10);
    char_p++; // Skip intermediate '-' and ','.
  }

  *input = char_p;

  if (*char_p == '\0') {
    return 0;
  }

  return 1;
}


void
print_range(size_t range[4])
{
  printf("%zu", range[0]);
  for (int ii=1; ii<4; ii++) {
    printf(", %zu", range[ii]);
  }
  printf("%s", "\n");
}


size_t
first(char * input)
{
  size_t range[4] = {0};

  while(next_range(&input, range)) {
    print_range(range);
  }

  return 0;
}


int
main(void)
{
  char * input_1 = read("inputs/04_test.txt");
  printf("Answer #1: %zu\n", first(input_1));
  free(input_1);
}
