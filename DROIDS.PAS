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
(* Problem Name: These Are Not the Droids We're Looking For!               *)
(* Filename: DROIDS                                                        *)
(*                                                                         *)
(* Specification by: Jason Daly                                            *)
(* Judge Solution and Data by: Michael Kujawa                              *)
(*                                                                         *)
(***************************************************************************)


Program Droids;

{ IsAlpha
    Returns true if "ch" is an alphabetic character (a through z).
    IsAlpha ignores case.
}
Function IsAlpha(ch : char) : Boolean;
Begin
    IsAlpha := (upcase(ch) >= 'A') AND (upcase(ch) <= 'Z');
End;

{ IsDigit
    Returns true if "ch" is a digit (0 trough 9)
}
Function IsDigit(ch : char) : Boolean;
Begin
    IsDigit :=  (ch >= '0') AND (ch <= '9');
End;

{ IsVowel
    Returns true if "ch" is a vowel (a,e,i,o,u,y).
    IsVowel ignores case.
}
Function IsVowel(ch : char) : Boolean;
Begin
    IsVowel := Pos(ch, 'aeiouyAEIOUY') <> 0;
End;


{ IsGoodName
    IsGoodName returns true if "Name" meets the requirements layed out in the
    problem statement for a good name. There are four requirements:
    1) second letter must be a number or a '-'
    2) last letter must be a number or a vowel
    3) no more than two consecutive letters
    4) only letters, numbers, and '-' are permitted
}
Function IsGoodName(Name : String) : Boolean;
Var
    idx : Integer;
    ch  : Char;
    bOk : Boolean;
    GroupLen : Integer;

Begin
    (* Test condition 1 *)
    bOk := ((Length(Name) > 1) AND
            ((Name[2] = '-') OR IsDigit(Name[2])));

    (* Test condition 2 *)
    ch := Name[ Length(Name) ];
    if NOT (IsDigit(ch) OR IsVowel(ch)) then
        bOk := false;

    (* Test conditions 3 and 4 *)
    GroupLen := 0;
    for idx := 1 to Length(Name) do
      Begin
        ch := Name[idx];
        if IsAlpha(ch) then
            Inc(GroupLen)
        else if IsDigit(ch) OR (ch = '-') then
            GroupLen := 0
        else
            bOk := false; (* This catches condition 4 *)

        if GroupLen > 2 then
            bOk := false;
      End;

      IsGoodName := bOk;
End;


Var
    F : Text;
    nDroidNames : Integer;
    DroidName : String;
    Count : Integer;

Begin
    Assign(F, 'droids.in');
    Reset(F);

    Readln(F, nDroidNames);
    For Count := 1 to nDroidNames Do
      Begin
        Readln(F, DroidName);
        Write(DroidName, ':  ');
        if IsGoodName(DroidName) then
            Writeln('We''ll take this one.')
        else
            Writeln('Hey! What are you trying to push on us?');
        Writeln;
      End;

    Close(F);
End.