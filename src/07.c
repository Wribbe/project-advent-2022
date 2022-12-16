#include "lib/lib.h"


#include <stdio.h>
#include <stdbool.h>

struct file {
  const char * name;
  size_t size;
};


struct dir {
  const char * name;
  struct dir * children;
  struct file * files;
};


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


struct dir
dir_from_input(const char * path_input)
{
  char * input = read(path_input);
  char * char_p = input;

  struct dir root = {
    .name = "/",
    .children = NULL,
    .files = NULL
  };

  while (*char_p != '\0') {
    char_p = consume_next(char_p);
  }

  free(input);
  return root;
}


void
first(void)
{
  struct dir root = dir_from_input("inputs/07_test.txt");
}


int
main(void)
{
  first();
}
