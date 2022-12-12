#include "lib/lib.h"

#include <stdio.h>
#include <stdbool.h>


// -----------------------------------------------------------------------------
// Shared
// -----------------------------------------------------------------------------


#define LEN(x) sizeof(x)/sizeof(x[0])


struct test_data {
  const char * input;
  size_t correct_result;
};


bool
duplicate_chars_in_window(char * start, char * end)
{
  for (char * temp_end = end; temp_end > start; temp_end--) {
    for (char * temp_start = start; temp_start < temp_end; temp_start++) {
      if (*temp_start == *temp_end) {
        return true;
      }
    }
  }
  return false;
}


size_t
start_of_package(const char * input)
{
  char * start = (char *)input;
  char * end = start+4;

  for (;;start++,end++) {

    if (*end == '\0') {
      break;
    }

    size_t pos_window_start = start-input;
    size_t pos_window_end = pos_window_start+4;

    if (duplicate_chars_in_window(start, end)) {
      printf(
        "Current window @ [%zu,%zu]: %.4s, contains duplicates, continuing.\n",
        pos_window_start,
        pos_window_end,
        start
      );
      continue;
    }
    return pos_window_end;
  }

  return 0;
}




// -----------------------------------------------------------------------------
// Part I
// -----------------------------------------------------------------------------


void
test_1(void)
{
  struct test_data test_data[] = {
    {"mjqjpqmgbljsphdztnvjfqwrcgsmlb", 7},
    {"bvwbjplbgvbhsrlpgdmjqwftvncz", 5},
    {"nppdvjthqldpwncqszvftbrmjlhg", 6},
    {"nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg", 10},
    {"zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw", 11},
  };

  for (size_t ii=0; ii<LEN(test_data); ii++) {
    printf("input: %s\n", test_data[ii].input);
    size_t result = start_of_package(test_data[ii].input);
    printf("expected: %zu, received: %zu\n", test_data[ii].correct_result, result);
  }
}


void
first(void)
{
  test_1();

  char * input_1 = read("inputs/06.txt");
  printf(
      "answer_1: Number of processed chars before start-of-packet: %zu\n",
      start_of_package(input_1)
  );
  free(input_1);
}

// -----------------------------------------------------------------------------
// Part II
// -----------------------------------------------------------------------------

void
test_2(void)
{
  struct test_data test_data[] = {
    {"mjqjpqmgbljsphdztnvjfqwrcgsmlb", 19},
    {"bvwbjplbgvbhsrlpgdmjqwftvncz", 23},
    {"nppdvjthqldpwncqszvftbrmjlhg", 23},
    {"nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg", 29},
    {"zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw", 26},
  };

  for (size_t ii=0; ii<LEN(test_data); ii++) {
    printf("input: %s\n", test_data[ii].input);
    size_t result = start_of_package(test_data[ii].input);
    printf("expected: %zu, received: %zu\n", test_data[ii].correct_result, result);
  }
}


void
second(void)
{
  test_2();

//  char * input_1 = read("inputs/06.txt");
//  printf(
//      "answer_1: Number of processed chars before start-of-packet: %zu\n",
//      start_of_package(input_1)
//  );
//  free(input_1);
}

// -----------------------------------------------------------------------------
// Main
// -----------------------------------------------------------------------------


int
main(void)
{
  first();
  second();
}
