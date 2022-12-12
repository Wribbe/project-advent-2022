#include "lib/lib.h"


#include <stdio.h>
#include <stdbool.h>


char *
seek(char * str_p, char c)
{
  for(;;str_p++) {

    if (*str_p == '\0') {
      return str_p;
    }

    if (*str_p == c) {
      return str_p+1;
    }

  }
}


char *
consume_next(char * input)
{
  char * start = input;
  input = seek(input, '\n');

  printf("%.*s", (int)(input-start), start);

  return input;

}


void
first(void)
{
  char * input = read("inputs/07_test.txt");
  while (*input != '\0') {
    input = consume_next(input);
  }
}


int
main(void)
{
  first();
}
