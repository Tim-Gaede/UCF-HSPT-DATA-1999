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
(* Problem Name: Ants                                                      *)
(* Filename: ANTS                                                          *)
(*                                                                         *)
(* Specification by: Ambrose Feinstein                                     *)
(* Judge Solution and Data by: Michael Kujawa                              *)
(*                                                                         *)
(***************************************************************************)


{ Ants

   This is a simple geometry problem, which means it is simple if you know
   the rules and formulas needed to solve it (otherwise it is impossible.)
   Simply put, the problem is to test if three sides can form a triangle,
   and if so, test if they can form a right triangle.
}

{ First, a couple of utility functions. }

{ sqr
   Computes the square of an integer.  Remember that for input ranging
   from 1 to 32000, the input squared ranges from 1 to 1,024,000,000!
   This result can not fit in a 16 bit int.
}
Function sqr(a : integer) : LongInt;
Var
  Ret : LongInt;

Begin
  Ret := a;
  Ret := Ret * Ret;
  sqr := Ret;
End;



{ Swap
   Swaps the values of two integers.  This is used to find and set the
   larger of the three side lengths.
}
Procedure Swap(var a : Integer; var b : Integer);
Var
  c : Integer;
Begin
  c := a;
  a := b;
  b := c;
End;





{ bIsRight
   bIsRight returns true if the three side lengths can construct a right
   triangle.  This is tested with the Pythagorean theorm: a triangle is a
   right triange if and only if the square of the length of the hypotoneuse
   is equal to the sum of the squares of the lengths of the other two sides.
}
Function bIsRight(a : Integer; b : Integer; c : Integer) : Boolean;
Var
  ASquared, BSquared, CSquared : LongInt;
Begin
  ASquared := sqr(a);
  BSquared := sqr(b);
  CSquared := sqr(c);

  bIsRight := ASquared + BSquared = CSquared;
End;





{ bIsTriangle
   bIsTriangle returns true if the three side lengths can construct a valid
   triangle.  A valid triangle MUST have area, so 1 1 2 can not construct
   a triangle, only a line segment.

   Three side lengths can construct a triangle if the longest side is shorter
   than the sum of the other two lengths. Note that a, b, and c must be cast
   to LongInts since adding to Integers could overflow an Integer.
}
Function bIsTriangle(a : LongInt; b : LongInt; c : LongInt) : Boolean;
Begin
  bIsTriangle := a + b > c;
End;





{ DoSet
   Process a single input set which consists of three integers to be tested
   for triangle-ness.
}
Procedure DoSet(a : Integer; b : Integer; c : Integer);
Begin
  if a > c then
    Swap(a, c);
  if b > c then
    Swap(b, c);

  if bIsTriangle(a,b,c) then
    if bIsRight(a,b,c) then
      Writeln('A right triangle can be constructed.')
    else
      Writeln('A triangle can be constructed.')
  else
    Writeln('No triangle can be constructed.');

End;





Var
  F : Text;
  a,b,c : Integer;
  SetNum, i, N : Integer;

Begin
  Assign(F, 'ants.in');
  Reset(F);

  Readln(F, N);
  for i := 1 to N do
    Begin
      Readln(F, a, b, c);
      DoSet(a,b,c);
    End;

  Close(F);
End.
