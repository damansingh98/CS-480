/*
Name: Damandeep Singh
Account: cssc0953
Course: CS480-02
*/

/*
 * specialcountmulthreads.c - this file implements the alphabetcountmulthreads function.
 */

#include <stdio.h> 
#include "count.h"
#include <dirent.h> 
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <pthread.h>




pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // mutex initializer


char *fileList[100]; // global fileList;
long *freq; // global frequency

struct thrd_strt{ // thread_structure to handle indexes
int first, last; 
};


/*
 Thread function: countsplchar(void *arg)
*/

void *countsplchar(void *arg){
  struct thrd_strt *th_st = (struct thrd_strt*) arg; // cast thread_struct to arg variable

  // print the first and last index to be proccessed in each thread
  printf("Thread id = %u starts processing files with index from %d to %d!\n", pthread_self(), th_st->first, th_st->last);
  
  FILE *fptr; //to open file

  // run a for loop from first index to last index

  for(int k = th_st->first; k <= th_st->last; k++){

     // **** START OF CRITICAL SECTION****
      pthread_mutex_lock(&mutex); 

    fptr = fopen(fileList[k], "r"); //open each file

    if (fptr == NULL){
      printf("Cannot open file\n"); //check for error
      exit(1);
    }else{
      // print the file that is currently being processed
      printf("Thread id = %u is processing file %s\n", pthread_self(), strrchr(fileList[k], '/')+1);
  
      char buff[256]; // buff to store content of file

      while((fgets(buff, sizeof(buff), fptr)) != NULL){
       char * token = strtok(buff, "\t\n.,!;:?- \" "); 
        while(token != NULL){
          for(int g=0; token[g]; g++){
            token[g] = tolower(token[g]); //update and lowercase each token
          }
          if(strcmp(token, "he") == 0){ //check for "he"
            freq[0]++; //update
          }else if(strcmp(token, "she") == 0){ //check for "she"
            freq[1]++; //update
          }else if(strcmp(token, "they") == 0){ //check for "they"
            freq[2]++; //update
          }else if(strcmp(token, "him") == 0){ //check for "him"
            freq[3]++; //update
          }else {
            if(strcmp(token, "me") == 0){ // check for "me"
            freq[4]++; //update
            }
          }
          token = strtok(NULL, "\t\n.,!;:?- \" ");// update each token
        }

      } 
       
    }
    fclose(fptr); //close file

    pthread_mutex_unlock(&mutex); 
  // ****END OF CRITICAL SECTION****
  }
  printf("Thread id = %u is done !\n", pthread_self()); // print which thread is done.
  
  pthread_exit(0); //exit thread

}


void specialcountmulthreads(char *path, char *filetowrite, long specialfreq[], int num_threads)
{
  // directory and file handlers
  DIR *directory;
  struct dirent* file;
  FILE* fptr;

  // count # of files
  const int file_count = count_txt_files(path);

 // used to print into result.txt
  const char *spl_wrd[] = {"he", "she", "they", "him", "me"};

  int i = 0;
	directory  = opendir(path); //open directory
  if(directory == NULL){
    printf("Error opening directory"); // exit if an error occurs
    exit(1);
  }else {
    while((file = readdir(directory))!= NULL){
      if(isTxt(file->d_name) && i < file_count){ //check if the file is a txt file
        fileList[i] = (char*)malloc(strlen(path) + strlen(file->d_name) + 2); // create space for each filename
        strcpy(fileList[i], path); // copy the ../data path to filelist
        strcat(fileList[i], "/"); // concat ../data/
        strcat(fileList[i], file->d_name); // concat ../data/input_xx.txt
        i++; // increment each time
      }
    }
  }
   closedir(directory); // close directory
  

  struct thrd_strt args[num_threads]; // resulting args(answers)
  pthread_t tids[num_threads]; // create thread ids

  for(int i = 0; i < num_threads; i++){
    // set first index for each thread
    args[i].first = i*(file_count/num_threads); //each iteration 0*(31/3) = 0, 1*(31/3) = 10

    if(i == num_threads-1){ // last thread must handle leftover files
      args[i].last = file_count-1; // last index is set to 30 (31 files)
    }else{
     args[i].last = (args[i].first + (file_count/num_threads))-1; //add to first value based on file_count/num_threads
      
    }
    
    pthread_attr_t attr; // attributes 
    pthread_attr_init(&attr); // attributes initializer
    pthread_create(&tids[i], &attr, countsplchar, &args[i]); // create threads
  }

    freq = specialfreq; // after processing is finished update the freq

  // wait until all threads have finished
  for(int i = 0; i < num_threads; i++){
    pthread_join(tids[i], NULL);
  }
 
 
int q =0;
fptr = fopen(filetowrite, "w"); // write to result.txt
if(fptr == NULL){
  printf("Cannot open file to write\n"); // exit if error occurs
  exit(1);
}else{
  while(q < SPECIALSIZE){
    fprintf(fptr, "%s -> %ld\n", spl_wrd[q], specialfreq[q]); // write to file
    q++; // increment

  }

}
fclose(fptr); // close file

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
  char *dot_file = strrchr(fileName, '.'); // last occurence of . 
  if(dot_file != NULL){
    int cmpr = strcmp(dot_file, ".txt"); // check after . is .txt
  if(cmpr == 0){
    return 1; // return true
  }else{
    return 0; // otherwise false
  }
  }else {
    return 0; // overall false if none of other condtions match
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
  directory = opendir(path); // open directory
  if(directory == NULL){
    printf("Cannot open directory"); //exit if error occurs
    exit(1);
  }else {
    while((file = readdir(directory)) != NULL){ // iterate over directory
      if(isTxt(file->d_name)){ // check whether file is .txt
        count++;
      }else{
        continue; // otherwise continue
      }

    }
  }
  closedir(directory); // close directory
  return count; // return count
  
}