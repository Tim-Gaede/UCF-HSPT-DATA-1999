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
(* Problem Name: Round and Round We Go                                     *)
(* Filename: FORCE                                                         *)
(*                                                                         *)
(* Specification by: Glenn Martin                                          *)
(* Judge Solution and Data by: Travis Terry                                *)
(*                                                                         *)
(***************************************************************************)


PROGRAM ForceProgram;

(* Global definitions

    These values will be used later in the program.  It is convenient to
    define them here so they can be refered to by name later, making the
    code easier to read.
*)

const PI=3.141592654;
const MASS=70;
const RADIUS=10;

(* Variables used by the program

    fp - pointer to the file structure for reading the input file
    N - number of values to read from the input file
    i - loop variable for counting the input values
    time - the number of seconds for one revolution (read from the input file)
    speed - linear velocity of the centrifuge
    force - force felt by the astronaut
*)
VAR
    i, N : INTEGER;
    time, speed, force : REAL;
    fp : TEXT;

BEGIN
    (* Open the input file

        The input file is opened using Assign() and Reset().  Assign()
        associates the file variable 'fp' to the file name 'force.in'.  Reset()
        opens the file for reading.
    *)
    Assign(fp, 'force.in');
    Reset(fp);

    (* Begin processing the input file

        The first line of the input file contains the number of data sets in
        the file.  This number is read by ReadLn.  The first parameter is
        a previously opened file.  The second parameter is the variable to read
        from the file.  ReadLn automatically reads the remainder of the line
        and discards any other characters.

        The FOR loop causes the program to execute the following statement
        (the code between the curly braces) multiple times.  The number of
        values in the data file is N, so the FOR statement counts from 1 to N.
    *)
    ReadLn(fp, N);
    FOR i := 1 to N DO BEGIN
        (* Read time from the input file

            Each remaining line of the input file contains a single floating-
            point value.  That value is read into the variable 'time' using
            ReadLn.  ReadLn will read the entire line and discard any other
            characters.
        *)
        ReadLn(fp, time);

        (* Calculate the answer

            The following two statements calculate the proper value of 'force'
            to solve the problem.  This formula could have been simplified, but
            for the sake of illustration, the statements follow the formulas
            given in the problem statement.  The global definitions are used
            here to enhance the legibility of the code.
        *)
        speed := 2 * PI * RADIUS / time;
        force := MASS * speed*speed / RADIUS;

        (* Print the output

            The WriteLn function is used to output the force calculated by
            the previous statements.  Passing 'force:1:3' to WriteLn causes
            the force to be printed with at least one digit to the left of
            the decimal and three digits to the right of the decimal.  The
            second call to WriteLn causes a blank line to be printed after
            each data set.
        *)
        WriteLn(force:1:3);
        WriteLn;
    END;

    (* Close the input file

        Once processing of the input file is complete, it is important to
        close the file.  This is done by calling Close().  Since the program
        is going to exit anyway and the file is only open for reading, this
        is technically unnecessary, but it is still a good habit to keep.
    *)
    Close(fp);
END.