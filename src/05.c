#include <stdio.h>
#include <stdbool.h>


#include "lib/lib.h"

// =============================================================================
// Shared
// =============================================================================


struct info_input {
  size_t num_columns;
  size_t max_crates_possible;
  char * instructions;
};


struct info_input
get_info_input(char * input)
{
  struct info_input info_input = {0};
  info_input.num_columns = 5;

  size_t counted_rows = 0;
  size_t line_longest = 0;
  size_t line_current = 0;

  // Parse the initial box-setup.
  for(;;input++) {

    printf("%c", *input);
    line_current += 1;

    if (*input == '\n') {

      counted_rows += 1;
      if (line_current > line_longest) {
        line_longest = line_current;
      }
      line_current = 0;

      if (*(input+1) == '\n') {
        input++; // Skip next newline.
        break;
      }

    }
  }

  info_input.num_columns = line_longest / 4;
  info_input.max_crates_possible = info_input.num_columns * (counted_rows - 1);
  info_input.instructions = input;

  return info_input;
}


void
print_info_input(struct info_input * info_input)
{
  printf("%s\n", "INFO:");
  printf("Columns: %zu\n", info_input->num_columns);
  printf("Maximum number of crates: %zu\n", info_input->max_crates_possible);
}


// =============================================================================
// Part I
// =============================================================================


void
first(char * output, struct info_input * info_input)
{
  print_info_input(info_input);
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
