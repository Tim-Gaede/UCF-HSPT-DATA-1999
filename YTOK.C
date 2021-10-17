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
/* Problem Name: The Y-to-K Problem                                        */
/* Filename: YTOK                                                          */
/*                                                                         */
/* Specification by: Phillip Dexheimer                                     */
/* Judge Solution and Data by: Ambrose Feinstein                           */
/*                                                                         */
/***************************************************************************/


/* ytok.c
 *
 * this program is very simple (although hard to see under all those
 * comments).  first it puts the input file on stdin, which makes reading
 * from it very convenient.  then it reads characters until it reaches
 * end of file.  for each character read, it translates it if necessary,
 * and then writes it to stdout.  newlines and other whitespace pass
 * through unchanged.
 */

#include <stdio.h> /* freopen(), getchar(), putchar() */

int main(){
  int c; /* int can hold all chars and -1 for eof */
  freopen("ytok.in","r",stdin); /* reuse stdin, since we dont want to read
				   from the keyboard anyway */
  while(EOF!=(c=getchar())){ /* get a character and test for eof */
    if(c=='y') c='k'; /* translate it if needed */
    if(c=='Y') c='K'; /* ... */
    putchar(c); /* write it to stdout */
  }
  /* loop broke from eof, all done writing */
  return 0; /* success!  leaving main should flush and close stdout for us */
}
