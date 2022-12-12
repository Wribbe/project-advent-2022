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


typedef void (*crane_op)(
  struct stack * stack,
  size_t num_crates,
  size_t column_from,
  size_t column_to
);


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
  info_input.instructions = input+1; // Skip past empty line.

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
stack_print(struct stack * stack)
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
stack_crate_push(struct stack * stack, size_t index_column, char box)
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


bool
next_instruction(
    char ** p_instructions,
    size_t * num_boxes,
    size_t * column_from,
    size_t * column_to
){
  char * p_char = *p_instructions;

  if (*p_char == '\0') {
    return false;
  }

  int s_num_boxes = 0;
  int s_column_from = 0;
  int s_column_to = 0;

  sscanf(
    p_char,
    "%*s%d%*s%d%*s%d",
    &s_num_boxes, &s_column_from, &s_column_to
  );

  *num_boxes = s_num_boxes;
  *column_from = s_column_from-1;
  *column_to = s_column_to-1;

  for (;;p_char++) {
    if (*p_char == '\n') {
      p_char++;
      break;
    }
  }

  *p_instructions = p_char;
  return true;
}

char
stack_crate_pop(struct stack * stack, size_t col)
{
  struct column * column = &stack->columns[col];

  if (column->height == 0) {
    return ' ';
  }

  column->height--;
  return *column->top--;
}


char
stack_crate_peek(struct stack * stack, size_t col)
{
  struct column * column = &stack->columns[col];

  if (column->height == 0) {
    return ' ';
  }
  return *column->top;
}


void
stack_crate_move(struct stack * stack, size_t col_from, size_t col_to)
{
  stack_crate_push(stack, col_to, stack_crate_pop(stack, col_from));
}


void
stack_init(
  struct info_input * info_input,
  struct stack * stack,
  char * column_data
) {
  for (size_t ii=0; ii<info_input->num_columns; ii++) {
    stack->columns[ii].top = &column_data[ii*info_input->max_crates_possible];
    stack->columns[ii].height = 0;
  }

  char * char_p = info_input->instructions;

  // Rewind to last newline before line of numbers.
  bool seen_first_col_lable = false;
  for (;;char_p--) {
    if (*char_p == '1') {
      seen_first_col_lable = true;
    }
    if (seen_first_col_lable && *char_p == '\n') {
      char_p -= 2; // Align with first box-label.
      break;
    }
  }

  char seen_crates[info_input->num_columns];
  memset(seen_crates, 0, sizeof(seen_crates));
  char * seen_latest = &seen_crates[0];

  for(;char_p >= info_input->start; char_p -= 4) {

    *seen_latest++ = *char_p;

    if (*(char_p-2) == '\n' || char_p-1 == info_input->start) {

      seen_latest--;
      size_t current_col = 0;

      for(;;current_col++,seen_latest--) {

        stack_crate_push(stack, current_col, *seen_latest);

        if (seen_latest == seen_crates) {
          break;
        }

      }
    }
  }
  stack_print(stack);
}


void
execute_instructions(struct info_input * info_input, char * output, crane_op crane_op)
{

  char column_data[info_input->num_columns*info_input->max_crates_possible];
  memset(column_data, 0, sizeof(column_data));
  struct column columns[info_input->num_columns];

  struct stack stack = {
    .len_highest_column = 0,
    .num_columns = info_input->num_columns,
    .columns = columns,
  };

  stack_init(info_input, &stack, column_data);
  char * p_instructions = info_input->instructions;

  size_t num_crates = 0;
  size_t col_from = 0;
  size_t col_to = 0;

  while (next_instruction(&p_instructions, &num_crates, &col_from, &col_to)) {
    crane_op(&stack, num_crates, col_from, col_to);
  }

  for (size_t ii=0; ii<info_input->num_columns; ii++) {
    output[ii] = stack_crate_peek(&stack, ii);
  }
  output[info_input->num_columns] = '\0';
}


// =============================================================================
// Part I
// =============================================================================


void
crate_mover_9000(
    struct stack * stack,
    size_t num_crates,
    size_t col_from,
    size_t col_to
) {
  for (;num_crates > 0;num_crates--) {
    stack_crate_move(stack, col_from, col_to);
  }
}


void
first(char * output, struct info_input * info_input)
{
  print_info_input(info_input);
  execute_instructions(info_input, output, crate_mover_9000);
}


// =============================================================================
// Part II
// =============================================================================


void
crate_mover_9001(
    struct stack * stack,
    size_t num_crates,
    size_t col_from,
    size_t col_to
) {

  char temp_col[num_crates];
  memset(temp_col, 0, sizeof(temp_col));

  char * top = temp_col;

  for (;num_crates > 0;num_crates--) {
    *top++ = stack_crate_pop(stack, col_from);
  }

  for (;;top--) {
    stack_crate_push(stack, col_to, *top);
    if (top == temp_col) {
      break;
    }
  }
}

void
second(char * output, struct info_input * info_input)
{
  print_info_input(info_input);
  execute_instructions(info_input, output, crate_mover_9001);
}

// =============================================================================
// Main
// =============================================================================

int
main(void)
{
  char * input_1 = read("inputs/05.txt");

  struct info_input info_input_1 = get_info_input(input_1);
  char output_1[info_input_1.num_columns];
  first(output_1, &info_input_1);

  printf("#1: Final box arrangement: %s\n", output_1);
  free(input_1);

  char * input_2 = read("inputs/05_test.txt");

  struct info_input info_input_2 = get_info_input(input_2);
  char output_2[info_input_2.num_columns];
  second(output_2, &info_input_2);

  printf("#2: Final box arrangement: %s\n", output_2);
  free(input_2);
}
