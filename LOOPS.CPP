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
/* Problem Name: Fruit Loops                                               */
/* Filename: LOOPS                                                         */
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
 * string.h
 * This will give our program access to all standard string manipulation functions.
 */
#include <string.h>

/*
 * main
 *
 * This is the main function for the program.
 *
 */
void main()
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
	FILE* input_file = fopen("loops.in", "rt");

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
	 * fruit_name
	 *
	 * Each test case will be a sequence of up to twelve characters. We'll use a
	 * character array to store each "fruit name" and make it more than big enough.
	 */
	char fruit_name[50];

	/*
	 * Now we'll read in each test case, process it, and produce the required output
	 * for it.
	 */
	for(int test_case_counter = 0; test_case_counter < number_test_cases; ++test_case_counter)
	{
		/*
		 * We'll set all the characters of fruit_name to zero before we use it each time.
		 * This may avoid some difficulties.
		 */
		memset(fruit_name, 0, 50);

		/*
		 * Now we'll use fscanf again, this time to read one string of characters
		 * (format %s) from the input file. It will stop reading characters at the end
		 * of the line. We'll store the test case in the character array we've created.
		 * As before, we want to make sure the number of fields read is correct.
		 */
		number_read = fscanf(input_file, "%s\n", fruit_name);

		/*
		 * If we got an error from fscanf, report it and exit the program.
		 */
		if(number_read != 1)
		{
			printf("Error - Could not read the number of test cases!!!");
			return;
		}

		/*
		 * How long is the fruit name?
		 */
		int number_letters = strlen(fruit_name);

		/*
		 * number_loops
		 *
		 * We need to count up the number of loops in this test case. We'll declare
		 * number_loops for this and--this is important--start it at zero.
		 */
		int number_loops = 0;

		/*
		 * For each letter in fruit_name, we'll determine what it is, and then use
		 * that information to see how many loops are in the letter. We'll add this
		 * number to the running total, number_loops.
		 */
		for(int letter_counter = 0; letter_counter < number_letters; ++letter_counter)
		{
			switch(fruit_name[letter_counter])
			{

			case 'B':
				number_loops += 2;
				break;

			case 'A':
			case 'D':
			case 'O':
			case 'P':
			case 'Q':
			case 'R':
				number_loops += 1;
				break;

			default:
				/* All other letters: We don't need to do anything. */
				break;

			}  // end of switch statement [letter]

		}  // end of for statement [letter_counter]

		/*
		 * Time to deliver the output! We'll use the standard output function "printf"
		 * and tell it to display a string (format %s) and an integer (format %d) in
		 * specific positions inside the output sentence. At the end of the output
		 * sentence we'll move to a new line (\n).
		 */
		printf("%s has %d loops.\n", fruit_name, number_loops);

	}  // end of for statement [test_case_counter]

}  // end of main function