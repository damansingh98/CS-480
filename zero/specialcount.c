/*
 * Name: Damandeep Singh
 * Account: cssc0953
 * Course: CS 480-02
 * specialcount.c - this file implements the specialcount function.
 */


#include <stdio.h> 
#include "count.h"
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


void specialcount(char *path, char *filetowrite, long charfreq[])
{
  DIR *directory;
  struct dirent* file;
  int file_count = count_txt_files(path);
  char* fileList[file_count];
  char* getFileName;
  int total_length;
  FILE *fptr;
  int ch, index;
  int i = 0;
  char buf[500];
  const char delimit[] = "\t\n.,!;:?- \" "; //all delimiters
  char* token; // a pointer variable to store each token
  const char *spl_wrd[] = {"he", "she", "they", "him", "me"};
  

  directory  = opendir(path);
  if(directory == NULL){
    printf("Error opening directory");
    exit(1);
  }else {
    while((file = readdir(directory))!= NULL){
      getFileName = file->d_name;
      if(isTxt(getFileName) && i < file_count){
        total_length  = strlen(path) + strlen(getFileName) + 1;
        fileList[i] = (char*)malloc(total_length);
        strcpy(fileList[i], path);
        strcat(fileList[i], "/");
        strcat(fileList[i], getFileName);
        i++;
      }else{
        continue;
      }
    }
  }
  closedir(directory);

  for(int k = 0; k < file_count; k++){
    fptr = fopen(fileList[k], "r");
    if(fptr == NULL){
      printf("Cannot open file");
      exit(1);

    }else {
      while(fgets(buf, sizeof(buf), fptr)){
        token = strtok(buf, delimit);
        while(token != NULL){
          for(int g = 0; token[g]; g++){
            token[g] = tolower(token[g]);
          }
          if(strcmp(token, "he") == 0){
            charfreq[0]++;
          }else if(strcmp(token, "she") == 0){
            charfreq[1]++;
          }else if(strcmp(token, "they") == 0){
            charfreq[2]++;
          }else if(strcmp(token, "him") == 0){
            charfreq[3]++;
          }else {
            if(strcmp(token, "me") == 0){
              charfreq[4]++;
            }
          }
          token = strtok(NULL, delimit);
        }
      }
    }
    fclose(fptr);
  }
  
  int q;
  fptr = fopen(filetowrite, "w");
  if(fptr == NULL){
    printf("Cannot open file to write\n");
    exit(1);
  }else {
    while (q < SPECIALSIZE){
      fprintf(fptr, "%s -> %ld\n", spl_wrd[q], charfreq[q]);
      q++;
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
  if(fileName== NULL){
    return 0;
  }
  char *dot_file = strrchr(fileName, '.');
  if(dot_file != NULL){
    int cmpr = strcmp(dot_file, ".txt");
  if(cmpr == 0){
    return 1;
  }else{
    return 0;
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
  DIR *directory;
  struct dirent* file;
  directory = opendir(path);
  if(directory == NULL){
    printf("Cannot open directory");
    exit(1);
  }else {
    while((file = readdir(directory)) != NULL){
      char *getFileName = file->d_name;
      if(isTxt(getFileName)){
        count++;
      }else{
        continue;
      }

    }
  }
  closedir(directory);
  return count;
  
}