/***************************************************************************/
/*                      University of Central Florida                      */
/*                            Thirteenth Annual                            */
/*                    High School Programming Tournament                   */
/*                                                                         */
/*                              May 7, 1999                                */
/*                                                                         */
/*                                                                         */
/*                                                                         */
/*                                                                         */
/* Problem Name: These Aren't The Droids We're Looking For!                */
/* Filename: DROIDS                                                        */
/*                                                                         */
/* Specification by: Jason Daly                                            */
/* Judge Solution and Data by: Michael Kujawa                              */
/*                                                                         */
/***************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

int isaVowel(char c);
int isaLetter(char c);
int numberp(char c);
char ucase(char c);
int isaDroidName(char name[]);

/*****************************************************************************
 * main allocates memory for the names of the droids that will be entered,   *
 * gets them from the file, and determines if they are valid using the       *
 * isaDroidName function.  It produces output per the problem specification. *
 *****************************************************************************/
void main() {
  int numNames, count;
  char *p, name[80];
  FILE *F;

  F = fopen("droids.in", "r");

  fscanf(F, "%d\n", &numNames);
  for(count=0;count<numNames;count++) {
	fgets(name, sizeof(name), F);
	p = strchr(name, '\n'); 
	if (p) *p = 0;

	if(isaDroidName(name))
	  printf("%s:  We'll take this one.\n", name);
	else
	  printf("%s:  Hey! What are you trying to push on us?\n", name);
    puts("");
  }

  fclose(F);
}

char ucase(char c) {
  if((c <= 'z') && (c >= 'a')) return c -= 32;
  return c;
}

int isaVowel(char c) {
  switch(ucase(c)) {
  case 'A':
  case 'E':
  case 'I':
  case 'O':
  case 'U':
  case 'Y':
    return TRUE;
  default: return FALSE;
  }
}

int isaLetter(char c) {
  char uc;
  
  uc = ucase(c);
  if((uc <= 'Z') && (uc >= 'A')) return TRUE;
  return FALSE;
}

int numberp(char c) {
  if((c <= '9') && (c >= '0')) return TRUE;
  return FALSE;
}

/**************************************************************************
 * isaDroidName returns TRUE if name[] is a string representing a valid   *
 * droid name, FALSE otherwise.  The function checks that the string      *
 * obeys the first two rules outside of a loop, and then checks the       *
 * second two inside of a loop.                                           *
 **************************************************************************/
int isaDroidName(char name[]) {
  int count, group, length;

  group = 0;
  count = 0;
  length = strlen(name);

  if(length == 1) return FALSE;
  if(!(numberp(name[1]) || (name[1] == '-'))) return FALSE;
  if(!(numberp(name[length-1]) || isaVowel(name[length-1]))) return FALSE;

  while(count < length) {
    if(numberp(name[count]) || (name[count] == '-')) group = 0;
    else {
      if(isaLetter(name[count])) group++;
      else return FALSE;
    }
    if(group > 2) return FALSE;
    count++;
  }
  return TRUE;
}
