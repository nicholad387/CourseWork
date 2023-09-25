
// Nicholas Mohamed
// Pledge: I pledge my honor that I have abided by the Stevens honor pledge
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    // Check if the correct number of arguments are provided
    if (argc != 3) {
        printf("Usage: %s <directory> <permissions string>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    // Declare pipes for communication between processes
    int pfind_to_sort_pipe[2], sort_to_parent_pipe[2];
    
    // Create the pipes and check for errors
    if (pipe(pfind_to_sort_pipe) == -1 || pipe(sort_to_parent_pipe) == -1) {
        perror("Error creating pipe");
        return EXIT_FAILURE;
    }
    
    // Fork the pfind process and check for errors
    pid_t pfind_pid = fork();
    if (pfind_pid == -1) {
        perror("Error forking pfind process");
        return EXIT_FAILURE;
    }
    
    // Child process: pfind
    if (pfind_pid == 0) {
        // Redirect stdout to the pfind_to_sort pipe's write end
        dup2(pfind_to_sort_pipe[1], STDOUT_FILENO);
        
        // Close all unneeded file descriptors
        close(pfind_to_sort_pipe[0]);
        close(pfind_to_sort_pipe[1]);
        close(sort_to_parent_pipe[0]);
        close(sort_to_parent_pipe[1]);
        
        // Execute pfind with the provided arguments and check for errors
        execl("./pfind", "pfind", argv[1], argv[2], NULL);
        perror("Error: pfind failed.");
        exit(EXIT_FAILURE);
    }
    
    // Fork the sort process and check for errors
    pid_t sort_pid = fork();
    if (sort_pid == -1) {
        perror("Error forking sort process");
        return EXIT_FAILURE;
    }
    
    // Child process: sort
    if (sort_pid == 0) {
        // Redirect stdin to the pfind_to_sort pipe's read end
        // Redirect stdout to the sort_to_parent pipe's write end
        dup2(pfind_to_sort_pipe[0], STDIN_FILENO);
        dup2(sort_to_parent_pipe[1], STDOUT_FILENO);
        
        // Close all unneeded file descriptors
        close(pfind_to_sort_pipe[0]);
        close(pfind_to_sort_pipe[1]);
        close(sort_to_parent_pipe[0]);
        close(sort_to_parent_pipe[1]);
        
        // Execute sort and check for errors
        execl("/usr/bin/sort", "sort", NULL);
        perror("Error: sort failed.");
        exit(EXIT_FAILURE);
    }
    
    // Parent process
    
    // Close unneeded file descriptors in the parent process
    close(pfind_to_sort_pipe[0]);
    close(pfind_to_sort_pipe[1]);
    close(sort_to_parent_pipe[1]);
    
    // Read and print data from the sort_to_parent pipe, count lines
    char buffer[1024];
    ssize_t nbytes;
    int line_count = 0;
    int error_occurred = 0;
    
    // Read data from the sort_to_parent pipe until EOF is reached
    while ((nbytes = read(sort_to_parent_pipe[0], buffer, sizeof(buffer) - 1)) > 0) {
        // Null-terminate the buffer to make it a valid string
        buffer[nbytes] = '\0';
        
        // Print the buffer to stdout
        printf("%s", buffer);
        
        // Count the number of lines ('\n' characters) in the buffer
        for (ssize_t i = 0; i < nbytes; i++) {
            if (buffer[i] == '\n') {
                line_count++;
            }
        }
    }
    
    // Close the read end of the sort_to_parent pipe
    close(sort_to_parent_pipe[0]);
    
    // Wait for both child processes to finish and retrieve their exit status
    int pfind_status, sort_status;
    waitpid(pfind_pid, &pfind_status, 0);
    waitpid(sort_pid, &sort_status, 0);
    
    // Check if either child process encountered an error
    if (!WIFEXITED(pfind_status) || !WIFEXITED(sort_status) ||
        WEXITSTATUS(pfind_status) != EXIT_SUCCESS || WEXITSTATUS(sort_status) != EXIT_SUCCESS) {
            error_occurred = 1;
        }
    
    // If no error occurred, print the total line count
    if (!error_occurred) {
        printf("\nTotal lines: %d\n", line_count);
    }
    
    // Return the appropriate exit status based on whether an error occurred
    return error_occurred ? EXIT_FAILURE : EXIT_SUCCESS;
}
