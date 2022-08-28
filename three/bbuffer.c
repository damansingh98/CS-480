/*
* Name: Damandeep Singh
* Course: CS 480
* Account: cssc0953
*/


#include <stdio.h> 
#include <stdlib.h> 
#include "bbuffer.h"
#include <semaphore.h>

void initilization()
{
    
    sem_init(&empty, 0, BUFFER_SIZE); // intialize a semaphore with an intital value of buffer_size (fixed size)
    sem_init(&full, 0, 0); // intialize a semaphore with intial value of 0 to represent there are no elements in buffer
    pthread_mutex_init(&mutex, NULL); // intialize mutex
     
}

/* *
 * insert_item - thread safe(?) function to insert items to the bounded buffer
 * @param item the value to be inserted
 * @return 0 in case of sucess -1 otherwise
 */
  
int insert_item(int item, long int id)
{
    /* Check and wait if the buffer is full. Ensure exclusive
     * access to the buffer and may use the existing code to insert an item.
     */   
     
    sem_wait(&empty); // check if there are empty space in the buffer (check empty > 0) and decrease the value empty sema.
    pthread_mutex_lock(&mutex); // mutex lock to ensure exclusive access per thread
    buffer.value[buffer.next_in] = item; // insert an item in the buffer
    
      
    printf("producer %ld: inserted item %d into buffer index %d\n", id, item, buffer.next_in);
       
    buffer.next_in = (buffer.next_in + 1) % BUFFER_SIZE; // move to available slot as per buffer size
    pthread_mutex_unlock(&mutex); // mutex unlock to ensure the critical region is now open for other threads
    sem_post(&full); // increments the full semaphore as we add an element into the buffer

    return 0;
}

/**
 * remove_item - thread safe(?) function to remove items to the bounded buffer
 * @param item the address of the variable that the removed value will be written
 * @return 0 in case of sucess -1 otherwise
 */
int remove_item(int *item, long int id)
{
    /* Check and wait if the buffer is empty. Ensure exclusive
     * access to the buffer and use the existing code to remove an item.
     */

    
    sem_wait(&full); // check if there are occupied space in the buffer (check full > 0) and decrease the value of full sema.
    pthread_mutex_lock(&mutex); // mutex lock to ensure exclusive access per thread
    *item = buffer.value[buffer.next_out]; // remove an item out of the buffer
    buffer.value[buffer.next_out] = -1;  // set the location of removed item to -1 representing an empty location
    
   
    printf("consumer %ld: removed item %d from buffer index %d\n", id, *item, buffer.next_out);
       
    buffer.next_out = (buffer.next_out + 1) % BUFFER_SIZE; // move to next available slot to remove an item as per buffer size
    pthread_mutex_unlock(&mutex);  // mutex unlock to ensure the critical region is now open
    sem_post(&empty); // increment the value of empty semaphore to represent an empty space is now available
    return 0;
}

/**
 * producer - will iterate PRODUCER_ITERATION times and call the corresponding
 * function to insert an integer to the bounded buffer
 * @param param an integer id of the producer used to distinguish between the
 * multiple producer threads
 * @return nothing
 */
void * producer(void *param)
{
    int item, i;
    long int id = (long int)param;

    printf("producer %d started!\n", id);
    i = PRODUCER_ITERATIONS;
    while (i--) {
	  sleep(rand() % 3);

	item = rand() % 10000;
	if (insert_item(item, id))
	    printf("Error while inserting to buffer\n");
    }

    pthread_exit(0);
}

/**
 * consumer - will iterate CONSUMER_ITERATION times and call the corresponding
 * function to remove an integer from the bounded buffer
 * @param param an integer id of the producer used to distinguish between the
 * multiple consumer threads
 * @return nothing
 */
void * consumer(void *param)
{
    int item, i;
    long int id = (long int)param;

    printf("consumer %d started!\n", id);
    i = CONSUMER_ITERATIONS;
    while (i--) {
	sleep(rand() % 3);

	if (remove_item(&item, id))
	    printf("Error while removing from buffer\n");
    }

    pthread_exit(0);
}
