#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    int fd1, fd2;
    char sentence[100];
    char buffer[200];

    // FIFO file paths
    char *pipe1 = "/tmp/pipe1"; // Pipe for sending sentences
    char *pipe2 = "/tmp/pipe2"; // Pipe for receiving results

    // Create named pipes (FIFOs)
    mkfifo(pipe1, 0666);
    mkfifo(pipe2, 0666);

    while (1) {
        printf("Enter a sentence: ");
        // Use fgets instead of read for better input handling
        if (fgets(sentence, sizeof(sentence), stdin) == NULL) {
            perror("Error reading input");
            continue;
        }

        // Remove newline character from fgets input if present
        sentence[strcspn(sentence, "\n")] = 0;

        // Open first pipe for writing the sentence
        fd1 = open(pipe1, O_WRONLY);
        if (fd1 == -1) {
            perror("Error opening pipe1 for writing");
            continue;
        }
        write(fd1, sentence, strlen(sentence) + 1);
        close(fd1);

        // Open second pipe for reading the output
        fd2 = open(pipe2, O_RDONLY);
        if (fd2 == -1) {
            perror("Error opening pipe2 for reading");
            continue;
        }
        read(fd2, buffer, sizeof(buffer));
        printf("Processed Output: \n%s", buffer);
        close(fd2);
    }

    return 0;
}
