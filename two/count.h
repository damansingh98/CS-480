/* charcount.h - This header file include type definitions (including function prototypes) and macros 
   used for the programing assignment two.
*/

/*
Name: Damandeep Singh
Account: cssc0953
Course: CS480-02
*/

#include <stdio.h> 

#define SPECIALSIZE 5     //The total number of special word "he","she","they","him" and "me" (case insensitive)

void specialcountmulthreads(char *path, char *filetowrite, long specialfreq[], int num_threads);


int count_txt_files(char *path);

void *countsplchar(void *arg);

int isTxt(char *fileName);