#include <string.h>


#include "lib/lib.h"


struct rucksack {
  struct slice compartment_1;
  struct slice compartment_2;
  char common;
  int priority;
};


int
item_priority(char item)
{
  size_t count = 0;
  for (;;count++,item--) {
    if (item == 'a') {
      return 1+count;
    }
    if (item == 'A') {
      return 27+count;
    }
  }
}


char
find_first_matching(struct slice * a, struct slice * b)
{
  for (size_t ii=0; ii<a->size; ii++) {
    for (size_t jj=0; jj<b->size; jj++) {
      if (a->start[ii] == b->start[jj]) {
        return a->start[ii];
      }
    }
  }
  return '!';
}


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

  rucksack->compartment_1.size = size_compartment;
  rucksack->compartment_1.start = start;

  rucksack->compartment_2.size = size_compartment;
  rucksack->compartment_2.start = start+size_compartment;

  rucksack->common = find_first_matching(
    &rucksack->compartment_1,
    &rucksack->compartment_2
  );

  rucksack->priority = item_priority(rucksack->common);

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

  printf("Common: %c\n", rucksack->common);
  printf("Priority: %d\n", rucksack->priority);

  printf("%s", "\n");
}


size_t
first(char * input)
{

  struct rucksack rucksack = {0};
  size_t sum_priorities = 0;

  for (;;) {

    rucksack_next(&input, &rucksack);
    rucksack_print(&rucksack);

    sum_priorities += rucksack.priority;

    if (*input == '\0') {
      break;
    }

  }

  return sum_priorities;
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
  printf("Result #1: %zu\n", first(input_first));

  char * input_second = read("inputs/03_test.txt");
  printf("Result #2: %d\n", second(input_second));

  free(input_first);
  free(input_second);
}
