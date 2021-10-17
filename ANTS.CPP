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
/* Problem Name: Ants                                                      */
/* Filename: ANTS                                                          */
/*                                                                         */
/* Specification by: Ambrose Feinstein                                     */
/* Judge Solution and Data by: Michael Kujawa                              */
/*                                                                         */
/***************************************************************************/


#include <stdio.h>
#include <stdlib.h>

/* Ants
   This is a simple geometry problem, which means it is simple if you know
   the rules and formulas needed to solve it (otherwise it is impossible.)
   Simply put, the problem is to test if three sides can form a triangle,
   and if so, test if they can form a right triangle.
*/

/* First, a couple of utility functions. */

/* sqr
   Computes tthe square of an integer.  Remember that for input ranging
   from 1 to 32000, the input squared ranges from 1 to 1,024,000,000!
   This result can not fit in a 16 bit int.
*/

#define bool int
#define true 1
#define false 0

unsigned long sqr(int a)
{
    return (unsigned long)a * (unsigned long)a;
}

/* Swap
   Swaps the values of two integers.  This is used to find and set the
   larger of the three side lengths.
*/
void Swap(int &a, int &b)
{
int c = a;
    a = b;
    b = c;
}





/* bIsRight
   bIsRight returns true if the three side lengths can construct a right
   triangle.  This is tested with the Pythagorean theorm: a triangle is a
   right triange if and only if the square of the length of the hypotoneuse
   is equal to the sum of the squares of the lengths of the other two sides.
*/
bool bIsRight(int a, int b, int c)
{
unsigned long ASquared, BSquared, CSquared;

    ASquared = sqr(a);
    BSquared = sqr(b);
    CSquared = sqr(c);

    return ASquared + BSquared == CSquared;
}




/* bIsTriangle
   bIsTriangle returns true if the three side lengths can construct a valid
   triangle.  A valid triangle MUST have area, so 1 1 2 can not construct
   a triangle, only a line segment.

   Three side lengths can construct a triangle if the longest side is shorter
   than the sum of the other two lengths.
   Remember that the sum of two signed 16 bit integers can exceed the storage
   capacity of a signed 16 bit int, so I take the parameters as 32bit ints.
*/
bool bIsTriangle(long a, long b, long c)
{
    return (a + b > c);
}





/* DoSet
   Process a single input set which consists of three integers to be tested
   for triangle-ness.
*/
void DoSet(int a, int b, int c)
{
    if (a > c)
        Swap(a, c);
    if (b > c)
        Swap(b, c);

    if (bIsTriangle(a,b,c))
    {
        if (bIsRight(a,b,c))
            printf("A right triangle can be constructed.\n");
        else
            printf("A triangle can be constructed.\n");
    }
    else
        printf("No triangle can be constructed.\n");
}





void main()
{
FILE *F;
int a,b,c;
int set, N;

    F = fopen("ants.in", "r");
    fscanf(F, "%d", &N);

    for (set=0; set < N; set++)
    {
        fscanf(F, "%d %d %d", &a, &b, &c);
        DoSet(a,b,c);
    }

    fclose(F);
}
