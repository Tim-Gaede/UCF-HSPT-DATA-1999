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
(* Problem Name: Dinner And A Movie                                        *)
(* Filename: MOVIE                                                         *)
(*                                                                         *)
(* Specification by: Jason Daly                                            *)
(* Judge Solution and Data by: Jonathan Kolb                               *)
(*                                                                         *)
(***************************************************************************)


program Movie;

type
  TTime = record  { Make our own data type to hold a time }
            Hour, Minute : integer;
          end;

var
  infile : text;
  index, numSets, i, waitMins, numMovies, j : integer;
  OffWork, Temp : TTime;
  Movies : array [0..19] of TTime;
  hours, minutes : string;

procedure TimeBetween(Time1, Time2 : TTime; var Between : TTime);

{ Returns the time between Time1 and Time2 in Between.  If Time2 is before
  Time1, Between returns with negative hours. }

begin
  Between.Hour := Time2.Hour - Time1.Hour;
  Between.Minute := Time2.Minute - Time1.Minute;
  while(Between.Minute < 0) do  { Can't go around with negative minutes. }
    begin
      Between.Hour := Between.Hour - 1;
      Between.Minute := Between.Minute + 60;
    end;
end;

procedure AddMinutes(Time1 : TTime; Minutes : integer; var NewTime : TTime);

{ Returns Minutes number of minutes added to Time1 in NewTime.  Correctly
  handles adding a number of minutes over 60. }

begin
  NewTime.Minute := Time1.Minute + Minutes;
  NewTime.Hour := Time1.Hour + NewTime.Minute div 60;  { More than 60 minutes?  Not acceptable! }
  NewTime.Minute := NewTime.Minute mod 60;
end;

function ReadTime(var infile : Text; var TimeRead : TTime) : boolean;

{ Reads in a time from infile, and returns true on success. If we are at the
  end of a line, there are no times available, and we'll return false. }

var
  c : char;
  i : integer;

begin
  if eoln(infile) then  { any more characters on this line? }
    ReadTime := false
  else
    repeat { read from infile until we get a digit 0..9 }
      read(infile, c);
    until (c in ['0'..'9']) or (eoln(infile));
  if (not eoln(infile)) then  { did we hit the end of the line before we got a digit? }
    begin
      i := ord(c) - ord('0'); { convert from character value to integer value. }
      read(infile, c);
      if (c <> ':') then { do we have a time after 10:00? }
        begin
          i := i * 10 + ord(c) - ord('0'); { old character was the tens place.  make it so. }
          read(infile, c);
        end;
      TimeRead.Hour := i;
      read(infile, c);
      i := ord(c) - ord('0'); { convert from character value to integer value. }
      read(infile, c);
      if (c <> ' ') then
        i := i * 10 + ord(c) - ord('0'); { old character value was the tens place.  make it so. }
      TimeRead.Minute := i;
      ReadTime := true; { successfully read a time. }
    end;
end;

begin
  assign(infile, 'movie.in');
  reset(infile);
  readln(infile, numSets);
  for i := 1 to numSets do
    begin
      numMovies := 0;
      ReadTime(infile, OffWork); { when do we get off work? }
      readln(infile);
      readln(infile, waitMins); { how long of a wait at the restaurant? }
      while(ReadTime(infile, Movies[numMovies])) do
        begin { as long as we have valid times left on the line, keep going }
          TimeBetween(Movies[0], Movies[numMovies], Temp);
{ remember, 24 hour period means 24 hours from the start of the first film.
  we *can* spill over into tomorrow.  if this is the case, the time of day
  for tomorrow's films will have to be earlier in the day than the time of
  day of the first film. }
          if (Temp.Hour < 0) then { was the new time earlier in the day tomorrow? }
            Movies[numMovies].Hour := Movies[numMovies].Hour + 24;
          numMovies := numMovies + 1;
        end;
        AddMinutes(OffWork, waitMins, Temp); { waiting at the restaurant }
        AddMinutes(Temp, 57, OffWork); { eating }
        index := -1; { set sentinel value so we don't always get the last showing. }
        for j := 0 to numMovies do
          begin
            TimeBetween(OffWork, Movies[j], Temp);
            if (Temp.Hour >= 0) and (index = -1) then { have we set the index before? }
              index := j;
          end;
        TimeBetween(OffWork, Movies[index], Temp);
        if (Temp.Minute = 1) then { minute vs. minutes, which to print? }
          minutes := ' minute'
        else
          minutes := ' minutes';
        if (temp.Hour = 1) then { hour vs. hours, which to print? }
          hours := ' hour'
        else
          hours := ' hours';
        Movies[index].Hour := Movies[index].Hour mod 24;  { pretty up the hour for printing. }
        if (Movies[index].Hour = 0) then
          Movies[index].Hour := 24;
        write(Movies[index].Hour, ':');
        if (Movies[index].Minute < 10) then { we have to print out our own 0 if less than 10 minutes after the hour. }
          write('0', Movies[index].Minute)
        else
          write(Movies[index].Minute);
        write(', you have ');
        if (Temp.Hour > 0) then
          if (Temp.Minute > 0) then
            writeln(Temp.Hour, hours, ' and ', Temp.Minute, minutes)
          else
            writeln(Temp.Hour, hours)
        else
          begin
            write(Temp.Minute, minutes);
            if (Temp.Minute < 20) then { with *less than* 20 minutes, print hurry up! }
              writeln(', hurry up!')
            else
              writeln;
          end;
        writeln; { blank line between data sets. }
        readln(infile);
    end;
  close(infile);
end.