#include <string.h>


#include "lib/lib.h"


struct rucksack {
  struct slice compartment_1;
  struct slice compartment_2;
  char common;
};


void
rucksack_next(char ** input, struct rucksack * rucksack)
{

  char * start = *input;
  char * end = start;

  for (;;end++) {
    if (*end == '\n') {
      end++;
      break;
    }
  }

  size_t size_rucksack = end-start;
  size_t size_compartment = size_rucksack / 2;

  char * middle = start + size_compartment;

  rucksack->compartment_1.size = size_compartment;
  rucksack->compartment_1.start = start;

  rucksack->compartment_2.size = size_compartment;
  rucksack->compartment_2.start = start+size_compartment;

  *input = start+size_rucksack;
}


void
rucksack_print(struct rucksack * rucksack)
{
  printf("%s\n", "Contents:");

  printf("%s", "  ");
  slice_print(&rucksack->compartment_1);
  printf("%s", "\n");

  printf("%s", "  ");
  slice_print(&rucksack->compartment_2);
  printf("%s", "\n");

  printf("%s", "\n");
}


int
first(char * input)
{

  struct rucksack rucksack = {0};

  for (;;) {

    rucksack_next(&input, &rucksack);
    rucksack_print(&rucksack);

    if (*input == '\0') {
      break;
    }

  }

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
