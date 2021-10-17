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
/* Problem Name: Limited Productivity                                      */
/* Filename: LIMITS                                                        */
/*                                                                         */
/* Specification by: Chris Gouge                                           */
/* Judge Solution and Data by: Sandra Powers and Chris Gouge               */
/*                                                                         */
/***************************************************************************/

/*
 * stdio.h
 * This will give our program access to all standard input/output functions and types.
 */
#include <stdio.h>

/*
 * main
 *
 * This is the main function for the program.
 *
 */
void main(void)
{
	/*
	 * input_file
	 *
	 * First we will need a pointer to a FILE structure so we can read from the input file.
	 * We declare this variable and initialize it at the same time.
	 *
	 * We'll use the standard "fopen" function to open the file. We tell it the name of the
	 * file, and also the modes we are using - r for read, and t for text. The function
	 * will create a FILE structure for us and return a pointer for us to use.
	 *
	 */
	FILE* input_file = fopen("limits.in", "rt");

	/*
	 * If we got an error (a null pointer) from fopen, report it and exit the program.
	 * Even though the judges' input file is guaranteed to be present when they run the
	 * program, this will help if we forget to create our own test input file, or maybe
	 * if we accidentally delete it.
	 */
	if(!input_file)
	{
		printf("%s", "Error - Could not open the input file!!!\n");
		return;
	}

	/*
	 * number_test_cases
	 *
	 * The first line of input is the number of test cases in the input file. This will
	 * be at least one (it has to be positive, which is greater than zero) and it will
	 * be less than 200. Then built-in "int" type will work just fine.
	 *
	 * Just to be cautious, we'll initialize number_test_cases to zero.
	 */
	int number_test_cases = 0;

	/*
	 * Now it's time to read the number of test cases from the file. We'll tell the
	 * standard function "fscanf" to read one integer (format %d) from the file, and
	 * to store that result in the location of our number_test_cases. If everything
	 * goes well, fscanf will return the number of things we asked it to read -- one.
	 * If not, it will return some other number.
	 */
	int number_read = fscanf(input_file, "%d\n", &number_test_cases);

	/*
	 * If we got an error from fscanf, report it and exit the program.
	 */
	if(number_read != 1)
	{
		printf("Error - Could not read the number of test cases!!!");
		return;
	}

	/*
	 * Now we'll read in each test case, process it, and produce the required output
	 * for it.
	 */
	for(int test_case_counter = 0; test_case_counter < number_test_cases; ++test_case_counter)
	{
		/*
		 * a_lower, a_upper, b_lower, b_upper
		 *
		 * We'll need to store the four input values. They will all be less than 100 so
		 * the standard "int" type will work just fine.
		 */
		int a_lower = 0;
		int a_upper = 0;
		int b_lower = 0;
		int b_upper = 0;

		/*
		 * Now we'll read the four numbers, again using the standard "fscanf" function,
		 * telling it to look for four integers on an input line. We'll store these in
		 * the variables we created for this purpose. As before we want to make sure
		 * that the number of fields read is correct.
		 */
		number_read = fscanf(input_file, "%d %d %d %d\n", &a_lower, &a_upper, &b_lower, &b_upper);

		/*
		 * If we got an error from fscanf, report it and exit the program.
		 */
		if(number_read != 4)
		{
			printf("%s", "Error - Did not read four numbers from input line!!!");
			return;
		}

		/*
		 * c_minimum, c_maximum
		 *
		 * Now calculate the minimum and maximum products for the input numbers. Since
		 * the input numbers are all positive, the minimum will be the product of the
		 * two lowest possible values and the maximum will be the product of the two
		 * highest possible values. (This wouldn't necessarily be true if one of the
		 * input numbers was allowed to be negative.)
		 */
		int c_minimum = a_lower * b_lower;

		int c_maximum = a_upper * b_upper;


		/*
		 * Time to deliver the output! We'll use the standard output function "printf"
		 * and tell it to display the integers (format %d) in specific positions inside
		 * an output sentence. At the end of the output sentence we'll move to a new
		 * line (\n).
		 */
		printf("The product of [%d..%d] and [%d..%d] is limited to the range [%d..%d].\n",
			a_lower, a_upper, b_lower, b_upper, c_minimum, c_maximum);

	}  // end of for statement [test_case_counter]

}  // end of main function
