/*
Name: Damandeep Singh
Account: cssc0953
Class: CS480-02
*/

#include <stdio.h> 
#include <unistd.h> 
#include <sys/types.h>
#include <stdlib.h> 
#include <sys/wait.h> 


int main(void) {
 
 pid_t child_one, child_two; // two pids to be forked
 pid_t get_first_process, get_second_process; //used to store current pids given from wait() 
 char *first_args[] = {"./testalphabet", NULL}; // list of argurments for first child to execute
 char *second_args[] = {"./testspecial", NULL}; // list of arguments for second child to execute
 

 if((child_one = fork()) == 0){ // first child created 
   printf("CHILD <PID:%ld> process is executing testalphabet program!\n", (long) getpid()); // print execution statement
   execv(first_args[0], first_args); // execute the ./testalphabet executable
   exit(0); // exit first child process using exit()
 }
  else if((child_two = fork()) == 0){ // second child created
   printf("CHILD <PID:%ld> process is executing testspecial program!\n", (long) getpid()); // print execution statement
   execv(second_args[0],second_args); //execute the ./testspecial executable
   exit(0); // exit second child process using exit()
 }

else{ // parent process

 get_first_process = wait(NULL); // wait for any child process to finish execution

 if(get_first_process == child_one){ // check if the pid matches first child's pid
 printf("CHILD <PID:%ld> process has done with testalphabet program! See the results above!\n",(long) get_first_process); // print ending statement
 }
 else{ // otherwise the other child process is done executing
   printf("CHILD <PID:%ld> process has done with testspecial program! See the results above!\n", (long) get_first_process); 
 }

 get_second_process = wait(NULL); // wait for any child process to finish execution

 if(get_second_process == child_two){ // check if the pid matches second child's pid
 printf("CHILD <PID:%ld> process has done with testspecial program! See the results above!\n", (long) get_second_process); 
 }
 else{ // otherwise the other child process is done executing
 printf("CHILD <PID:%ld> process has done with testalphabet program! See the results above!\n", (long) get_second_process);
 }

}
   return 0;

 }




 



