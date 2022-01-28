/**
 * Contains the main() function for allowing user input
 * and displaying requested output.
 *
 * @author Alysa
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "stats.h"
#include "menu.h"

#define MAX_INPUT_LEN 128 /** maximum length of input users can enter */

/**
 * Main function
 * 
 * @param argc the number of command line arguments (ignore for this assignment)
 * @param argv an array of command line arguments (ignore for this assignment)
 */
int main(int argc, char **argv)
{
	char input[MAX_INPUT_LEN]; // holds user-input string
	WordStats st;
	st = initStats(st);
	int choice = MENU_RET; // begin by allowing user to enter strings
	while (choice != MENU_EXIT){
		if (choice!=MENU_VC && choice!=MENU_WC && choice!=MENU_HISTO && choice!=MENU_RET){
			printf("Error: Unknown option %d. Try again.\n", choice);
		}
		if (choice == MENU_VC){
			printVowelConsFreq(st);
		}
		if (choice == MENU_WC){
			printWordCount(st);
		}
		if (choice == MENU_HISTO){
			printHistogram(st);
		}
		if (choice == MENU_RET){
			int update = 1; // if 1, user is entering strings; if 0, user has stopped
			printf("Enter strings (# to stop):\n");
			while (update){ // while user is still entering strings
				fgets(input, MAX_INPUT_LEN, stdin);
				if (input[0] == '#' && !isprint(input[1])){ // if user has chosen to stop
					update = 0;
				}
				else if (!isspace(input[0])){ // if user has entered another string
					st = updateVowelCons(st, input);
					st = updateWordCount(st, input);
					updateHistogram(st.histo, input);
				}
			}
		}
		printf("\n");
		choice = getMenuOption();
	}
	printf("Exiting...\n");
	return 0;
}