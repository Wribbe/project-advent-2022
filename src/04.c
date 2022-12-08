#include <stdio.h>
#include <stdbool.h>

#include "lib/lib.h"


// =============================================================================
// SHARED
// =============================================================================


int
next_range(char ** input, size_t range[4])
{
  char * char_p = *input;

  if (*char_p == '\0') {
    return 0;
  }

  // Format: N1-N2,N3-N4\n
  for (int ii=0; ii<4; ii++) {
    range[ii] = strtoul(char_p, &char_p, 10);
    char_p++; // Skip intermediate '-' and ','.
  }

  *input = char_p;

  return 1;
}


// =============================================================================
// PART I
// =============================================================================


bool
a_contains_b(size_t a1, size_t a2, size_t b1, size_t b2)
{
  return a1 <= b1 && a2 >= b2;
}


bool
full_overlap(size_t range[4])
{
  size_t a1 = range[0], a2 = range[1], b1 = range[2], b2 = range[3];
  return a_contains_b(a1, a2, b1, b2) || a_contains_b(b1, b2, a1, a2);
}


void
print_range(size_t range[4])
{
  printf("%zu", range[0]);
  for (int ii=1; ii<4; ii++) {
    printf(", %zu", range[ii]);
  }
  printf(", Fully overlaps: %d", full_overlap(range));
  printf("%s", "\n");
}


size_t
first(char * input)
{
  size_t range[4] = {0};
  size_t sum_overlapping_pairs = 0;

  while(next_range(&input, range)) {
    print_range(range);
    sum_overlapping_pairs += full_overlap(range);
  }

  return sum_overlapping_pairs;
}


int
main(void)
{
  char * input_1 = read("inputs/04.txt");
  printf("Answer #1: %zu\n", first(input_1));
  free(input_1);
}
