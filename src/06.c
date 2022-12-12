#include "lib/lib.h"

#include <stdio.h>


#define LEN(x) sizeof(x)/sizeof(x[0])


size_t
answer_1(const char * input)
{
  return 0;
}


int
main(void)
{

  struct test_data {
    const char * input;
    size_t correct_result;
  };

  struct test_data test_data[] = {
    {"bvwbjplbgvbhsrlpgdmjqwftvncz", 5},
    {"nppdvjthqldpwncqszvftbrmjlhg", 6},
    {"nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg", 10},
    {"zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw", 11},
  };

  for (size_t ii=0; ii<LEN(test_data); ii++) {
    printf("input: %s\n", test_data[ii].input);
    size_t result = answer_1(test_data[ii].input);
    printf("expected: %zu, received: %zu\n", test_data[ii].correct_result, result);
  }
}
