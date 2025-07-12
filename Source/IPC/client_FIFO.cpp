#include <iostream>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char* fifo_path = "/tmp/myfifo";

    // Mở FIFO để đọc
    int fd = open(fifo_path, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    char buffer[256];

    while (true) {
        ssize_t n = read(fd, buffer, sizeof(buffer));
        if (n > 0) {
            std::cout << "Received: " << buffer << std::endl;
        }
    }

    close(fd);
    return 0;
}
