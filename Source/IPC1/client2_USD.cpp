// server.cpp
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

int main() {
    const char* socket_path = "/tmp/mysocket";
    unlink(socket_path); // Xóa nếu socket cũ còn

    int server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    std::cout <<" Server_fd: " <<server_fd << "\n";
    if (server_fd == -1) {
        perror("socket");
        return 1;
    }

    sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path) - 1);

    if (bind(server_fd, (sockaddr*)&addr, sizeof(addr)) == -1) {
        perror("bind");
        return 1;
    }

    listen(server_fd, 5);
    std::cout << "[Server] Waiting for connection...\n";

    int client_fd = accept(server_fd, nullptr, nullptr);
    if (client_fd == -1) {
        perror("accept");
        return 1;
    }

    std::cout << "[Server] Client connected.\n";

    char buffer[256];
    while (true) {
        ssize_t n = read(client_fd, buffer, sizeof(buffer));
        if (n > 0) {
            std::cout << "[Server] Received: " << buffer << std::endl;
        } else if (n == 0) {
            std::cout << "[Server] Client disconnected.\n";
            break;
        } else {
            perror("read");
            break;
        }
    }

    close(client_fd);
    close(server_fd);
    unlink(socket_path);
    return 0;
}
