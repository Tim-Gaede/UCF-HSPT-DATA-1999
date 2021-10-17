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
(* Problem Name: Inspector Doohickey                                       *)
(* Filename: MAZE                                                          *)
(*                                                                         *)
(* Specification by: Eric Heimburg                                         *)
(* Judge Solution and Data by: Sandra Powers                               *)
(*                                                                         *)
(***************************************************************************)


(* The easiest way to solve a problem like this is with a recursive depth-
   first search. At each position, you check to see if you have reached your
   goal. If not, you mark where you are as having been visited (because you
   don't want to come back and try again) and then you try to move in some
   direction. If you can move, you do so and repeat the process for that
   position. If you can't move in that direction, you try another direction.
   If you get to a position where you can't move at all, you back up along
   your path until you can move to some unvisited spot and you go on. By the
   time the original call of the recursive function in the main program
   returns, you will have hit every spot in the maze. Of course, in this
   program we optimize so that when we find the right spot we stop trying.
   It's a long, arduous process for the computer (not really, but it can be
   if the array is too big) but a relatively short program to write for the
   programmer. *)


(* First thing we want to do is maximize our stack size with this compiler
   directive. Otherwise, the stack doesn't have enough space to handle the
   maximum case of recursion and we crash. *)

{$M 65520, 0, 655360}




VAR
(* these things are global so you can reference them in the recursive function
without having to pass them *)

Maze: array [1..10, 1..10] of char;              (* holds the characters from
                                                    input *)
Visited: array [1..10, 1..10] of integer;        (* keeps track of where you
                                                    have been so far *)
Path: String;                 		         (* holds the path of
                                                    directions *)
going,                      			 (* works as a flag to tell
                                                    you whether you are going
                                                    in or out: 0 means going
                                                    in, 1 means going out *)
gone: boolean;                       		 (* works as a flag in the
                                                    recursive Move() function;
                                                    if gone = 1 you've found
                                                    and printed your path, so
                                                    stop looking *)


(* Move moves you along the path recursively. If you already found a solution,
   it simply returns along the solution path. If you find the solution path
   this turn, it sets the appropriate flag to true and returns. Otherwise,
   it tries to move in each direction and if it can, calls itself recursively
   from the new position. *)

PROCEDURE Move(a, b: integer);
BEGIN
    (* if we already have a solution, don't waste time trying more paths,
       just return *)
    IF gone THEN exit;

    (* if you are on your way in and find the Inspector, or on your way out
       and find the exit, print the path, set gone to show that you are done,
       and return *)
    IF ((Maze[a, b] = 'I') AND NOT (going)) OR ((Maze[a, b] = 'X')
        AND (going)) THEN
    BEGIN
         writeln(Path);
	 gone := true;
	 exit;
    END;

    (* try each direction - note that before going in a direction you must
       check if it is still on the 10x10 map and that it hasn't already been
       visited; since we set the wall spaces as visited when we read in the
       input, we don't have to explicitly check for that *)

    IF (a+1 <= 10) AND (Visited[a+1, b] <> 1) THEN
    BEGIN
        (* add the appropriate direction to the Path string and set
           Visited for the spot we are about to move to *)
	Path := Path + 'S';
	Visited[a+1, b] := 1;

        (* recursively move *)
	Move(a+1, b);

        (* when you return from the above Move() call, either you have
           found the path and printed it and you're done, or you haven't
           and going this was leads to a dead end; either way, remove the
           direction from the Path string *)
	Delete(Path, Length(Path), 1);

    END; (* end if able to go S *)

    (* now, if you haven't found the path, try the next direction(s) *)
    IF (b+1 <= 10) AND (Visited[a, b+1] <> 1) AND NOT (gone) THEN
    BEGIN
        Path := Path + 'E';
	Visited[a][b+1] := 1;
	Move(a, b+1);
	Delete(Path, Length(Path), 1);
    END; (* end if able to go E *)

    IF (a-1 > 0) AND (Visited[a-1, b] <> 1) AND NOT (gone) THEN
    BEGIN
        Path := Path + 'N';
	Visited[a-1, b] := 1;
	Move(a-1, b);
	Delete(Path, Length(Path), 1);
    END; (* end if able to go N *)

    IF (b-1 > 0) AND (Visited[a, b-1] <> 1) AND NOT (gone) THEN
    BEGIN
        Path := Path + 'W';
	Visited[a, b-1] := 1;
	Move(a, b-1);
	Delete(Path, Length(Path), 1);
    END; (* end if able to go W *)

    (* if there were no guaranteed path, we might have to do something else
       here; but we are guaranteed a solution *)
    exit;
END; (* end of Move() *)


(* main program *)
VAR
    ifp: Text;                  (* input file  *)
    nMazes,                     (* number of mazes total *)
    i, j, k,                    (* i = number maze you are in now; j & k =
                                   counters for running through the matrix *)
    Ij, Ik,                     (* starting position of Liver *)
    Oj, Ok: Integer;            (* starting position of the Inspector *)

BEGIN

    (* open the file and read in the number of mazes *)
    Assign(ifp, 'maze.in');
    Reset(ifp);
    Readln(ifp, nMazes);

    (* for each of the mazes, do all this stuff *)
    FOR i := 1 TO nMazes DO
    BEGIN
        (* set the Path and Visited matrix to 0 and initialize the flags *)
	Path := '';
        FOR j := 1 TO 10 DO
            FOR k := 1 TO 10 DO
                Visited[j, k] := 0;
        going := false;
        gone := false;

        (* print out the header for this maze *)
	writeln('Maze #', i);

        (* read in the input and make not of some things *)
	FOR j := 1 TO 10 DO
	BEGIN
	    FOR k := 1 TO 10 DO
	    BEGIN
	        Read(ifp, Maze[j, k]);


                (* take note of initial position of Liver and the Inspector *)
	        IF (Maze[j,k] = 'L') THEN
		BEGIN
		    Ik := k;
		    Ij := j;
                END (* end of if == 'L' *)
		ELSE IF (Maze[j,k] = 'I') THEN
		BEGIN
		    Ok := k;
		    Oj := j;
                END (* end of if == 'I' *)

                (* or if it's a wall set Visited (since you can't ever go into
                   a wall space, it counts as having been visited) *)
		ELSE IF (Maze[j,k] = 'W')
                THEN Visited[j,k] := 1;
            END; (* end of for that reads in one line of input *)

            (* scan in the \n at the end of each line *)
	    Readln(ifp);
        END;

        (* because of the way Move() is set up, you have to set where you
           currently are as visited before you call move the first time *)
	Visited[Ij,Ik] := 1;

        (* find the path from Liver to the Inspector *)
	Move(Ij, Ik);

        (* clean up Visited so that only walls are marked as true *)
        FOR j := 1 TO 10 DO
            FOR k := 1 TO 10 DO
                IF Maze[j,k] = 'W' THEN Visited[j,k] := 1
                ELSE Visited[j,k] := 0;

        (* reset the flags; going = 1 now because you are on your way out *)
        going := true;
	gone := false;

        (* just like above *)
        Visited[Oj,Ok] := 1;

        (* find the path from the Inspector to the exit *)
	Move(Oj, Ok);

        writeln;
    END; (* end of outside for loop (for each maze) *)

    (* be neat, close your file *)
    close(ifp);

END. (* end of main() *)
