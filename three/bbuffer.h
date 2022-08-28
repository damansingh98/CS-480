/*
 * Name: Damandeep Singh
 * Account: cssc0953
 * Course: CS 480
 * This header file is for programming #3.    
 *  
 */


#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#define BUFFER_SIZE 5   // rounded buffer size

#define PRODUCERS 3  // number of producers
#define CONSUMERS 5  // number of consumers

#define ITERATIONS 60   // number of actions producers/consumers perform 
#define PRODUCER_ITERATIONS (ITERATIONS / PRODUCERS)  //number of actions each producer performs
#define CONSUMER_ITERATIONS (ITERATIONS / CONSUMERS) //number of actions each consumer performs

typedef struct {
    int value[BUFFER_SIZE];
    int next_in, next_out;
} buffer_t;    // struct of bounded buffer


buffer_t buffer;   //global variable: rounded buffer

pthread_t consumer_tid[CONSUMERS], producer_tid[PRODUCERS]; // producer and consumer threads


pthread_mutex_t mutex; // mutex variable

sem_t empty, full; // sempahore variables to represent empty and full buffer



void initilization(); // intitalization function

int insert_item(int item, long int id); // thread safe(?) function to insert items to the bounded buffer

int remove_item(int *item, long int id); // thread safe(?) function to remove items to the bounded buffer

void * producer(void *param);  // producer - will iterate PRODUCER_ITERATION times and call the corresponding function to insert an integer to the bounded buffer

void * consumer(void *param); // consumer - will iterate CONSUMER_ITERATION times and call the corresponding function to remove an integer from the bounded buffer

