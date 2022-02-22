#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    int p[2];
    int flag = 1;
    pipe(p);
    if(fork() == 0) {
        read(p[0], &flag, sizeof(flag));
        printf("%d: received ping\n", getpid());
        write(p[1], &flag, sizeof(flag));
    } else {
        write(p[1], &flag, sizeof(flag));
        wait(0);
        read(p[0], &flag, sizeof(flag));
        printf("%d: received pong\n", getpid());
    }
    exit(0);
}