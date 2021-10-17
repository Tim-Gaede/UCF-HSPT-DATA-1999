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
/* Problem Name: Inspector Doohickey                                       */
/* Filename: MAZE                                                          */
/*                                                                         */
/* Specification by: Eric Heimburg                                         */
/* Judge Solution and Data by: Sandra Powers                               */
/*                                                                         */
/***************************************************************************/


/* The easiest way to solve a problem like this is with a recursive depth-first
   search. At each position, you check to see if you have reached your goal. If 
   not, you mark where you are as having been visited (because you don't want 
   to come back and try again) and then you try to move in some direction. If 
   you can move, you do so and repeat the process for that position. If you 
   can't move in that direction, you try another direction. If you get to a 
   position where you can't move at all, you back up along your path until you 
   can move to some unvisited spot and you go on. By the time the original call
   of the recursive function in the main program returns, you will have hit 
   every spot in the maze. Of course, in this program we optimize so that when 
   we find the right spot we stop trying. It's a long, arduous process for the 
   computer (not really, but it can be if the array is too big) but a relatively
   short program to write for the programmer. */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/* these things are global so you can reference them in the recursive function
   without having to pass them */

char Maze[10][10];              /* holds the characters from input */
int Visited[10][10];            /* keeps track of where you have been so far */
char Path[200];                 /* holds the path of directions */
int going,                      /* works as a flag to tell you whether you are
                                   going in or out: 0 means going in, 1 means 
                                   going out */
    gone;                       /* works as a flag in the recursive Move() 
                                   function; if gone = 1 you've found and 
                                   printed your path, so stop looking */

void main(void)
{
	FILE * ifp;                 /* input file  */
	int nMazes,                 /* number of mazes total */
            i, j, k,                /* i = number maze you are on now; 
                                       j & k = counters for running through the 
                                       matrices */
            Ij, Ik,                 /* starting position of Liver */
            Oj, Ok;                 /* starting position of the Inspector */

	void Move(int a, int b);    /* recursive function defined below */

        /* open the file and read in the number of mazes */
	ifp = fopen("maze.in", "r");    
	fscanf(ifp, "%d\n", &nMazes);

        /* for each of the mazes, do all this stuff */
	for (i = 0; i < nMazes; i++)
	{
        /* set the Path and Visited matrix all to 0 and initialize the flags */
		memset(Path, 0, sizeof(Path));
		memset(Visited, 0, sizeof(Visited));
		going = 0;
		gone = 0;

        /* print out the header for this maze */
		printf("Maze #%d\n", i+1);

        /* read in the input */
		for (j = 0; j < 10; j++)
		{
			for (k = 0; k < 10; k++)
			{
				fscanf(ifp, "%c", &Maze[j][k]);

                /* take note of the position of Liver and the Inspector */
				if (Maze[j][k] == 'L')
				{
					Ik = k;
					Ij = j;
                } /* end of if == 'L' */
				else if (Maze[j][k] == 'I')
				{
					Ok = k;
					Oj = j;
                } /* end of if == 'I' */

                /* or if it's a wall set Visited (since you can't ever go into
                   a wall space, it counts as having been visited) */
				else if (Maze[j][k] == 'W')
					Visited[j][k] = 1;
            } /* end of for that reads in a single line of input */

            /* remember to scan in the \n at the end of each line */
			fscanf(ifp, "\n");
		}

        /* because of the way Move() is set up, you have to set where you 
           currently are as visited before you call move the first time */
		Visited[Ij][Ik] = 1;

        /* find the path from Liver to the Inspector */
		Move(Ij, Ik);

        /* clean up Visited so that only the original walls are marked as 1 */
        for (j = 0; j < 10; j++)
            for (k = 0; k < 10; k++)
            {
                if (Maze[j][k] == 'W')
					Visited[j][k] = 1;
                else Visited[j][k] = 0;
            }


        /* reset the flags; going = 1 now because you are on your way out */
        going = 1;
		gone = 0;

        /* just like above */
        Visited[Oj][Ok] = 1;

        /* find the path from the Inspector to the exit */
	Move(Oj, Ok);
	printf("\n");

    } /* end of outside for loop (for each maze) */

    /* be neat, close your file */
    fclose(ifp);
} /* end of main() */

void Move(int a, int b)
{

    /* if we already have a solution, don't waste time trying more paths, 
       just return */
	if (gone) return;

    /* if you are on your way in and find the Inspector, or on your way out 
       and find the exit, print the path, set gone to show that you are done, 
       and return */
	if ((Maze[a][b] == 'I' && going == 0) || (Maze[a][b] == 'X' && going == 1))
	{
		printf("%s\n", Path);
        gone = 1;
		return;
	}

    /* try each direction - note that before going in a direction you must 
       check if it is still on the 10x10 map and that it hasn't already been 
       visited; since we set the wall spaces as visited when we read in the 
       input, we don't have to explicitly check for that */

    if (a+1 < 10 && Visited[a+1][b] != 1)
	{
        /* add the appropriate direction to the Path string and set Visited 
           for the spot we are about to move to */
		Path[strlen(Path)] = 'S';
		Visited[a+1][b] = 1;

        /* recursively move */
		Move(a+1, b);

        /* when you return from the above Move() call, either you have found 
           the path and printed it and you're done, or you haven't and going 
           this was leads to a dead end; either way remove the direction from 
           the Path string */
		Path[strlen(Path)-1] = '\0';
    } /* end if able to go S */

	if (!gone && b+1 < 10 && Visited[a][b+1] != 1)
	{
		Path[strlen(Path)] = 'E';
		Visited[a][b+1] = 1;
		Move(a, b+1);
		Path[strlen(Path)-1] = '\0';
    } /* end if able to go E */

	if (!gone && a-1 >= 0 && Visited[a-1][b] != 1)
	{
		Path[strlen(Path)] = 'N';
		Visited[a-1][b] = 1;
		Move(a-1, b);
		Path[strlen(Path)-1] = '\0';
    } /* end if able to go N */

	if (!gone && b-1 >= 0 && Visited[a][b-1] != 1)
	{
		Path[strlen(Path)] = 'W';
		Visited[a][b-1] = 1;
		Move(a, b-1);
		Path[strlen(Path)-1] = '\0';
    } /* end if able to go W */

    /* if there were no guaranteed path, we might have to do something else 
       here; but we are guaranteed a solution */
	return;

} /* end of Move() */