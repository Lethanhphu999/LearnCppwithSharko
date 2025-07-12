#include <iostream>
#include <unistd.h>
#include <csignal>

int main() {
    pid_t target_pid;
    std::cout << "Enter receiver PID: ";
    std::cin >> target_pid;

    while (true) {
        std::cout << "Send SIGUSR1 to " << target_pid << std::endl;
        kill(target_pid, SIGUSR1);
        sleep(1);
    }

    return 0;
}
