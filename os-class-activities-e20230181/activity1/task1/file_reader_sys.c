/* file_reader_sys.c */
#include <fcntl.h>    // open(), O_RDONLY
#include <unistd.h>   // read(), write(), close()
#include <string.h>   // strlen()

int main() {
    char buffer[256];
    ssize_t bytesRead;

    // 1. Open "output.txt" for reading
    int fd = open("output.txt", O_RDONLY);
    if (fd < 0) {
        const char *err = "Error opening file\n";
        write(2, err, strlen(err));   // fd 2 = stderr
        return 1;
    }

    // 2 + 3. Read a block into buffer, then write exactly that many bytes to the terminal
    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
        write(1, buffer, bytesRead);  // fd 1 = stdout
    }

    // 4. Close the file
    close(fd);
    return 0;
}
