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
/* Problem Name: Too Many Keys                                             */
/* Filename: KEYS                                                          */
/*                                                                         */
/* Specification by: Michael Kujawa                                        */
/* Judge Solution and Data by: Michael Kujawa                              */
/*                                                                         */
/***************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define bool int
#define true 1
#define false 0

/* TKey
   A structure holding the tenants name and the cuts in the key.  There are
   eight notch sites, and these are numbered as follows

          111
     02468024
   =#--------######O
     13579111
          135

   Note that the name is stored with a colon appended to it to simplify
   formatting the output later.

   Cuts could have simply been a 16-bit integer.  Very simple bit-wise math
   could then be used to check one key against another, but for ease of
   understanding, I do it the more obvious, bit-by-bit, way.
*/
struct TKey
{
    char Name[20];
    bool Cuts[16];
};

TKey Keys[1000];  /* Keys in this data set */
int nKeys;        /* the number of keys in "Keys" */



/* ReadKey
   ReadKey processes the middle line in the ASCII art for a key and
   reads the 16 cuts into the "Cuts" array.
*/
void ReadKey(char *Inp, TKey &Key)
{
    for (int i=2; i < 10; i++)
    {
    int cut = (i-2)*2;
        switch (Inp[i])
        {
            case '-':
                Key.Cuts[cut] = true;
                Key.Cuts[cut+1] = true;
                break;
            case '.':
                Key.Cuts[cut] = true;
                Key.Cuts[cut+1] = false;
                break;
            case '"':
                Key.Cuts[cut] = false;
                Key.Cuts[cut+1] = true;
                break;
            case '#':
                Key.Cuts[cut] = false;
                Key.Cuts[cut+1] = false;
                break;
        }
    }
}





/* bCanOpen
   BCanOpen returns true if "KeyToCheck" can open the door designed for
   "CorrectKey" (KeyToCheck and CorrectKey are indices into "Keys".)

   This is done by looping through all the possible cuts, and if a cut
   is present on the correct key, making sure it is present on the key
   to check.

   Bitwise, we are checking that
   PatternToCheck AND CorrectPattern = CorrectPattern.
*/
bool bCanOpen(int KeyToCheck, int CorrectKey)
{
bool bOk = true;

    for (int cut=0; cut < 16; cut++)
        if (Keys[CorrectKey].Cuts[cut] && !Keys[KeyToCheck].Cuts[cut])
            bOk = false;
    return bOk;
}





/* CheckKey
   Returns the number of doors that Keys[idx] can open other than its own.
   This is done by caling "bCanOpen" for all keys (besides idx.)
*/
int CheckKey(int idx)
{
int nWrongKeys = 0;

    for (int i=0; i < nKeys; i++)
        if (i != idx)
            if (bCanOpen(idx, i))
                nWrongKeys++;
    return nWrongKeys;
}





/* DoSet
   Reads in the keys for a set then generates the output; it does a single
   set.
*/
void DoSet(FILE *F)
{
int i;
char st[256];

    /* Read the input.  Note that the names are stored with a colon */
    for (i=0; i < nKeys; i++)
    {
    char *p;
        fgets(Keys[i].Name, 256, F);
        p = strchr(Keys[i].Name, '\n');
        if (p) *p = 0;

        strcat(Keys[i].Name, ":");
        fgets(st, 256, F);
        fgets(st, 256, F);
        ReadKey(st, Keys[i]);
        fgets(st, 256, F);
    }

    /* Generate the output.  Now the name is just printed in 16 characters */
    for (i=0; i < nKeys; i++)
        printf("  %-16s %d\n", Keys[i].Name, CheckKey(i));
}




void main()
{
int Set = 0;
FILE *F;
char st[256];

    F = fopen("keys.in","r");

    fgets(st, 256, F);
    sscanf(st, "%d", &nKeys);
    while (nKeys > 0)
    {
        Set++;
        printf("Set #%d:\n", Set);
        DoSet(F);
        printf("\n");
        fgets(st, 256, F);
        sscanf(st, "%d", &nKeys);
    }

    fclose(F);
}
