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
/* Problem Name: Wheebop!                                                  */
/* Filename: ROBOTS                                                        */
/*                                                                         */
/* Specification by: Eric Heimburg                                         */
/* Judge Solution and Data by: Phillip Dexheimer                           */
/*                                                                         */
/***************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//As a rule, I hate global variables.  However, they sure do simplify things
char curline[80]; //The current line straight from the input file
char words[110][80]; //The parsed and separated words in the current sentence
int nWords; //The number of words in the current sentence
FILE *In; //The input file
int nReverse; //counts consecutive words with an 'a' or 'e'

//This is the function that actually does the work.
//It is called when curline contains the next line of input.  Note that a new
//line of input does not mean a new sentence.
void BreakLine()
{
 char *p, *q;//Two char *'s to step through curline.
 //p will point to the beginning of the current word, while q will point to the
 //end
 p = curline;
 q = curline;
 while (q && *q) //The safest terminating condition for this kind of step
  {
   if (strchr(" \n.!?", *q))//checks to see if q is pointing at a word delimiter
    {
     //This checks for words of no length (eg, between a period and a newline)
     if (q == p)
      {
       printf ("%c", *q);
       q++;
       p++;
       continue; //word with no characters
      }
     //The hideous abbreviation hack
     //If the word delimiter is a period, check to see if there's another
     //delimiter in the next space.
     if ((*q == '.') && (strchr(" \n.!?", *(q+1))))
      {
       //If there is, then it's eligible to be an abbreviation.
       if ((!strncmp(p, "Mr", q-p)) || (!strncmp(p, "Mrs", q-p)) ||
	   (!strncmp(p, "Ms", q-p)) || (!strncmp(p, "Dr", q-p)) ||
	   (!strncmp(p, "Sr", q-p)) || (!strncmp(p, "Jr", q-p)))
	 q++;//If it's an abbreviation, the period is part of the word
      }
     //Copy the word into it's place in the array
     memset (words[nWords], 0, sizeof(words[nWords]));
     strncpy (words[nWords], p, q-p);

     p = q+1; //Increment p to the start of the next word

     //Check to see if the current word has an 'a' or an 'e'.  If it does,
     //the number of contiguous words should be incremented.  Else, it
     //should be set back to zero
     if ((strchr(words[nWords], 'a')) || (strchr(words[nWords], 'A')) ||
     				  (strchr(words[nWords], 'e')) || (strchr(words[nWords], 'E')))
        nReverse++;
     else
        nReverse = 0;

     nWords++;
	  //print the word, with whatever transformations are necessary
     if (nWords > 10)
      {
       printf("%s", words[nWords-11]);
       printf ("%c", *q);
      }
     else if ((nWords == 1) && (strchr(".!?", *q)))
       printf("Wheebop!");
     else if (nReverse >= 8)
      {
       char tempword[80];
       strcpy (tempword, words[nWords-1]);
       printf("%s", strrev(tempword));
       printf ("%c", *q);
      }
     else
      {
       printf("%s", words[nWords-1]);
       printf ("%c", *q);
      }
     //If the word delimiter was a sentence ender, then reset everything for
     //the new sentence
     if (strchr(".!?", *q))
      {
       nWords = 0;
       nReverse = 0;
      }
    }
   //Check the next character
   q++;
  }
}

//the main function isn't complicated.  It reads input one line at a time
//(fgets() retains the carriage return to simplify things later on)
//and then calls BreakLine() to parse out the words and print the output
void main ()
{
 In = fopen ("robots.in", "r");
 nWords = 0;
 nReverse = 0;
 while (!feof(In))
  {
   if (fgets(curline, 75, In))
     BreakLine();
  }
 fclose (In);
}