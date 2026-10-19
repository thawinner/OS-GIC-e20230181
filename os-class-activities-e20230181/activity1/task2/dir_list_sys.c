/* dir_list_sys.c */
#include <fcntl.h>
#include <unistd.h>     // write()
#include <dirent.h>     // opendir(), readdir(), closedir()
#include <sys/stat.h>   // stat()
#include <string.h>     // strlen()
#include <stdio.h>      // only for snprintf (and perror)

int main() {
    char buffer[512];

    // 1. Open current directory
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("Error opening directory");
        return 1;
    }

    struct dirent *entry;
    struct stat fileStat;

    // 2. Print the two header lines using write()
    snprintf(buffer, sizeof(buffer), "%-30s %10s\n", "Filename", "Size (bytes)");
    write(1, buffer, strlen(buffer));

    snprintf(buffer, sizeof(buffer), "%-30s %10s\n", "------------------------------", "----------");
    write(1, buffer, strlen(buffer));

    // 3. Loop through all entries
    while ((entry = readdir(dir)) != NULL) {
        // 4. Get file info (size) with stat()
        if (stat(entry->d_name, &fileStat) == 0) {
            // 5. Format name + size into buffer, then write it to fd 1
            snprintf(buffer, sizeof(buffer), "%-30s %10ld\n", entry->d_name, fileStat.st_size);
            write(1, buffer, strlen(buffer));
        }
    }

    // 6. Close directory
    closedir(dir);
    return 0;
}
