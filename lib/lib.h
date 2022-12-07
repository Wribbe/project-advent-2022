#include <stdlib.h>
#include <stdio.h>


struct slice {
  size_t size;
  const char * start;
};


char *
read(const char * path);


void
slice_print(struct slice * slice);
