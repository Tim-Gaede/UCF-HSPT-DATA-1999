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
(* Problem Name: Eugene And The Supremes                                   *)
(* Filename: RATS                                                          *)
(*                                                                         *)
(* Specification by: Phillip Dexheimer                                     *)
(* Judge Solution and Data by: Jason Daly                                  *)
(*                                                                         *)
(***************************************************************************)

program rat;

type
    ratName = string[15];

var
    infile     : text;      {Input file}
    sets       : integer;   {Number of data sets}
    currentSet : integer;

    numRats    : integer;
    rats       : array [1..30] of ratName;    {Rat names}
    reps       : array [1..30] of integer;    {Rat reputations}

    supremeRat : integer;   {Index of the Supreme Rat}
    supremeRep : integer;   {Reputation of the Supreme Rat}

procedure checkSupreme;
var maxrep : integer;
    index  : integer;
    count  : integer;
    i      : integer;
begin
    maxrep := 0;
    count  := 0;
    index  := 0;

    if (numRats = 0) then
     begin
         {Special case:  No rats, so no Supreme Rat}
         supremeRat := 0;
         supremeRep := 0;
     end
    else
        if (numRats = 1) then
         begin
             {Special case:  One rat, so automagically Supreme}
             supremeRat := 1;
             supremeRep := reps[1];
         end
        else
         begin
             for i := 1 to numRats do
              begin
                  if (abs(reps[i]) > abs(maxrep)) then
                   begin
                       maxrep := reps[i];
                       index := i;
                       count := 1;
                   end
                  else
                      if (abs(reps[i]) = abs(maxrep)) then
                          count := count + 1;
              end;

             if (count > 1) then
              begin
                  {No Supreme Rat, but we'll record maxrep as
                   the rep to beat to be Supreme}
                  supremeRat := 0;
                  supremeRep := maxrep;
              end
             else
              begin
                  {The Supreme Rat is . . .}
                  supremeRat := index;
                  supremeRep := reps[index];
              end;
         end;
end;

procedure laud( rat1 : ratName; rat2 : ratName);
var index1, index2 : integer;
    i              : integer;
begin

    {First, find the indices of the two rats}
    index1 := 1;
    while (rats[index1] <> rat1) do
        index1 := index1 + 1;

    index2 := 1;
    while (rats[index2] <> rat2) do
        index2 := index2 + 1;

    {Next check to see if we're lauding the Supreme Rat}
    if (index2 = supremeRat) then
        reps[index1] := reps[index1] + 2
    else
     begin
         reps[index1] := reps[index1] - 1;
         reps[index2] := reps[index2] + 3;
     end;

    {Finally, check to see if we have a new Supreme Rat, or
     if we've deposed the current Supreme Rat}
    checkSupreme;
end;

procedure slander( rat1 : ratName; rat2 : ratName);
var index1, index2 : integer;
    i              : integer;
begin

    {First, find the indices of the two rats}
    index1 := 1;
    while (rats[index1] <> rat1) do
        index1 := index1 + 1;

    index2 := 1;
    while (rats[index2] <> rat2) do
        index2 := index2 + 1;

    {Next check to see if we're lauding the Supreme Rat}
    if (index2 = supremeRat) then
        reps[index1] := reps[index1] - 2
    else
     begin
         reps[index1] := reps[index1] + 1;
         reps[index2] := reps[index2] - 3;
     end;

    {Finally, check to see if we have a new Supreme Rat, or
     if we've deposed the current Supreme Rat}
    checkSupreme;
end;

procedure supreme;
begin
    if (supremeRat <> 0) then
        writeln(rats[supremeRat],' is the Supreme Rat')
    else
        writeln('There is no Supreme Rat');
end;

procedure print;
var sortedRats : array [1..30] of ratName;
    sortedReps : array [1..30] of integer;
    j          : integer;

    procedure sortRats;
    var i       : integer;
        n       : integer;
        exch    : boolean;
        tempRep : integer;
        tempRat : ratName;
    begin
        {First, a bubble sort based on rep}
        n := numRats;
        exch := True;
        while (exch) do
         begin
            exch := False;
            for i:= 1 to n-1 do
              if (sortedReps[i] > sortedReps[i+1]) then
               begin
                   tempRep := sortedReps[i];
                   sortedReps[i] := sortedReps[i+1];
                   sortedReps[i+1] := tempRep;
                   tempRat := sortedRats[i];
                   sortedRats[i] := sortedRats[i+1];
                   sortedRats[i+1] := tempRat;
                   exch := True;
               end;
            n := n-1;
         end;

        {Now, make a second pass based on name for the
         tied reputations}
        n := numRats;
        exch := True;
        while (exch) do
         begin
            exch := False;
            for i:= 1 to n-1 do
                if ((sortedReps[i] = sortedReps[i+1]) AND
                    (sortedRats[i] > sortedRats[i+1])) then
                 begin
                     {Don't need to swap reps since they're equal}
                     tempRat := sortedRats[i];
                     sortedRats[i] := sortedRats[i+1];
                     sortedRats[i+1] := tempRat;
                     exch := True;
                 end;
            n := n-1;
         end;
    end;

begin
    {First, we need to make a temporary copy of the "rats" and "reps"
     arrays}

    for j := 1 to numRats do
     begin
         sortedRats[j] := rats[j];
         sortedReps[j] := reps[j];
     end;

    {Now, lets sort the arrays}
    sortRats;

    {Finally, we just print them out}
    for j := 1 to numRats do
         writeln(sortedRats[j],': ',sortedReps[j]);
end;


procedure executeInstructions;
var t1,t2,t3:string[15];
    line:string[80];
    wordEnd:integer;
begin

    t1 := ''; t2 := ''; t3 := '';

    while (t1 <> 'END') do
     begin
         {Read the next line of input}
         read(infile, line);
         readln(infile);

         {Parse out the first element}
         wordEnd := pos(' ',line);
         if (wordEnd = 0) then
             t1 := line
         else
             t1 := copy(line, 1, wordEnd-1);

         if (t1 = 'SUPREME') then
             supreme
         else
             if (t1 = 'PRINT') then
                 print
             else
                 if (t1 <> 'END') then
                  begin
                      {t1 is the name of the first rat in a
                       LAUD or SLANDER instruction.  We need
                       to parse out the other two elements}

                      {First, remove the first element (space included)
                       from the "line" string}
                      line := copy(line, wordEnd+1, length(line));

                      {Now, find the next space}
                      wordEnd := pos(' ',line);

                      {Now, copy out the second element}
                      t2 := copy(line, 1, wordEnd-1);

                      {Repeat for the third element}
                      line := copy(line, wordEnd+1, length(line));

                      {Check for space at the end of the line}
                      wordEnd := pos(' ',line);
                      if (wordEnd = 0) then
                          t3 := line
                      else
                          t3 := copy(line, 1, wordEnd-1);

                      {Now we need to check t2 (the action) to see
                       what t1 (the first rat) does to t3 (the second rat)}
                      if (t2 = 'LAUD') then
                          laud(t1, t3)
                      else
                          slander(t1, t3);
                  end;
     end; {while loop}

end; {executeInstructions}

procedure initReps;
var i:integer;
begin
    for i := 1 to numRats do
        reps[i] := 0;

    {Initialize the supreme rat, too}
    supremeRat := 0; supremeRep := 0;
end;

procedure getRatNames;
var i:integer;
begin
    for i := 1 to numRats do
        readln(infile, rats[i]);
end;

begin
    assign(infile, 'rats.in');
    reset(infile);

    readln(infile,sets);
    for currentSet := 1 to sets do
     begin
         readln(infile,numRats);

         {Reset all reputations to zero}
         initReps;

         {Read the rats' names into the "rats" array}
         getRatNames;

         {Check for Supreme Rat (special case of one rat)}
         checkSupreme;

         {Now, process the actions of the rats}
         executeInstructions;
     end;

     close(infile);
end.