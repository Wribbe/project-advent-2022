#include <stdlib.h>
#include <stdio.h>


#include "lib/lib.h"


#define LEN(arr) sizeof(arr)/sizeof(arr[0])


// Their, Ours, Result.
// A: Rock, B: Paper, C: Scissors.
const char RULES[][3] = {
  {'A', 'B', 'W'},
  {'A', 'C', 'L'},
  {'B', 'A', 'L'},
  {'B', 'C', 'W'},
  {'C', 'A', 'W'},
  {'C', 'B', 'L'},
};


char
round_result(char their, char our)
{
  if (their == our) {
    return 'D';
  }

  for (int ii=0; ii<LEN(RULES); ii++) {
    if (their == RULES[ii][0] && our == RULES[ii][1]) {
      return RULES[ii][2];
    }
  }

  fprintf(stderr, "%s\n", "No rule matched!");
  return 'F';
}


int
score_round(char * round)
{

  int score_shape = 0;
  int score_result = 0;

  char their = *round;
  char our = *(round+2);

  switch (our) {
    case 'X':
    case 'A':
      score_shape = 1;
      our = 'A';
      break;
    case 'Y':
    case 'B':
      score_shape = 2;
      our = 'B';
      break;
    case 'Z':
    case 'C':
      score_shape = 3;
      our = 'C';
      break;
  }

  switch(round_result(their, our)) {
    case('W'):
      score_result = 6;
      break;
    case('D'):
      score_result = 3;
      break;
    case('L'):
      score_result = 0;
      break;
  }

  return score_shape + score_result;
}


int
first(char * input)
{
  int sum_score = 0;

  for(;;) {
    if (*input == '\0') {
      break;
    }
    sum_score += score_round(input);
    input += 4;
  }
  return sum_score;
}


void
rewrite_round_instruction(char * p_char)
{

  char their = p_char[0];
  char outcome = p_char[2];

  if (outcome == 'Y') { // Make it draw.
    p_char[2] = their;
    return;
  }

  char sought_outcome = (outcome == 'X') ? 'L' : 'W';

  for (int ii=0; ii<LEN(RULES); ii++) {

    char rules_their = RULES[ii][0];
    char rules_our = RULES[ii][1];
    char rules_outcome = RULES[ii][2];

    if (their != rules_their) {
      continue;
    }

    if (rules_outcome != sought_outcome) {
      continue;
    }

    p_char[2] = rules_our;
    return;

  }
}


char *
modify_input(char * input)
{
  char * p_char = input;

  for (;;) {
    rewrite_round_instruction(p_char);
    p_char += 4;
    if (*p_char == '\0') {
      break;
    }
  }
  return input;
}


int
second(char * input)
{
  return first(modify_input(input));
}


int
main(void)
{
  char * input_one = read("inputs/02.txt");
  printf("first: %d\n", first(input_one));

  char * input_two = read("inputs/02.txt");
  printf("second: %d\n", second(input_two));

  free(input_one);
  free(input_two);
}
