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
/* Problem Name: Dinner And A Movie                                        */
/* Filename: MOVIE                                                         */
/*                                                                         */
/* Specification by: Jason Daly                                            */
/* Judge Solution and Data by: Jonathan Kolb                               */
/*                                                                         */
/***************************************************************************/


#include <stdio.h>
#include <string.h>

struct TTime // our own struct to handle times
{
  int Hour, Minute;
};

void TimeBetween(TTime Time1, TTime Time2, TTime &Between)
// Get the amount of time elasped between two times, abd store it in Between
// If Time2 is before Time1, Between gets negative hours
{
  Between.Hour = Time2.Hour - Time1.Hour;
  Between.Minute = Time2.Minute - Time1.Minute;
  while(Between.Minute < 0)  // We can't have negative minutes
  {
    Between.Hour--;
    Between.Minute += 60;
  }
}

void AddMinutes(TTime Time1, int Minutes, TTime &NewTime)
// Get the new time after adding Minutes number of minutes to a time
// Correctly handles more than 60 minutes
{
  NewTime.Minute = Time1.Minute + Minutes;
  NewTime.Hour = Time1.Hour + NewTime.Minute / 60;
  NewTime.Minute %= 60;
}

void main()
{
  FILE *infile = fopen("movie.in", "r");
  int numSets, i, waitMins, numMovies, j;
  TTime OffWork, Movies[20], Temp;
  char buf[100], *p, hours[20], minutes[20];

  fscanf(infile, "%d\n", &numSets);
  for(i=0; i<numSets; i++)
  {
    numMovies = 0;
    fscanf(infile, "%d:%d\n", &OffWork.Hour, &OffWork.Minute); // When do we get off work?
    fscanf(infile, "%d\n", &waitMins); // How long to wait a the restaurant?
    fgets(buf, sizeof(buf), infile); // Read in all the movie times
    p = strtok(buf, " \n"); // Get the first movie time ready
    while(p) // Parse the movie times
    {
      sscanf(p, "%d:%d", &Movies[numMovies].Hour, &Movies[numMovies].Minute);
      TimeBetween(Movies[0], Movies[numMovies], Temp);
/* remember, 24 hour period means 24 hours from the start of the first film.
   we *can* spill over into tomorrow.  if this is the case, the time of day
   for tomorrow's films will have to be earlier in the day than the time of
   day of the first film. */
      if(Temp.Hour < 0)  // was the new time earlier in the day tomorrow?
        Movies[numMovies].Hour += 24;
      numMovies++;
      p = strtok(NULL, " \n");
    }
    AddMinutes(OffWork, waitMins, Temp); // Waiting at the restaurant
    AddMinutes(Temp, 57, OffWork); // Eating
    for(j=0; j<numMovies; j++)
    {
      TimeBetween(OffWork, Movies[j], Temp);
      if (Temp.Hour >= 0)
        break; // We found a movie we can go to!  Get out of the loop!
    }
    if(j == numMovies)  // This should never happen, but it's a good idea anyway
      j--;
    Movies[j].Hour %= 24; // Pretty up the hours to print them
    if (Movies[j].Hour == 0)
      Movies[j].Hour = 24;
    printf("%d:%02d, you have ", Movies[j].Hour, Movies[j].Minute);
    if (Temp.Hour != 1) // hour vs. hours, which to print?
      strcpy(hours, "hours");
    else
      strcpy(hours, "hour");
    if(Temp.Minute != 1) // minute vs. minutes, which to print?
      strcpy(minutes, "minutes");
    else
      strcpy(minutes, "minute");
    if (Temp.Hour > 0)
      if (Temp.Minute > 0)
        printf("%d %s and %d %s\n\n", Temp.Hour, hours, Temp.Minute, minutes);
      else
        printf("%d %s\n\n", Temp.Hour, hours);
    else
    {
      printf("%d %s", Temp.Minute, minutes);
      if (Temp.Minute < 20) // with *less than* 20 minutes, print hurry up!
        printf(", hurry up!\n\n");
      else
        printf("\n\n");
    }
  }
  fclose(infile);
}
