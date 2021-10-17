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
(* Problem Name: Limited Productivity                                      *)
(* Filename: LIMITS                                                        *)
(*                                                                         *)
(* Specification by: Chris Gouge                                           *)
(* Judge Solution and Data by: Chris Gouge and Sandra Powers               *)
(*                                                                         *)
(***************************************************************************)

program limits;

var
    (*
     * input_file
     *
     * First we will need a "Text" variable so we can read from the input file,
     * which is a text file.
     *)
    input_file : Text;

    (*
     * number_test_cases
     *
     * The first line of input is the number of test cases in the input file. This will
     * be at least one (it has to be positive, which is greater than zero) and it will
     * be less than 200. Then regular "integer" type will work just fine.
     *)
    number_test_cases : integer;
    test_case_counter : integer;

    (*
     * a_lower, a_upper, b_lower, b_upper
     *
     * We'll need to store the four input values. They will all be less than 100 so
     * the standard "int" type will work just fine.
     *)
    a_lower : integer;
    a_upper : integer;
    b_lower : integer;
    b_upper : integer;

    (*
     * c_minimum, c_maximum
     *
     * These variables will store the products we come up with.
     *)
    c_minimum: integer;
    c_maximum: integer;


begin
    (*
     * Hook up input_file with the name of the file to read and
     *)
    assign(input_file, 'limits.in');
    reset(input_file);


    (*
     * Now it's time to read the number of test cases from the file. We'll tell the
     * standard function "readln" to read the first line from input_file, and
     * to store that result in number_test_cases.
     *)
    readln(input_file, number_test_cases);


    (*
     * Now we'll read in each test case, process it, and produce the required output
     * for it.
     *)
    for test_case_counter := 1 to number_test_cases do
    begin

        (*
         * Now we'll read the four numbers, again using the standard "readln" function,
         * telling it to get the contents of the next line and store these in
         * the variables we created for this purpose.
         *)
        readln(input_file, a_lower, a_upper, b_lower, b_upper);

        (*
         * Now calculate the minimum and maximum products for the input numbers. Since
         * the input numbers are all positive, the minimum will be the product of the
         * two lowest possible values and the maximum will be the product of the two
         * highest possible values. (This wouldn't necessarily be true if one of the
         * input numbers was allowed to be negative.)
         *)
        c_minimum := a_lower * b_lower;
        c_maximum := a_upper * b_upper;

        (*
         * Time to deliver the output! We'll use the standard output function "writeln"
         * and tell it to display our numbers in the appropriate output sentence.
         *)
        writeln('The product of [', a_lower, '..', a_upper, '] and [',
            b_lower, '..', b_upper, '] is limited to the range [',
            c_minimum, '..', c_maximum, '].');

    end;

end.
