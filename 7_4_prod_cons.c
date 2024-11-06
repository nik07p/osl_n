#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 5  // Define the size of the buffer

int buffer[BUFFER_SIZE];  // Shared buffer
int in = 0, out = 0;      // Buffer indices for producer and consumer

// Declare semaphores and mutex
sem_t empty_slots;    // Counts empty slots in the buffer
sem_t filled_slots;   // Counts filled slots in the buffer
pthread_mutex_t mutex;  // Mutex to protect access to the buffer

// Producer function
void* producer(void* arg) {
    int item;
    while (1) {
        item = rand() % 10;  // Produce an item (random integer)

        sem_wait(&empty_slots);  // Wait if no empty slots are available
        pthread_mutex_lock(&mutex);  // Lock mutex to enter critical section

        // Add item to the buffer
        buffer[in] = item;
        printf("Producer produced: %d\n", item);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);  // Release mutex
        sem_post(&filled_slots);  // Signal that a new item is available

        sleep(2);  // Fixed sleep time to simulate production time
    }
}

// Consumer function
void* consumer(void* arg) {
    int item;
    while (1) {
        sem_wait(&filled_slots);  // Wait if no filled slots are available
        pthread_mutex_lock(&mutex);  // Lock mutex to enter critical section

        // Remove item from the buffer
        item = buffer[out];
        printf("Consumer consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);  // Release mutex
        sem_post(&empty_slots);  // Signal that a slot is now available

        sleep(2);  // Fixed sleep time to simulate consumption time
    }
}

int main() {
    pthread_t prod_thread, cons_thread;

    // Initialize the semaphores
    sem_init(&empty_slots, 0, BUFFER_SIZE);  // Initially all slots are empty
    sem_init(&filled_slots, 0, 0);           // No filled slots initially
    pthread_mutex_init(&mutex, NULL);         // Initialize mutex

    // Create producer and consumer threads
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    // Join threads (this code will run indefinitely)
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    // Cleanup
    sem_destroy(&empty_slots);
    sem_destroy(&filled_slots);
    pthread_mutex_destroy(&mutex);

    return 0;
}
