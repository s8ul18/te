#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_KEY 1234
#define SHM_SIZE 1024

int main() {
    int shmid;
    char *shmaddr;

    // Access existing shared memory
    shmid = shmget(SHM_KEY, SHM_SIZE, 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }

    // Attach shared memory
    shmaddr = (char *) shmat(shmid, NULL, 0);
    if (shmaddr == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    printf("Client: Reading message from shared memory...\n");
    printf("Message: %s\n", shmaddr);

    // Detach
    shmdt(shmaddr);

    // Delete shared memory permanently
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
