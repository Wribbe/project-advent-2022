#include <stdio.h>


#include "lib/lib.h"

// =============================================================================
// Shared
// =============================================================================


struct info_input {
  size_t num_columns;
  char * instructions;
};


struct info_input
get_info_input(char * input)
{
  struct info_input info_input = {0};
  info_input.num_columns = 5;

  return info_input;
}


// =============================================================================
// Part I
// =============================================================================


void
first(char * output, struct info_input * info_input)
{
  for (size_t ii=0; ii<info_input->num_columns; ii++) {
    output[ii] = 'X';
  }
}


// =============================================================================
// Main
// =============================================================================

int
main(void)
{
  char * input_1 = read("inputs/05_test.txt");

  struct info_input info_input = get_info_input(input_1);
  char output_1[info_input.num_columns];
  first(output_1, &info_input);

  printf("#1: Final box arrangement: %s\n", output_1);
}
