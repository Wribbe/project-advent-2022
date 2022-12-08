#include <stdio.h>
#include <stdbool.h>
#include <string.h>


#include "lib/lib.h"

// =============================================================================
// Shared
// =============================================================================


struct info_input {
  size_t num_columns;
  size_t max_crates_possible;
  char * start;
  char * instructions;
};


struct column {
  char * top;
  size_t height;
};


struct stack {
  size_t len_highest_column;
  size_t num_columns;
  struct column * columns;
};


struct info_input
get_info_input(char * input)
{
  struct info_input info_input = {0};
  info_input.num_columns = 5;
  info_input.start = input;

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


void
print_stack(struct stack * stack)
{
  size_t current_max = stack->len_highest_column;

  for (;current_max > 0;current_max--) {

    for (size_t ii=0; ii<stack->num_columns; ii++) {
      struct column * column = &stack->columns[ii];
      if (column->height < current_max) {
        printf("%s", "   ");
      } else {
        printf("[%c]", *(column->top-(column->height-current_max)));
      }
    }
    printf("%s", "\n");
  }
}

void
stack_add(struct stack * stack, size_t index_column, char box)
{

  if (box == ' ') {
    return;
  }

  struct column * column = &stack->columns[index_column];

  column->top += 1;
  *column->top = box;
  column->height += 1;

  if (stack->len_highest_column < column->height) {
    stack->len_highest_column = column->height;
  }
}


// =============================================================================
// Part I
// =============================================================================


void
execute_instructions(struct info_input * info_input, char * output)
{

  char column_data[info_input->num_columns*info_input->max_crates_possible];
  memset(column_data, 0, sizeof(column_data));
  struct column columns[info_input->num_columns];

  struct stack stack = {
    .len_highest_column = 0,
    .num_columns = info_input->num_columns,
    .columns = columns,
  };

  for (size_t ii=0; ii<info_input->num_columns; ii++) {
    stack.columns[ii].top = &column_data[ii*info_input->max_crates_possible];
    stack.columns[ii].height = 0;
  }

  // Set-up initial state of the stack.
  char * char_p = info_input->start+1;
  size_t current_col = 0;
  for(;;) {

    stack_add(&stack, current_col, *char_p);

    if (*(char_p+2) == '\n') {

      current_col = 0;

      if (*(char_p+4) == '1') {
        break;
      }

    } else {
      current_col++;
    }

    char_p += 4;
  }

  print_stack(&stack);
}


void
first(char * output, struct info_input * info_input)
{
  print_info_input(info_input);
  execute_instructions(info_input, output);
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
