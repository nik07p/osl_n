#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

void *writer_thr(void *arg);
void *reader_thr(void *arg);
sem_t mutex;
sem_t wrt;
int readcount = 0, nwt, nrd;

int main() {
    int i;
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);
    pthread_t reader[100], writer[100];

    printf("Enter the number of readers:\n");
    scanf("%d", &nrd);
    printf("Enter the number of writers:\n");
    scanf("%d", &nwt);

    // Create writer threads
    for (i = 0; i < nwt; i++) {
        if (pthread_create(&writer[i], NULL, writer_thr, (void *)(long)i) != 0) {
            perror("Failed to create writer thread");
            exit(EXIT_FAILURE);
        }
    }

    // Create reader threads
    for (i = 0; i < nrd; i++) {
        if (pthread_create(&reader[i], NULL, reader_thr, (void *)(long)i) != 0) {
            perror("Failed to create reader thread");
            exit(EXIT_FAILURE);
        }
    }

    // Join writer threads
    for (i = 0; i < nwt; i++) {
        pthread_join(writer[i], NULL);
    }

    // Join reader threads
    for (i = 0; i < nrd; i++) {
        pthread_join(reader[i], NULL);
    }

    sem_destroy(&wrt);
    sem_destroy(&mutex);

    return 0;
}

void *reader_thr(void *arg) {
    long temp = (long)arg + 1; // Adjust index for output
    printf("\nReader %ld is trying to enter database for reading.", temp);
    sem_wait(&mutex); // Start critical section
    readcount++;
    if (readcount == 1) {
        sem_wait(&wrt); // First reader locks the writers
    }
    sem_post(&mutex); // End critical section

    printf("\nReader %ld is reading in database.", temp);
    sleep(1);

    sem_wait(&mutex); // Start critical section
    readcount--;
    if (readcount == 0) {
        sem_post(&wrt); // Last reader unlocks the writers
    }
    sem_post(&mutex); // End critical section

    printf("\nReader %ld has left the database.", temp);
    sleep(3);
    return NULL;  // Ensure to return NULL
}

void *writer_thr(void *arg) {
    long temp = (long)arg + 1; // Adjust index for output
    printf("\nWriter %ld is trying to enter database for modifying data.", temp);
    sem_wait(&wrt); // Writer requests access to the database
    printf("\nWriter %ld is writing in database.", temp);
    sleep(3);
    sem_post(&wrt); // Writer releases access to the database
    printf("\nWriter %ld has left the database.", temp);
    return NULL;  // Ensure to return NULL
}

