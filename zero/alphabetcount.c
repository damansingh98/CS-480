/*
* Name: Damandeep Singh
* Account: cssc0953
* Course: CS 480-02
* alphabetcount.c - This file implements alphabetlettercount function
*/

#include <stdio.h> 
#include "count.h"
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>


void alphabetlettercount(char *path, char *filetowrite, long alphabetfreq[])
{


DIR *directory;
struct dirent* file;
int file_count = count_txt_files(path); // stores a total count of files in directory
char* fileList[file_count]; // A file list with size of number of files
char *getFileName;
int total_length;
FILE *fptr;
int ch, index;
int i =0;


directory = opendir(path); 
if(directory == NULL){
   printf("Error opening directory");
   exit(1);
}else{
while((file = readdir(directory)) != NULL){
   getFileName = file->d_name; // get file name
   if(isTxt(getFileName) && i < file_count){ // check whether the file is a ".txt"
   total_length = strlen(path)+strlen(getFileName)+2; // total length for each block of fileList
   fileList[i] = (char *)malloc(total_length); //space is allocated in fileList based on the total length
   strcpy(fileList[i], path);
   strcat(fileList[i], "/");
   strcat(fileList[i], getFileName); // full path is stored in fileList such as "../data/input_00.txt"
   i++;
   }else {
      continue;
   }
}
}
closedir(directory);


// Open each file for reading one by one and update the alphabetfreq array in real time
for (int k = 0; k < file_count; k++){
fptr = fopen(fileList[k], "r");
if(fptr == NULL){
   printf("Error cannot open file\n");
   exit(1);
}else {
while((ch = fgetc(fptr))!= EOF){
   if(ch >= 'a' && ch <= 'z'){
      index = (ch-'a')+26; // all lowercase frequencies are stored between 26-52 indexes inclusive
      alphabetfreq[index]++;
   }else if(ch >= 'A' && ch <= 'Z'){
      index = (ch -'A'); // all uppercase frequencies letters are stored between 0-25 indexes inclusive
      alphabetfreq[index]++;
   }else {
      continue;
   }
}
}
fclose(fptr);
}

/**
 * Writing into file operations 
 */

int j, p;
int sz = ALPHABETSIZE/2;
p = sz; 

// open file in writing mode
fptr = fopen(filetowrite, "w");
if(fptr == NULL){
   printf("Error cannot open file\n");
   exit(1);
}else {
   while(j < sz){ //write all uppercase frequencies into the file (0-26) 
   fprintf(fptr, "%c -> %ld\n", (char)(j+65), alphabetfreq[j]);
   j++;
   }
}
fclose(fptr);

// open file again in "append" mode
fptr = fopen(filetowrite,"a");
if(fptr == NULL){
   printf("Error cannot open file\n");
   exit(1);
}else{
while(p < ALPHABETSIZE){ //append all lowercase frequencies into the file
   fprintf(fptr, "%c -> %ld\n", (char)(p+71), alphabetfreq[p]);
   p++;
}
}
fclose(fptr);

}


/**
 * isTxt(fileName): A function to check whether the file type is ".txt"
 * 
 * return: an int value -> 1 (True) or 0 (False) 
 */
int isTxt(char *fileName){
if(fileName == NULL){
   return 0;
}
   char *dot_file = strrchr(fileName, '.'); // last occurence of '.' in fileName
   if(dot_file != NULL){
   int cmpr = strcmp(dot_file, ".txt"); // compare .txt matches .txt
   if(cmpr == 0){
      return 1; //return 1 if match occurs
   }else {
      return 0; // otherwise false
   }
   }else {
      return 0;
   }
   }

/**
 * count_txt_files(path): A function to return a count for total
 *                        number of files present in a given path/directory
 *
 * return: an int value
 */

int count_txt_files(char *path){
   int count = 0;
   DIR* directory;
   struct dirent* file;
   // open directory
   directory = opendir(path);
   if(directory == NULL){
      printf("Cannot open directory");
      exit(1);
   }else {
      while((file = readdir(directory)) != NULL){
         char *getFileName = file->d_name;
         if(isTxt(getFileName)){ //check if the file is a text file
            count++; // increment count by 1
         }else {
            continue;
         }

      }
   }
   closedir(directory);
   return count;
}

