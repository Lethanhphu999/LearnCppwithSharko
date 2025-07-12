#include <iostream>
#include <csignal>
#include <unistd.h>

void handle_signal(int signo) {
    std::cout << "Received signal: " << signo << std::endl;
}

int main() {
    signal(SIGUSR1, handle_signal);
    std::cout << "Receiver PID: " << getpid() << std::endl;

    while (true) {
        pause(); // chờ signal đến
    }

    return 0;
}
