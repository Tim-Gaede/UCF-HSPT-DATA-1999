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
/* Problem Name: Eugene And The Supremes                                   */
/* Filename: RATS                                                          */
/*                                                                         */
/* Specification by: Phillip Dexheimer                                     */
/* Judge Solution and Data by: Jason Daly                                  */
/*                                                                         */
/***************************************************************************/


#include <stdio.h>
#include <string.h>
#include <math.h>

FILE *infile;  /* Input file */

int  numRats;
char rats[30][16];
int  reps[30];

int  supremeRat;
int  supremeRep;



void checkSupreme(void)
{
    int maxrep;
    int index;
    int count;
    int i;

    maxrep = 0;
    count  = 0;
    index  = 0;

    if (numRats == 0)
    {
	/* Special case:  No rats, so no Supreme Rat */
	supremeRat = -1;
	supremeRep = 0;
    }
    else
    {
	if (numRats == 1)
	{
	    /* Special case:  One rat, so automagically Supreme */
	    supremeRat = 0;
	    supremeRep = reps[0];
	}
	else
	{
	    for (i=0; i<numRats; i++)
	    {
		if (abs(reps[i]) > abs(maxrep))
		{
		    maxrep = reps[i];
		    index = i;
		    count = 1;
		}
		else
		{
		    if (abs(reps[i]) == abs(maxrep))
			count++;
		}
	    }

	    if (count > 1)
	    {
		/* No Supreme Rat, but we'll record maxrep as
		   the rep to beat to be Supreme */
		supremeRat = -1;
		supremeRep = maxrep;
	    }
	    else
	    {
		/* The Supreme Rat is . . . */
		supremeRat = index;
		supremeRep = reps[index];
	    }
	}
    }
}

void laud( char *rat1, char *rat2)
{
    int index1, index2;
    int i;

    /* First, find the indices of the two rats */
    index1 = 0;
    while (strcmp(rats[index1], rat1) != 0)
	index1++;

    index2 = 0;
    while (strcmp(rats[index2], rat2) != 0)
	index2++;

    /* Next check to see if we're lauding the Supreme Rat */
    if (index2 == supremeRat)
	reps[index1] += 2;
    else
    {
	reps[index1] -= 1;
	reps[index2] += 3;
    }

    /* Finally, check to see if we have a new Supreme Rat, or
       if we've deposed the current Supreme Rat */
    checkSupreme();
}

void slander(char *rat1, char *rat2)
{
    int index1, index2;
    int i;

    /* First, find the indices of the two rats */
    index1 = 0;
    while (strcmp(rats[index1], rat1) != 0)
	index1++;

    index2 = 0;
    while (strcmp(rats[index2], rat2) != 0)
	index2++;

    /* Next check to see if we're slandering the Supreme Rat */
    if (index2 == supremeRat)
	reps[index1] -= 2;
    else
    {
	reps[index1] += 1;
	reps[index2] -= 3;
    }

    /* Finally, check to see if we have a new Supreme Rat, or
       if we've deposed the current Supreme Rat */
    checkSupreme();
}

void supreme(void)
{
    if (supremeRat != -1)
	printf("%s is the Supreme Rat\n", rats[supremeRat]);
    else
	printf("There is no Supreme Rat\n");
}

void sortRats(char sortedRats[30][16], int sortedReps[30])
{
    int  i;
    int  n;
    int  exch;
    int  tempRep;
    char tempRat[16];

    /* First, a bubble sort based on rep */
    n = numRats;
    exch = 1;
    while (exch == 1)
    {
	exch = 0;
	for (i=0; i<n-1; i++)
	   if (sortedReps[i] > sortedReps[i+1])
	   {
	       tempRep = sortedReps[i];
	       sortedReps[i] = sortedReps[i+1];
	       sortedReps[i+1] = tempRep;
	       strcpy(tempRat, sortedRats[i]);
	       strcpy(sortedRats[i], sortedRats[i+1]);
	       strcpy(sortedRats[i+1], tempRat);
	       exch = 1;
	   }
	   n--;
    }

    /* Now, make a second pass based on name for the
       tied reputations */
    n = numRats;
    exch = 1;
    while (exch)
    {
	exch = 0;
	for (i=0; i<n-1; i++)
	    if ((sortedReps[i] == sortedReps[i+1]) &&
		(strcmp(sortedRats[i], sortedRats[i+1]) > 0))
	    {
		/* Don't need to swap reps since they're equal */
		strcpy(tempRat, sortedRats[i]);
		strcpy(sortedRats[i], sortedRats[i+1]);
		strcpy(sortedRats[i+1], tempRat);
		exch = 1;
	    }
	    n--;
    }
}

void print(void)
{
    char sortedRats[30][16];
    int  sortedReps[30];
    int  i;

    /* First, we need to make a temporary copy of the
       "rats" and "reps" arrays */

    for (i=0; i<numRats; i++)
    {
	strcpy(sortedRats[i], rats[i]);
	sortedReps[i] = reps[i];
    }

    /* Now, lets sort the arrays */
    sortRats(sortedRats, sortedReps);

    /* Finally, we just print them out */
    for (i=0; i<numRats; i++)
	printf("%s: %d\n", sortedRats[i], sortedReps[i]);
}


void executeInstructions(void)
{
    char t1[15];
    char t2[15];
    char t3[15];

    strcpy(t1, "");
    strcpy(t2, "");
    strcpy(t3, "");

    while (strcmp(t1, "END") != 0)
    {
	/* Read the next line of input */
	 fscanf(infile,"%s", t1);

	 if (!strcmp(t1, "SUPREME"))
	 {
	     supreme();
	     fscanf(infile,"\n");
	 }
	 else
	     if (!strcmp(t1, "PRINT"))
	     {
		 print();
		 fscanf(infile,"\n");
	     }
	     else
		 if (strcmp(t1, "END") != 0)
		 {
		     /* t1 is the name of the first rat in a
		      LAUD or SLANDER instruction.  We need to
		      read in t2 and t3 */

		     fscanf(infile," %s %s\n", t2, t3);

		     /* Now check t2 to see what t1 does to t3 */

		     if (!strcmp(t2, "LAUD"))
			 laud(t1, t3);
		     else
			 slander(t1, t3);
		 }
     }
}

void initReps(void)
{
    int i;

    for (i=0; i<numRats; i++)
	reps[i] = 0;

    /* Initialize the supreme rat, too */
    supremeRat = -1;
    supremeRep = 0;
}

void getRatNames(void)
{
    int i;

    for (i=0; i<numRats; i++)
    {
	fscanf(infile,"%s", &rats[i]);
	fscanf(infile,"\n");
    }
}

void main(void)
{
    int  sets;
    int  currentSet;

    infile = fopen("rats.in", "r");

    fscanf(infile, "%d\n", &sets);

    for (currentSet = 0; currentSet<sets; currentSet++)
    {
	fscanf(infile, "%d\n", &numRats);

	/* Reset all reputations to zero */
	initReps();

	/* Read the rats' names into the "rats" array */
	getRatNames();

	/* Check for Supreme Rat (special case of one rat) */
	checkSupreme();

	/* Now, process the actions of the rats */
	executeInstructions();
    }

    fclose(infile);
}