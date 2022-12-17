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
str_seek(char * str_p, char c)
{
  char * start = str_p;
  for(;;str_p++) {

    if (*str_p == '\0') {
      return str_p;
    }

    if (*str_p == c && str_p != start) {
      return str_p;
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
  char * name_end = str_seek(name_start, '\n');

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
  printf("Processing ls\n");
}


char *
consume_next(char * input, struct dir * root, struct dir ** current)
{
  char * start = input;
  char * end = str_seek(start, '$');

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


void
first(void)
{
  struct dir root = dir_from_input("inputs/07_test.txt");
  printf("name root: %s\n", root.name);
  dir_print(&root);
}


int
main(void)
{
  first();
}
