#include "stdiox.h"
//Nicholas Mohamed
//I pledge my honor that i have abided by the stevens honor pledge
// Helper Function to convert the integer to a string
void integer_to_string(int num, char* string, int* count) {
        while (num) {
                int temp = num % 10;
                char c = temp + '0';
                string[*count] = c;
                (*count)--;
                num = num / 10;
        }
}

int fprintfx(char* filename, char format, void* data) {
        // Check for invalid format specifier
        if (format != 's' && format != 'd') {
                errno = EIO;
                return -1;
        }
        // Check for NULL data when using 's' format specifier
        if (format == 's' && (char*)data == NULL) {
                errno = EIO;
                return -1;
        }
        // Check for NULL data when using 'd' format specifier
        if (format == 'd' && (int*)data == NULL) {
                errno = EIO;
                return -1;
        }
        // Declare a buffer to hold the formatted data
        char buff[PATH_MAX];
        // Open the file with appropriate permissions
        int fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP);
        
        if (format == 's') {
                // Copy the string data to the buffer and add a newline character
                strcpy(buff, (char*)data);
                strcat(buff, "\n");
        } else { 
                // For integer data, declare some necessary variables
                int num = *((int*)data);
                char string[PATH_MAX];
                int count = strlen(string)-1;
                char* ptr = buff;
                // Convert the integer to a string and add it to the buffer
                if (num < 0) {
                        // Handle negative integers
                        num = -num;
                        string[count] = '\n';
                        count--;
                        integer_to_string(num, string, &count);
                        string[count] = '-';
                } else if (num > 0) {
                        // Handle positive integers
                        string[count] = '\n';
                        count--;
                        integer_to_string(num, string, &count);
                        count++;
                } else {
                        // Handle the case where the integer is 0
                        string[count] = '\n';
                        count--;
                        string[count] = '0';
                }
                // Copy the integer string to the buffer
                strcpy(ptr, string+count);
        }
        // If no file is provided, output to stdout
        if (strlen(filename) == 0) {
                if ( write(1, buff, strlen(buff)) != strlen(buff)) {
                        errno = EIO;
                        return -1;
                }
        } else {
                // Otherwise, write to the specified file
                if ( write(fd, buff, strlen(buff)) != strlen(buff)) {
                        errno = EIO;
                        return -1;
                }
        }
        return 0;
}

int fscanfx(char* filename, char format, void* dst) {
        int openedFd = -1;
        struct stat stats;
        char path[PATH_MAX];
        realpath(filename, path);
        char originalPath[PATH_MAX];
        realpath(".", originalPath);
        
        if (stat(path, &stats) != 0) {
                errno = ENOENT;
                return -1;
        }
        ino_t fileInode = stats.st_ino;
        DIR *d;
        struct dirent *dir;
        
        d = opendir("/proc/self/fd/");
        chdir("/proc/self/fd/");
        if (d == NULL) {
                errno = EIO;
                return -1;
        }
        while ((dir = readdir(d)) != NULL) {
                if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0 || strcmp(dir->d_name, "0") == 0 || strcmp(dir->d_name, "1") == 0 || strcmp(dir->d_name, "2") == 0) {
                        continue;
                } 
                struct stat stats2;
                char path2[PATH_MAX];
                realpath(dir->d_name,path2);
                stat(path2, &stats2);
                ino_t fdInode = stats2.st_ino;
                if (fdInode == fileInode) {
                        openedFd = atoi(dir->d_name);
                        break;
                }
        }
        closedir(d);
        chdir(originalPath);
        if (openedFd == -1) {
                openedFd = open(filename, O_RDONLY);
                if (openedFd == -1) {
                        return -1;
                }
        }
        char* buff = NULL;
        int size = 128;
        char buff2;
        int count = 0;
        buff = (char*)malloc(size);
        while(1) {
                int rd = read(openedFd, &buff2, 1);
                if (rd == 0) {
                        free(buff);
                        return 1;
                }
                if (count == size - 1) { 
                        size += 128;
                        buff = (char*)realloc(buff, size);
                } 
                if (buff2 == '\n') {
                        buff[count] = '\0';
                        break;
                } else {
                        buff[count] = buff2;
                        count++;
                }
        }
        if (format != 's') {
                errno = EIO;
                free(buff);
                return -1;
        } else {
                memset(dst, 0, strlen((char*)dst));
                memcpy(dst, buff, strlen(buff));
                free(buff);
        }
        return 0;
}





int clean() {
        int fd;
        struct dirent *dir;
        char fd_path[PATH_MAX];
        DIR *d = opendir("/proc/self/fd/");
        if (d == NULL) {
                errno = EIO;
                return -1;
        }
        
        while ((dir = readdir(d)) != NULL) {
                if (dir->d_type == DT_LNK) {
                        //memset(fd_path, 0, PATH_MAX);
                        //strcpy(fd_path, "/proc/self/fd/");
                        //strcat(fd_path, dir->d_name);
                        fd = atoi(dir->d_name);
                        if (fd > 2) {
                                close(fd);
                        }
                }
        }
        
        closedir(d);
        return 0;
}