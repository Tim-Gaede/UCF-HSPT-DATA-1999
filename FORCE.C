/***************************************************************************/
/*                      University of Central Florida                      */
/*                            Thirteenth Annual                            */
/*                    High School Programming Tournament                   */
/*                                                                         */
/*                              May 7, 1999                                */
/*                                                                         */
/*                                                                         */
/*                                                                         */
/*                                                                         */
/* Problem Name: Round and Round We Go                                     */
/* Filename: FORCE                                                         */
/*                                                                         */
/* Specification by: Glenn Martin                                          */
/* Judge Solution and Data by: Travis Terry                                */
/*                                                                         */
/***************************************************************************/


/* Library includes

    This program only needs to include the standard I/O routines from the
    C run-time library.
*/
#include <stdio.h>
#include <stdlib.h>

/* Global definitions

    These values will be used later in the program.  It is convenient to
    define them here so they can be refered to by name later, making the
    code easier to read.
*/

#define PI 3.141592654
#define MASS 70
#define RADIUS 10

/* This is the main (and only) routine of FORCE. */
int main() {
    /* Variables used by main()

        fp - pointer to the file structure for reading the input file
        N - number of values to read from the input file
        i - loop variable for counting the input values
    */
    int i, N;
    FILE *fp;

    /* Open the input file

        The input file is opened using the standard library function fopen().
        The first parameter to fopen() is the name of the file, in this case
        FORCE.IN.  The second parameter is the access mode.  For the input
        file, we use "r" to signify the file should be opened only for reading.
        If the file fails to open for any reason, fopen() returns NULL.  If
        this happens, perror() is used to print an error message describing
        what happened, and the program exists with an error code by calling
        exit().  In the contest environment, the input file will always be
        present, but checking the return value of fopen() is a good habit.
    */
    fp = fopen("force.in", "r");
    if (!fp) {
        perror("force.in");
        exit(1);
    }

    /* Begin processing the input file

        The first line of the input file contains the number of data sets in
        the file.  This number is read by fscanf().  The first parameter is
        a previously opened file.  The second parameter is the format string
        to match, in this case "%d" means read an integer (d for decimal).
        The remaining parameter is a pointer to the integer variable to hold
        the value read from the file.  Normally it is important to verify the
        correct number of values are matched by checking the return value of
        fscanf(), but since the format of the input file is known to be
        correct, it is simpler to assume an integer is matched correctly.

        The for() statement causes the program to execute the following
        statement (the code between the curly braces) multiple times.  The
        number of values in the data file is N, so the for() statement counts
        from 0 to N-1.
    */
    fscanf(fp, "%d", &N);
    for (i=0; i<N; i++) {
        /* Variables used in the loop

            These variables are defined inside the loop because they are not
            needed outside.  Confining variable definitions to the scope in
            which they are used keeps the variables as close as possible to
            their related code.  Not only does this make the code easier to
            read, but it can help prevent problems sometimes encountered with
            reusing global variables.

            time - the number of seconds for one revolution (read from the file)
            speed - linear velocity of the centrifuge
            force - force felt by the astronaut
        */
        double time, speed, force;

        /* Read time from the input file

            Each remaining line of the input file contains a single floating-
            point value.  That value is read into the double-precision variable
            'time' using fscanf().  The second parameter is "%lf" to tell
            fscanf() to read a double-precision value (l-ong f-loat).  The
            last parameter is a pointer to the location where the double will
            be stored.  fscanf() will automatically skip past white space in
            the input file (spaces and ends of lines), so there is no need
            to perform any other processing of the input file.
        */
        fscanf(fp, "%lf", &time);

        /* Calculate the answer

            The following two statements calculate the proper value of 'force'
            to solve the problem.  This formula could have been simplified, but
            for the sake of illustration, the statements follow the formulas
            given in the problem statement.  The global definitions are used
            here to enhance the legibility of the code.
        */
        speed = 2 * PI * RADIUS / time;
        force = MASS * speed*speed / RADIUS;

        /* Print the output

            The printf() function is used to output the force calculated by
            the previous statements.  The format string "%.3lf\n\n" tells
            printf() to printf a double precision value to 3 decimal places
            and follow that value by two blank lines.  The final parameter
            to printf() is the double-precision value to print.
        */
        printf("%.3lf\n\n", force);
    }

    /* Close the input file

        Once processing of the input file is complete, it is important to
        close the file.  This is done by calling fclose() with the file
        pointer.  After closing the file, the file structure pointer, fp,
        is set to NULL to indicate the pointer is no longer in use.  Since
        the program is going to exit anyway, this is technically unnecessary,
        but it is still a good habit to keep.
    */
    fclose(fp);
    fp = NULL;

    /* Exit the main routine

        Calling return causes the main routine to exit.  The value returned
        from main() is an error code to the operating system.  Since the
        program finished correctly, a value of zero is returned.
    */
    return 0;
}