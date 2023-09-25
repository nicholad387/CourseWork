//Nicholas mohamed
//i pledge my honor that i have abided by the stevens honor pledge

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <limits.h>
#include <errno.h>

#define PERMISSION_LENGTH 9

void print_error_message(char* pstring) {
    fprintf(stderr, "Error: Permissions string '%s' is invalid.\n", pstring);
    exit(EXIT_FAILURE);
}

int check_permission(const char *perm_string) {
    // Check that the permission string is the correct length
    if (strlen(perm_string) != PERMISSION_LENGTH) {
        return 0;
    }
    
    // Check that each character is a valid permission
    for (int i = 0; i < PERMISSION_LENGTH; i++) {
        char c = perm_string[i];
        if (i % 3 == 0 && c != 'r' && c != '-') {
            return 0;
        } else if (i % 3 == 1 && c != 'w' && c != '-') {
            return 0;
        } else if (i % 3 == 2 && c != 'x' && c != '-') {
            return 0;
        }
    }
    
    return 1;
}

void search_dir(char* path, int permission) {
    DIR* dir;
    struct dirent* entry;
    struct stat sb;
    char fullpath[PATH_MAX];

    if ((dir = opendir(path)) == NULL) {
        fprintf(stderr, "Error: cannot open directory '%s'\n", path);
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);
        if (stat(fullpath, &sb) == -1) {
            fprintf(stderr, "Error: cannot get file status '%s'\n", fullpath);
            continue;
        }
        if ((sb.st_mode & PERMISSION_LENGTH) == permission) {
            printf("%s\n", fullpath);
        }
        if (entry->d_type == DT_DIR) {
            search_dir(fullpath, permission);
        }
    }
    
    closedir(dir);

}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <path> <permission>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *perm_string = argv[2];
    
    // Check that the permission string is valid
    if (!check_permission(perm_string)) {
        fprintf(stderr, "Error: Permissions string '%s' is invalid.\n", perm_string);
        exit(EXIT_FAILURE);
        
    }
    
    int permission = strtol(argv[2], NULL, 8);
    int perms[] = {S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH};
    
    char *perm_str = argv[2];
    int permissions = 0;
    for (int i = 0; i < 9; i++) {
        permissions <<= 1;
        if (perm_str[i] != '-')
            permissions |= 1;
    }

    // Search the directory for files with the given permission
    search_dir(argv[1], permissions);
    
    return EXIT_SUCCESS;
}
//all error checking works
