#include <string.h>


#include "lib/lib.h"


struct rucksack {
  size_t size_compartment;
  const char * contents_start;
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

  rucksack->size_compartment = size_compartment;
  rucksack->contents_start = start;

  *input = start+size_rucksack;
}


void
rucksack_print(struct rucksack * rucksack)
{
  size_t size_comp = rucksack->size_compartment;
  const char * start = rucksack->contents_start;

  printf("Size compartment: %zu\n", size_comp);
  printf("%s\n", "Contents:");
  printf("  %.*s\n", (int)size_comp, start);
  printf("  %.*s\n", (int)size_comp, start+size_comp);
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
