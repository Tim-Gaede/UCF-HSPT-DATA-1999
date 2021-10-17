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
(* Problem Name: Wheebop!                                                  *)
(* Filename: ROBOTS                                                        *)
(*                                                                         *)
(* Specification by: Eric Heimburg                                         *)
(* Judge Solution and Data by: Phillip Dexheimer                           *)
(*                                                                         *)
(***************************************************************************)


type
  WordArray = array[1..110] of string;

var
  curline : string;
  words : WordArray;
  nWord : integer;
  nReverse : integer;
  InFile : TEXT;

{BreakLine is called immediately after a line of input has been read into
 curline.  This is the proc that actually does the work of parsing input
 and writing output}
procedure BreakLine;

var
  i, j, k : integer;
  curword : string; {stores the current word that I am manipulating}
  AorE    : boolean;{bool that indicates whether the curword has an a or e in it}

begin
  i := 1;
  j := 1;
{In order to find the words, I step through the line char by char.
 i will be the index of the beginning of the word, j will be the index of the end}
  while (j <= Length(curline)) do
   begin
{Checks to see if j is at a word delimiter}
    if (curline[j] in [' ','.','?','!']) then
     begin
      {Throw out zero-character words (Here are two: '  ')}
      if (j = i) then
       begin
        write (curline[j]);
        i := j+1;
       end
      else
       begin
        {copy into curword}
        curword := copy(curline, i, j-i);
        {Check for the six abbreviations. The Length check is for abbr's at
         the end of the line}
        if (curline[j] = '.') and
           ((j = Length(curline)) or (curline[j+1] in [' ','.','?','!'])) then
          if (curword = 'Mr') or (curword = 'Mrs') or
             (curword = 'Ms') or (curword = 'Dr') or
             (curword = 'Sr') or (curword = 'Jr') then
           begin
             {Append the period and inc j so we don't see the period again}
             curword := curword + '.';
             inc(j);
           end;
        {add curword into the words array}
        inc(nWord);
        words[nword] := curword;
        {check to see if the current word has an 'a' or 'e' in it}
        k := 1;
        AorE := false;
        while (k <= Length(curword)) and (not AorE) do
         begin
          if (curword[k] in ['a','A','e','E']) then
            AorE := true;
          inc(k);
         end;
        {If so, increment the 'contiguous words with an 'a' or 'e'' counter}
        if (AorE) then
          inc(nReverse)
        {else, set it back to zero (They won't be contiguous anymore}
        else
          nReverse := 0;
        {Output.  Each if is another rule}
        if (nWord >= 11) then
         begin
          write(words[nWord-10]);
          {This if in all of these is to print out the word delimiter
           (eg: spaces, puctuation}
          if (j <= length(curline)) then
            write (curline[j]);
         end
        else if (nReverse >= 8) then
         begin
          for k := Length(curword) downto 1 do
            write (curword[k]);
          if (j <= length(curline)) then
            write (curline[j]);
         end
        else if (nWord = 1) and (curline[j] in ['.','?','!']) then
          write ('Wheebop!')
         {Don't print out curline[j] here because it's guaranteed to
          be the sentence-ender, and the rule says to replace the
          sentence with Wheebop!, not the word}
        else
         begin
          write (curword);
          if (j <= length(curline)) then
            write (curline[j]);
         end;
        if (curline[j] in ['.', '?', '!']) then
         begin
          {If we're at the end of the sentence, reset the variables}
          nWord := 0;
          nReverse := 0;
         end;
        {Put i at the beginning of the next word}
        i := j+1;
       end;
     end;
    inc(j);
   end;
  {After we finish that while loop, there are two cases:
    1) i is off the end of the line.  If so, we go on our merry way
    2) i points to the beginning of the last word.  If so, we need to
       handle it
   if i is off the end of the sentence, it must equal j (Because of i := j+1;inc(j);}
  {We'll handle the last word just like the others, except:
    abbreviations aren't an issue.  That period will get caught above, and i
      will now point after the line.
    We don't print the word delimiter.  Here, it is always the newline, and
      there's a writeln in the loop of main to handle that
    It won't be the end of the sentence.  That would have been caught above,
      just like the abbreviations}
  if (j <> i) then
   begin
    curword := copy (curline, i, j-i);
    inc(nWord);
    words[nword] := curword;
    k := 1;
    AorE := false;
    while (k <= Length(curword)) and (not AorE) do
     begin
      if (curword[k] in ['a','A','e','E']) then
        AorE := true;
      inc(k);
     end;
    if (AorE) then
      inc(nReverse)
    else
      nReverse := 0;
    if (nWord >= 11) then
     begin
      write(words[nWord-10]);
     end
    else if (nReverse >= 8) then
     begin
      for k := Length(curword) downto 1 do
        write (curword[k]);
     end
    else if (nWord = 1) and (curline[j+1] in ['.','?','!']) then
      write ('Wheebop!')
    else
     begin
      write (curword);
     end;
   end;
end;

{Here's main. Nothing real complicated here}
begin
  assign(InFile, 'robots.in');
  reset(InFile);
  nWord := 0;
  nReverse := 0;
  while (not eof(InFile)) do
   begin
    readln(InFile, curline);
    BreakLine;
    writeln;
   end;
  close(InFile);
end.