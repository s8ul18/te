#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_KEY 1234     // Unique key
#define SHM_SIZE 1024    // Memory size

int main() {
    
    int shmid;
    char *shmaddr;

    // Create shared memory segment
    shmid = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }

    // Attach shared memory to process
    shmaddr = (char *) shmat(shmid, NULL, 0);
    if (shmaddr == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    printf("Server: Enter a message to write into shared memory:\n");
    fgets(shmaddr, SHM_SIZE, stdin);   // Store message in shared memory

    printf("Server: Message written to shared memory.\n");
    printf("Message is: %s\n", shmaddr);

    // Detach
    shmdt(shmaddr);

    return 0;
}
