// client.cpp
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <limits>

int main() {
    const char* socket_path = "/tmp/mysocket";

    int sock_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    std::cout <<" Server_fd: " <<sock_fd << "\n";
    if (sock_fd == -1) {
        perror("socket");
        return 1;
    }

    sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path) - 1);

    if (connect(sock_fd, (sockaddr*)&addr, sizeof(addr)) == -1) {
        perror("connect");
        return 1;
    }

    std::cout << "[Client] Connected to server.\n";

    char buffer[256];
    while (true) {
        std::cout << "Enter message: ";
        std::cin.getline(buffer, sizeof(buffer));

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "[Warning] Message too long. Truncated!\n";
        }

        write(sock_fd, buffer, strlen(buffer) + 1); // gửi cả '\0'
    }

    close(sock_fd);
    return 0;
}
