#include "lib/lib.h"


#include <stdio.h>
#include <stdbool.h>
#include <string.h>


struct file {
  char * name;
  size_t size;
  struct file * next;
};


struct dir {
  char * name;
  struct dir * parent;
  struct dir * children;
  struct file * files;
  struct dir * next;
};


char *
str_seek(char * str_p, char * chars)
{
  for(;;str_p++) {

    if (*str_p == '\0') {
      return str_p;
    }

    char * chars_p = chars;
    for(;*chars_p != '\0'; chars_p++) {
      if (*str_p == *chars_p) {
        return str_p;
      }
    }
  }
}


bool
str_prefix(char * str, const char * prefix)
{
  for (;*prefix != '\0';prefix++,str++) {
    if (*str != *prefix) {
      return false;
    }
  }
  return true;
}


void
dir_append_child(struct dir * parent, struct dir * child)
{
  if (parent->children == NULL) {
    parent->children = child;
  } else {
    struct dir * last_child = parent->children;
    for(;;) {
      if (last_child->next == NULL) {
        break;
      }
      last_child = last_child->next;
    }
    last_child->next = child;
  }
  child->parent = parent;
}


void
dir_append_file(struct dir * dir, char * name, size_t size)
{
  struct file * file = malloc(sizeof(struct file));
  size_t len_name = strlen(name);
  file->name = malloc(len_name);
  strncpy(file->name, name, len_name);
  file->size = size;
  if (dir->files == NULL) {
    dir->files = file;
  } else {
    struct file * last_file = dir->files;
    while(last_file->next != NULL) {
      last_file = last_file->next;
    }
    last_file->next = file;
  }
}


struct dir *
dir_create(char * name, size_t len_name)
{
    struct dir * dir = malloc(sizeof(struct dir));

    dir->name = malloc(len_name+1);
    strncpy(dir->name, name, len_name);
    dir->name[len_name] = '\0';

    return dir;
}


void
dir_print_rec(struct dir * dir, size_t indent)
{

  printf("%*s- %s (dir)\n", (int)indent, "", dir->name);

  struct dir * child = dir->children;
  for(;child != NULL;child=child->next) {
    dir_print_rec(child, indent+2);
  }
  for(struct file * file = dir->files;file != NULL;file=file->next) {
    printf(
      "%*s- %s (file, size=%zu)\n",
      (int)indent+2,
      "",
      file->name,
      file->size
    );
  }
}


void
dir_print(struct dir * dir)
{
  dir_print_rec(dir, 0);
}


void
cmd_cd(char * start, char * end, struct dir * root, struct dir ** current)
{
  char * name_start = start+3;
  char * name_end = str_seek(name_start, "\n");

  if (str_prefix(name_start, (*current)->name)) {
    return;
  }

  if (str_prefix(name_start, "..")) {
    *current = (*current)->parent;
  } else {
    struct dir * new_dir = dir_create(name_start, name_end-name_start);
    dir_append_child(*current, new_dir);
    *current = new_dir;
  }
}


void
cmd_ls(char * start, char * end, struct dir * root, struct dir ** current)
{
  size_t size_buf_name = 256;
  char name[size_buf_name];
  memset(name, 0, sizeof(char) * size_buf_name);

  start += 3; // Skip initial <ls > part.
  for(;;) {
    char * end_line = str_seek(start, "\n$");

    if (*end_line == '$' || *end_line == '\0') {
      break;
    }

    if (!str_prefix(start, "dir ")) {
      size_t size_file = strtoul(start, &start, 10);
      start++;
      char * name_p = name;
      for(;*start != '\n';start++) {
        *name_p++ = *start;
      }
      *name_p = '\0';
      dir_append_file(*current, name, size_file);
    }

    start = end_line+1;
  }
}


char *
consume_next(char * input, struct dir * root, struct dir ** current)
{
  char * start = input;
  char * end = str_seek(start+1, "$");

  char * start_cmd = start+2;

  if (str_prefix(start_cmd, "cd")) {
    cmd_cd(start_cmd, end, root, current);
  } else if(str_prefix(start_cmd, "ls")) {
    cmd_ls(start_cmd, end, root, current);
  } else {
    fprintf(stderr, "No command matching %.*s\n", (int)(end-start), start);
  }

  return end;
}


struct dir
dir_from_input(const char * path_input)
{
  char * input = read(path_input);
  char * char_p = input;

  struct dir root = {.name = "/"};
  struct dir * current = &root;

  while (*char_p != '\0') {
    char_p = consume_next(char_p, &root, &current);
  }

  free(input);
  return root;
}


size_t
sum_dir_sizes(struct dir * dir)
{
  size_t sum_files = 0;

  for (struct file * file=dir->files; file != NULL; file=file->next) {
    sum_files += file->size;
  }

  size_t sum_children = 0;
  for (struct dir * child=dir->children; child != NULL; child=child->next) {
    sum_children += sum_dir_sizes(child);
  }

  size_t sum_this_dir = sum_files + sum_children;

  if (sum_this_dir < 100000) {
    return sum_this_dir + sum_children;
  } else {
    return sum_children;
  }
}


void
first(void)
{
  struct dir root = dir_from_input("inputs/07_test.txt");
  dir_print(&root);
  printf("sum: %zu\n", sum_dir_sizes(&root));
}


int
main(void)
{
  first();
}
