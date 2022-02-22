#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    int sleepTime = atoi(argv[1]);
    sleep(sleepTime);
    exit(0);
}