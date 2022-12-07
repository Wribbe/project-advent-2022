#include "lib/lib.h"

char *
read(const char * path)
{
  FILE * handle_file = fopen(path, "r");
  if (handle_file == NULL) {
    fprintf(stderr, "Could not open given path: %s", path);
    return NULL;
  }

  fseek(handle_file, 0, SEEK_END);
  size_t size_buffer = ftell(handle_file);
  rewind(handle_file);

  char * buffer = malloc(size_buffer+1);
  if (buffer == NULL) {
    fprintf(stderr, "%s", "Could not allocate enough memory to read file.");
    return NULL;
  }

  size_t size_read = 0;
  while (size_read < size_buffer) {
    size_read += fread(buffer+size_read, 1, size_buffer-size_read, handle_file);
  }

  buffer[size_buffer] = '\0';

  return buffer;
}


void
slice_print(struct slice * slice)
{
  printf("%.*s", (int)slice->size, slice->start);
}
