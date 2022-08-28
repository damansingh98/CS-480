/* 
* Name: Damandeep Singh
* Account: cssc0953
* Course: CS 480-02
* charcount.h - This header file include type definitions (including function prototypes) and macros 
   used for the programing assignment zero.
*/

#include <stdio.h> 

#define ALPHABETSIZE 52     //The total number of alphabetical letter from A - Z and a - z(case sensitive)
#define SPECIALSIZE 5   // The total number of these special words: he, she, they, him, me 

// alphabetlettercount function definition
void alphabetlettercount(char *path, char *filetowrite, long alphabetfreq[]);

// isTxt function definition
int isTxt(char *fileName);

// count_txt_files function definition 
int count_txt_files(char *path);

// specialcount function definition 
void specialcount(char *path, char *filetowrite,  long charfreq[]);
