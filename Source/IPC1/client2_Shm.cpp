// reader.cpp
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <unistd.h>
#include <iostream>

struct SharedData {
    sem_t sem_can_write;
    sem_t sem_can_read;
    char buffer[256];
};

int main() {
    const char* shm_name = "/my_shm";
    int fd = shm_open(shm_name, O_RDWR, 0666);
    SharedData* data = (SharedData*)mmap(nullptr, sizeof(SharedData),
                        PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    while (true) {
        sem_wait(&data->sem_can_read); // Chờ có dữ liệu

        std::cout << "[Reader] Read: " << data->buffer << std::endl;

        sem_post(&data->sem_can_write); // Cho writer ghi tiếp
        sleep(1); // Mô phỏng xử lý
    }

    return 0;
}
