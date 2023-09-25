// Nicholas Mohamed
// I pledge my honor that i have abided by the stevens honor pledge 
// all the extra credit is done

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/stat.h> 
#include <limits.h>

#define BLUE "\x1b[34;1m"
#define DEFAULT "\x1b[0m"
#define GREEN "\x1b[32;1m"
#define MAGENTA "\x1b[35;1m"

// Global variable to track if SIGINT was received
volatile sig_atomic_t interrupted = 0;
// Signal handler for SIGINT
void handle_sigint(int sig) {
    interrupted = 1;
}

void ls_command(const char *dir_path) {
    DIR *dir;
    struct dirent *entry;
    struct stat sb;
    
    dir = opendir(dir_path);
    if (!dir) {
        fprintf(stderr, "Error: Directory doesn't exist.\n");
        return;
    }
    
    while ((entry = readdir(dir)) != NULL) {
        // Skip hidden files and directories (those starting with a dot)
        if (entry->d_name[0] == '.') {
            continue;
        }
        
        stat(entry->d_name, &sb);
        if (S_ISDIR(sb.st_mode)) {
            fprintf(stdout, "%s%s%s\n", GREEN, entry->d_name, DEFAULT);
        } else {
            fprintf(stdout, "%s\n", entry->d_name);
        }
    }
    
    closedir(dir);
}

// Function to implement the find command
void find_command(const char *directory, const char *filename) {
    struct stat stats;
    stat(directory, &stats);
    
    if (!S_ISDIR(stats.st_mode)) {
        fprintf(stderr, "'%s' is not a directory\n", directory);
    } else {
        DIR *dp = opendir(directory);
        if (dp) {
            struct dirent *d;
            while ((d = readdir(dp)) != NULL) {
                if (strcmp(d->d_name, filename) == 0) {
                    char relative_path[PATH_MAX];
                    char absolute_path[PATH_MAX];
                    
                    snprintf(relative_path, sizeof(relative_path), "%s/%s", directory, d->d_name);
                    realpath(relative_path, absolute_path);
                    
                    fprintf(stdout, "%s\n", absolute_path);
                }
            }
            closedir(dp);
        }
    }
}
// Function to implement the stat command
void stat_command(const char *file_path) {
    struct stat sb;
    
    if (stat(file_path, &sb) == -1) {
        perror("stat");
        return;
    }
    
    fprintf(stdout, "File: %s\n", file_path);
    fprintf(stdout, "Size: %lld bytes\n", (long long)sb.st_size);
    fprintf(stdout, "Mode: %o\n", sb.st_mode);
    fprintf(stdout, "User ID: %d\n", sb.st_uid);
    fprintf(stdout, "Group ID: %d\n", sb.st_gid);
    fprintf(stdout, "Inode number: %llu\n", (unsigned long long)sb.st_ino);
}
// Function to implement the tree command
void tree_command(const char *dir_path, int depth, int level) {
    DIR *dir;
    struct dirent *entry;
    struct stat sb;
    
    if (level > depth && depth != -1) {
        return;
    }
    
    dir = opendir(dir_path);
    if (!dir) {
        fprintf(stderr, "Error: Directory doesn't exist.\n");
        return;
    }
    
    while ((entry = readdir(dir)) != NULL) {
        // Skip hidden files and directories (those starting with a dot)
        if (entry->d_name[0] == '.') {
            continue;
        }
        
        for (int i = 0; i < level; i++) {
            printf("│   ");
        }
        
        stat(entry->d_name, &sb);
        if (S_ISDIR(sb.st_mode)) {
            printf("├── %s%s%s\n", MAGENTA, entry->d_name, DEFAULT);
            char new_dir_path[PATH_MAX];
            snprintf(new_dir_path, sizeof(new_dir_path), "%s/%s", dir_path, entry->d_name);
            tree_command(new_dir_path, depth, level + 1);
        } else {
            printf("├── %s\n", entry->d_name);
        }
    }
    
    closedir(dir);
}

int main() {
    char input[1024];
    char *args[64];
    struct passwd *pw;
    char *dir;
    char *token;
    int status;
    
    // Register the signal handler for SIGINT
    if (signal(SIGINT, handle_sigint) == SIG_ERR) {
        fprintf(stderr, "Error: Cannot register signal handler. %s.\n", strerror(errno));
        return EXIT_FAILURE;
    }
    // Main loop
    while (1) {
        // Get current working directory
        dir = getcwd(NULL, 0);
        if (!dir) {
            fprintf(stderr, "Error: Cannot get current working directory. %s.\n", strerror(errno));
            return EXIT_FAILURE;
        }
        // Print the prompt with the current working directory in blue
        fprintf(stdout, "%s[%s]%s > ", BLUE, dir, DEFAULT);
        free(dir);
        // Read user input
        if (!fgets(input, sizeof(input), stdin)) {
            if (interrupted) {
                interrupted = 0;
                continue;
            } else {
                fprintf(stderr, "Error: Failed to read from stdin. %s.\n", strerror(errno));
                return EXIT_FAILURE;
            }
        }
        // Tokenize user input and store in args array
        int i = 0;
        token = strtok(input, " \t\n");
        while (token) {
            args[i++] = token;
            token = strtok(NULL, " \t\n");
        }
        args[i] = NULL;
        // If no command was entered, continue to the next iteration
        if (!args[0]) {
            continue;
        }
        // Built-in command: cd
        if (strcmp(args[0], "cd") == 0) {
            if (i > 2) {
                fprintf(stderr, "Error: Too many arguments to cd.\n");
            } else if (i == 1 || strcmp(args[1], "~") == 0) {
                pw = getpwuid(getuid());
                if (!pw) {
                    fprintf(stderr, "Error: Cannot get passwd entry. %s.\n", strerror(errno));
                } else {
                    chdir(pw->pw_dir);
                }
            } else {
                if (chdir(args[1]) == -1) {
                    fprintf(stderr, "Error: Cannot change directory to '%s'. %s.\n", args[1], strerror(errno));
                }
            }
            // Built-in command: exit
        } else if (strcmp(args[0], "exit") == 0) {
            return EXIT_SUCCESS;
        } else if (strcmp(args[0], "ls") == 0) { // Built-in command: ls
            if (i > 2) {
                fprintf(stderr, "Error: Too many arguments to ls.\n");
            } else if (i == 1) {
                ls_command(".");
            } else {
                ls_command(args[1]);
            }
            // Built-in command: find
        } else if (strcmp(args[0], "find") == 0) {
            if (i != 3) {
                fprintf(stderr, "Error: find requires exactly two arguments: <directory> <filename>.\n");
            } else {
                find_command(args[1], args[2]);
            }
            // Built-in command: stat
        } else if (strcmp(args[0], "stat") == 0) {
            if (i != 2) {
                fprintf(stderr, "Error: stat requires exactly one argument: <file_path>.\n");
            } else {
                stat_command(args[1]);
            }
        } else if (strcmp(args[0], "tree") == 0) {
            if (i > 2) {
                fprintf(stderr, "Error: Too many arguments to tree.\n");
            } else if (i == 1) {
                tree_command(".", -1, 0); // No depth limit, starting level 0
            } else {
                tree_command(args[1], -1, 0); // No depth limit, starting level 0
            }
        } else {
            // All other commands executed using fork and exec
            pid_t pid = fork();
            if (pid == -1) {
                fprintf(stderr, "Error: fork() failed. %s.\n", strerror(errno));
            } else if (pid == 0) {
                if (execvp(args[0], args) == -1) {
                    fprintf(stderr, "Error: exec() failed. %s.\n", strerror(errno));
                    return EXIT_FAILURE;
                }
            } else {
                if (wait(&status) == -1) {
                    fprintf(stderr, "Error: wait() failed. %s.\n", strerror(errno));
                }
            }
        }
        
    }
    
    return EXIT_SUCCESS;
}
