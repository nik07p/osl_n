#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>

int count_characters(const char *sentence) {
    return strlen(sentence);
}

int count_words(const char *sentence) {
    int count = 0;
    int in_word = 0;

    for (int i = 0; sentence[i] != '\0'; i++) {
        if (sentence[i] == ' ' || sentence[i] == '\n') {
            in_word = 0;
        } else if (in_word == 0) {
            in_word = 1;
            count++;
        }
    }
    return count;
}

int count_lines(const char *sentence) {
    int count = 0;
    for (int i = 0; sentence[i] != '\0'; i++) {
        if (sentence[i] == '\n') {
            count++;
        }
    }
    return count + 1; // At least one line
}

int main() {
    int fd1, fd2;
    char sentence[100], output[200];
    FILE *file;

    // FIFO file paths
    char *pipe1 = "/tmp/pipe1"; // Pipe for receiving sentences
    char *pipe2 = "/tmp/pipe2"; // Pipe for sending results

    while (1) {
        // Open first pipe for reading the sentence
        fd1 = open(pipe1, O_RDONLY);
        if (fd1 == -1) {
            perror("Error opening pipe1 for reading");
            continue;  // Retry if pipe is not yet open or is empty
        }
        printf("Receiver: Reading from pipe1...\n");

        ssize_t bytes_read = read(fd1, sentence, sizeof(sentence));
        if (bytes_read < 0) {
            perror("Error reading from pipe1");
            close(fd1);
            continue;
        }

        printf("Receiver: Received sentence: %s\n", sentence);
        close(fd1);

        // Count characters, words, and lines
        int num_chars = count_characters(sentence);
        int num_words = count_words(sentence);
        int num_lines = count_lines(sentence);

        // Prepare output
        snprintf(output, sizeof(output), "Character count: %d\nWord count: %d\nLine count: %d\n", num_chars, num_words, num_lines);

        // Write the output to a file
        file = fopen("/tmp/output.txt", "w");
        if (file == NULL) {
            perror("Error opening output file");
            continue;
        }
        fprintf(file, "%s", output);
        fclose(file);

        // Open second pipe for writing the content of the file
        fd2 = open(pipe2, O_WRONLY);
        if (fd2 == -1) {
            perror("Error opening pipe2 for writing");
            continue;
        }
        printf("Receiver: Writing to pipe2...\n");
        write(fd2, output, strlen(output) + 1);
        close(fd2);
    }

    return 0;
}
