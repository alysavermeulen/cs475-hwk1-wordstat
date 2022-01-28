/**
 * Implements the functions declared in stats.h
 * (calculating and printing word stats)
 *
 * @author Alysa
 */

#include "stats.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/**
 * Initializes the statistics structure
 * @param st an uninitialized WordStats struct
 * @return an initialized WordStats struct 
 */
WordStats initStats(WordStats st)
{
	int i;
	for (i = 0; i < ALPHABET_SIZE; i++){
		st.histo[i] = 0;
	}
	st.wordCount = 0;
	st.vowelCount = 0;
	st.consonantCount = 0;
	return st;
}

/**
 * Updates vowels and consonants in the struct
 * @param st WordStats structure
 * @param str the user-input string
 * @return an updated WordStats struct 
 */
WordStats updateVowelCons(WordStats st, const char str[])
{
	int i = 0;
	char c;
	while (str[i] != '\0'){ // while there are still characters left in the string
		c = tolower(str[i]);
		if (isalpha(c)){
			if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
				st.vowelCount++;
			}
			else{
				st.consonantCount++;
			}
		}
		i++;
	}
	return st;
}

/**
 * Updates word count in the struct
 * @param st 
 * @param str 
 * @return an updated WordStats struct 
 */
WordStats updateWordCount(WordStats st, const char str[])
{
	const char s[2] = " "; // words are space-delimited
	char* str2 = strdup(str); // must make copy of constant string before tokenizing it
	char* token = NULL;
	token = strtok(str2,s); // get first token
	while (token != NULL){  // go through tokens
		if (isalpha(token[0])){ // if first char in token is alphabetical, count as word
			st.wordCount++;
		}
		token = strtok(NULL,s);
	}
	free(str2); // free the copy
	return st;
}

/**
 * Outputs vowel and consonant stats
 * @param st WordStats structure
 */
void printVowelConsFreq(WordStats st)
{
	int total = st.vowelCount + st.consonantCount;
	float vowelFreq = (st.vowelCount/(float)total)*100;
	float consonantFreq = (st.consonantCount/(float)total)*100;
	printf("Vowels = %d (%.2f%%), ", st.vowelCount, vowelFreq);
	printf("Consonants = %d (%.2f%%), ", st.consonantCount, consonantFreq);
	printf("Total = %d\n", total);
}

/**
 * Outputs word count
 * @param st WordStats structure
 */
void printWordCount(WordStats st)
{
	printf("Words: %d\n", st.wordCount);
}

/**
 * Outputs histogram vertically
 * @param st WordStats structure
 */
void printHistogram(WordStats st)
{
	int i, a, histHeight = 0;
	char c;
	for (i = 0; i < ALPHABET_SIZE; i++){ // finding histogram height (highest frequency)
		if (st.histo[i] > histHeight){
			histHeight = st.histo[i];
		}
	}
	for (i = histHeight; i >= 0; i--){ // using histogram height for printing vertically
		for (a = 0; a < ALPHABET_SIZE; a++){
			if (st.histo[a] > i){
				printf("%*c ", 1, '*'); 
			} else{
				printf("%*c ", 1, ' ');
			}
		}
    	printf("\n");
	}
	for (c = 'a'; c <= 'z'; c++){
		printf("%c ", c);
    }
	printf("\n");
	i = 0;
	for (c = 'a'; c <= 'z'; c++){
		printf("%d ", st.histo[i]);
		i++;
    }
	printf("\n");
}

/**
 * Update the histogram
 * @param histo	the histogram
 * @param str	the string used to update the histogram
 */
void updateHistogram(int histo[], const char str[])
{
	// updates the frequencies in the histogram, given the letters in the input string
	int i = 0, j = 0;
	char x, c;
	while (str[i] != '\0'){
		x = tolower(str[i]);
		if (isalpha(x)){
			for (c = 'a'; c <= 'z'; c++){
				if (x == c){
					histo[j]++;
				}
				j++;
    		}
		}
		j=0;
		i++;
	}
}
