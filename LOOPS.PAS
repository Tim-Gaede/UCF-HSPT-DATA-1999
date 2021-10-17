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
(* Problem Name: Fruit Loops                                               *)
(* Filename: LOOPS                                                         *)
(*                                                                         *)
(* Specification by: Chris Gouge                                           *)
(* Judge Solution and Data by: Sandra Powers and Chris Gouge               *)
(*                                                                         *)
(***************************************************************************)

PROGRAM loops;

VAR
   (* number of fruit lines to read in, number of loops per fruit *)
   nSets, nLoops: integer;

   (* input file *)
   ifp: Text;

   (* counters for the for loops *)
   i, j: integer;

   (* fruit name *)
   fruit: string;

BEGIN
     (* assign the file and get it ready for reading *)
     assign(ifp, 'loops.in');
     reset(ifp);

     (* read the number of fruit lines that follow *)
     readln(ifp, nSets);

     (* for each of the fruit names ... *)
     FOR i := 1 TO nSets DO
     BEGIN

          (* reset the number of loops for this fruit to zero *)
          nLoops := 0;

          (* read in the fruit name *)
          readln(ifp, fruit);

          (* for each of the letters in the fruit name *)
          FOR j := 1 TO length(fruit) DO
          BEGIN

               (* if the letter has a loop, add the appropriate number to
                  nLoops *)
               IF fruit[j] = 'B'
                  THEN nLoops := nLoops + 2
               ELSE IF (fruit[j] = 'A') OR (fruit[j] = 'P') OR (fruit[j] = 'O')
               OR (fruit[j] = 'P') OR (fruit[j] = 'Q') OR (fruit[j] = 'R')
               OR (fruit[j] = 'D')
                 THEN nLoops := nLoops + 1;
          END;

          (* print out the output *)
          writeln(fruit, ' has ', nLoops, ' loops.');
     END;

     (* close the input file *)
     close(ifp);
END.
