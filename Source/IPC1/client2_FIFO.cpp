#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <limits>

int main() {
    const char* fifo_path = "/tmp/myfifo";

    // Mở FIFO để ghi
    int fd = open(fifo_path, O_WRONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    char buffer[256];

    while (true) {
        std::cout << "Enter message: ";
        std::cin.getline(buffer, sizeof(buffer));

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "[Warning] Message too long. Truncated!\n";
        }

        write(fd, buffer, strlen(buffer) + 1); // gửi cả '\0'
    }

    close(fd);
    return 0;
}
