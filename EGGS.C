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
/* Problem Name: Hatching Lizards                                          */
/* Filename: EGGS                                                          */
/*                                                                         */
/* Specification by: Sandra Powers                                         */
/* Judge Solution and Data by: Glenn Martin                                */
/*                                                                         */
/***************************************************************************/


#include <stdio.h>
#include <string.h>

void main()
{
   FILE     *infile;
   char     line[80];
   int      numClutches;
   int      i;
   int      numEggs;
   char     season[80];
   double   hatchingRate;
   double   survivalRate;
   int      numHatched;
   int      numSurvived;

   /* Open the input file */
   infile = fopen("eggs.in", "r");

   /* Read the number of data sets (number of clutches) */
   fgets(line, 79, infile);
   sscanf(line, "%d", &numClutches);

   /* Process each clutch */
   for (i=0; i < numClutches; i++)
   {
      /* Get the number of eggs in the clutch and what season it is */
      fgets(line, 79, infile);
      sscanf(line, "%d %s", &numEggs, season);

      /* Figure out the hatching rate based the number of eggs */
      if (numEggs <= 50)
	 hatchingRate = 0.55;
      else if ( (numEggs >= 51) && (numEggs <= 100) )
	 hatchingRate = 0.70;
      else if (numEggs > 100)
	 hatchingRate = 0.20;

      /* Figure out survival rate depending on season */
      if (season[strlen(season)-1] == '*')
	 survivalRate = 0.90;
      else if (strcmp(season, "spring") == 0)
	 survivalRate = 0.75;
      else if (strcmp(season, "summer") == 0)
	 survivalRate = 0.50;
      else if (strcmp(season, "fall") == 0)
	 survivalRate = 0.25;
      else if (strcmp(season, "winter") == 0)
	 survivalRate = 0.10;

      /* Figure out how many hatch and how many of those survive           */
      /* We need to be careful with floating-point error so add an epsilon */
      numHatched = hatchingRate * numEggs + 1e-5;
      numSurvived = survivalRate * numHatched + 1e-5;

      /* Write the output */
      printf("Clutch #%d: %d surviving lizards\n", i+1, numSurvived);
   }

   /* Close the input file */
   fclose(infile);
}