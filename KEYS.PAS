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
(* Problem Name: Too Many Keys                                             *)
(* Filename: KEYS                                                          *)
(*                                                                         *)
(* Specification by: Michael Kujawa                                        *)
(* Judge Solution and Data by: Michael Kujawa                              *)
(*                                                                         *)
(***************************************************************************)


{ TKey
   A structure holding the tenants name and the cuts in the key.  There are
   eight notch sites, and these are numbered as follows

          111
     13579135
   =#--------######O
     24681111
         0246

   Note that the name is stored with a colon appended to it to simplify
   formatting the output later.

   Cuts could have simply been a 16-bit integer.  Very simple bit-wise math
   could then be used to check one key against another, but for ease of
   understanding, I do it the more obvious, bit-by-bit, way.
}
Type
String20 = String[20];
TKey = record
    Name : String20;
    Cuts : Array[1..16] of Boolean;
  End;

Var
Keys : Array[1..1000] of TKey; { Keys in this data set }
nKeys : Integer;               { The number of keys in "Keys" }



{ ReadKey
   ReadKey processes the middle line in the ASCII art for a key and
   reads the 16 cuts into the "Cuts" array.
}
Procedure ReadKey(Inp : String20; var Key : TKey);
Var
  i, cut : Integer;

Begin
  for i:=3 to 10 do
    Begin
      cut := (i-3)*2 + 1;
      if (Inp[i] = '-') OR (Inp[i] = '.') then
        Key.Cuts[cut] := True
      else
        Key.Cuts[cut] := False;

      cut := cut + 1;
      if (Inp[i] = '-') OR (Inp[i] = '"') then
        Key.Cuts[cut] := True
      else
        Key.Cuts[cut] := False;
    End;
End;





{ bCanOpen
   BCanOpen returns true if "KeyToCheck" can open the door designed for
   "CorrectKey" (KeyToCheck and CorrectKey are indices into "Keys".)

   This is done by looping through all the possible cuts, and if a cut
   is present on the correct key, making sure it is present on the key
   to check.

   Bitwise, we are checking that
   PatternToCheck AND CorrectPattern = CorrectPattern.
}
Function bCanOpen(KeyToCheck : Integer; CorrectKey : Integer) : Boolean;
Var
  cut : Integer;
Begin
  bCanOpen := true;
  for cut := 1 to 16 do
      if (Keys[CorrectKey].Cuts[cut] = True) AND (Keys[KeyToCheck].Cuts[cut] = False) then
          bCanOpen := false;
End;




{ CheckKey
   Returns the number of doors that Keys[idx] can open other than its own.
   This is done by caling "bCanOpen" for all keys (besides idx.)
}
Function CheckKey(idx : Integer) : Integer;
Var
  i, nWrongKeys : Integer;

Begin
  nWrongKeys := 0;
  for i := 1 to nKeys do
    if (i <> idx) AND bCanOpen(idx, i) then
      Inc(nWrongKeys);
  CheckKey := nWrongKeys;
End;




{ GenSpaces
  Generates the spaces to right-pad the names in the output.
}
Procedure GenSpaces(Name : String20; var Spaces : String);
Var
  i : Integer;
Begin
  Spaces := '';
  for i := 1 to 17 - Length(Name) do
    Spaces := Spaces + ' ';
End;

{ DoSet
   Reads in the keys for a set then generates the output; it does a single
   set.
}
Procedure DOSet(Var F : Text);
Var
  i : Integer;
  st : String;
  Spaces : String;

Begin
  { Read the input.  Not that the names are stored with a colon appended }
  for i := 1 to nKeys do
    Begin
      Readln(F, st);
      Keys[i].Name := st + ':';
      Readln(F, st);
      Readln(F, st);
      ReadKey(st, Keys[i]);
      Readln(F, st);
    End;

  { Generate the output.  Now the name is just printed in 16 characters }
  for i := 1 to nKeys do
    Begin
      GenSpaces(Keys[i].Name, Spaces);
      Writeln('  ', Keys[i].Name, Spaces, CheckKey(i));
    End;
End;

Var
  SetNum : Integer;
  F      : Text;
  i      : Integer;

Begin
  Assign(F, 'keys.in');
  Reset(F);
  SetNum := 0;

  Readln(F, nKeys);

  while nKeys > 0 do
    Begin
      Inc(SetNum);
      Writeln('Set #', SetNum, ':');
      DoSet(F);
      Writeln;
      Readln(F, nKeys);
    End;
  Close(F);
End.