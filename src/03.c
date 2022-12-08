#include <string.h>


#include "lib/lib.h"


#define NUM_PACKS_IN_GROUPSACK 3


struct slice {
  size_t size;
  const char * start;
};


struct rucksack {
  struct slice compartment_1;
  struct slice compartment_2;
  char common;
  int priority;
};


void
slice_print(struct slice * slice)
{
  printf("%.*s", (int)slice->size, slice->start);
}


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


struct groupsack {
  struct slice compartments[3];
  char common;
  int priority;
};


char
find_first_matching_3(struct slice * a, struct slice * b, struct slice * c)
{
  for (size_t ii=0; ii<a->size; ii++) {
    for (size_t jj=0; jj<b->size; jj++) {
      for (size_t kk=0; kk<c->size; kk++) {
        if (a->start[ii] == b->start[jj] && b->start[jj] == c->start[kk]) {
          return a->start[ii];
        }
      }
    }
  }
  return '!';
}


void
groupsack_next(char ** input, struct groupsack * groupsack)
{

  char * start = *input;
  char * end = start;

  size_t counter_packs = 0;

  for (;;end++) {
    if (*end == '\n') {
      end++;
      groupsack->compartments[counter_packs].start = start;
      groupsack->compartments[counter_packs].size = end-start;
      start = end;
      counter_packs++;
    }
    if (counter_packs == NUM_PACKS_IN_GROUPSACK) {
      break;
    }
  }

  groupsack->common = find_first_matching_3(
    &groupsack->compartments[0],
    &groupsack->compartments[1],
    &groupsack->compartments[2]
  );

  groupsack->priority = item_priority(groupsack->common);

  *input = end;
}


void
groupsack_print(struct groupsack * groupsack)
{
  printf("%s\n", "Contents:");

  for (int ii=0; ii<NUM_PACKS_IN_GROUPSACK; ii++) {
    printf("%s", "  ");
    slice_print(&groupsack->compartments[ii]);
  }

  printf("Common: %c\n", groupsack->common);
  printf("Priority: %d\n", groupsack->priority);

  printf("%s", "\n");
}


int
second(char * input)
{
  struct groupsack groupsack = {0};
  size_t sum_priorities = 0;

  for (;;) {

    groupsack_next(&input, &groupsack);
    groupsack_print(&groupsack);

    sum_priorities += groupsack.priority;

    if (*input == '\0') {
      break;
    }
  }

  return sum_priorities;
}


int
main(void)
{
  char * input_first = read("inputs/03.txt");
  printf("Result #1: %zu\n", first(input_first));

  char * input_second = read("inputs/03.txt");
  printf("Result #2: %d\n", second(input_second));

  free(input_first);
  free(input_second);
}
