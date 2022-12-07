#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


#include "lib/lib.h"


int
first(const char * input)
{
  char * char_p = (char *)input;
  unsigned long value = 0;
  for (int ii=0; ii<3; ii++) {
    value = strtoul(char_p, &char_p, 10);
    printf("%lu\n", value);
  }
  return 92;
}


void
top_three_update(unsigned long top_three[3], unsigned long value)
{

  size_t insert_index = 0;
  bool insert_value = false;

  // Index 0 contains the largest value.
  for (int ii=0; ii<3; ii++) {
    if (value > top_three[ii]) {
      insert_index = ii;
      insert_value = true;
      break;
    }
  }

  if (!insert_value) {
    return;
  }

  // Move any lower values if there was a break above.
  for (int ii=2; ii>insert_index; ii--) {
    top_three[ii] = top_three[ii-1];
  }

  top_three[insert_index] = value;
}


int
second(const char * input)
{
  char * char_p = (char *)input;

  unsigned long value = 0;
  unsigned long sum_current = 0;

  unsigned long top_three[3] = {0};

  for(;;) {

    value = strtoul(char_p, &char_p, 10);

    if (value == 0) {
      break;
    }

    sum_current += value;

    if (*char_p == '\n' && *(char_p+1) == '\n') {
      top_three_update(top_three, sum_current);
      sum_current = 0;
    }
  }

  top_three_update(top_three, sum_current);

  unsigned long sum_top_three = 0;
  for (int ii=0; ii<3; ii++) {
    sum_top_three += top_three[ii];
  }

  return sum_top_three;
}


int
main(int argc, char ** argv)
{

  //const char * input_one = read("inputs/01.txt");
  //printf("First answer: %d\n", first(input));

  //const char * input_two = read("inputs/01_test.txt");
  const char * input_two = read("inputs/01.txt");
  printf("Second answer: %d\n", second(input_two));
}
