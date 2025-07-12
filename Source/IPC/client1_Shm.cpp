// writer.cpp
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

struct SharedData {
    sem_t sem_can_write;
    sem_t sem_can_read;
    char buffer[256];
};

int main() {
    const char* shm_name = "/my_shm";
    int fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
    ftruncate(fd, sizeof(SharedData));

    SharedData* data = (SharedData*)mmap(nullptr, sizeof(SharedData),
                        PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    // Init semaphores (chỉ init 1 lần khi tạo)
    sem_init(&data->sem_can_write, 1, 1); // 1: có thể ghi
    sem_init(&data->sem_can_read, 1, 0);  // 0: chưa có gì để đọc

    int counter = 0;
    while (true) {
        sem_wait(&data->sem_can_write); // Chờ tới lượt ghi

        std::cout << "Enter message: " << counter++ << "\n";
std::cin.getline(data->buffer, sizeof(data->buffer));
        std::cout << "[Writer] Wrote: " << data->buffer << std::endl;

        sem_post(&data->sem_can_read); // Cho reader đọc
        sleep(1); // Mô phỏng delay
    }

    return 0;
}
