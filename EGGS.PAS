(***************************************************************************)
(*                      University of Central Florida                      *)
(*                            Thirteenth Annual                            *)
(*                    High School Programming Tournament                   *)
(*                                                                         *)
(*                              May 7, 1999                                *)
(*                                                                         *)
(*                                                                         *)
(*                                                                         *)
(*                                                                         *)
(* Problem Name: Hatching Lizards                                          *)
(* Filename: EGGS                                                          *)
(*                                                                         *)
(* Specification by: Sandra Powers                                         *)
(* Judge Solution and Data by: Glenn Martin                                *)
(*                                                                         *)
(***************************************************************************)

program eggs;

var infile:text;
    numClutches:integer;
    i:integer;
    numEggs:integer;
    space:char;
    season:string;
    hatchingRate:real;
    survivalRate:real;
    numHatched:integer;
    numSurvived:integer;

begin
   (* Open the input file *)
   assign(infile, 'eggs.in');
   reset(infile);

   (* Read the number of data sets (number of clutches) *)
   readln(infile, numClutches);

   (* Process each clutch *)
   for i:=1 to numClutches do
   begin
      (* Read the number of eggs in the clutch and the season *)
      readln(infile, numEggs, space, season);

      (* Determine the hatching rate based on the number of eggs *)
      if (numEggs <= 50) then
	 hatchingRate:=0.55
      else if ( (numEggs >= 51) and (numEggs <= 100) ) then
	 hatchingRate:=0.70
      else if (numEggs > 100) then
	 hatchingRate:=0.20;

      (* Determine the survival rate based on the season *)
      if (season[length(season)] = '*') then
	 survivalRate:=0.90
      else if (season = 'spring') then
	 survivalRate:=0.75
      else if (season = 'summer') then
	 survivalRate:=0.50
      else if (season = 'fall') then
	 survivalRate:=0.25
      else if (season = 'winter') then
	 survivalRate:=0.10;

      (* Figure out how many hatch and how many of those survive *)
      numHatched:=trunc(hatchingRate * numEggs);
      numSurvived:=trunc(survivalRate * numHatched);

      (* Write out output *)
      writeln('Clutch #', i, ': ', numSurvived, ' surviving lizards');
   end;

   (* Close input file *)
   close(infile);
end.