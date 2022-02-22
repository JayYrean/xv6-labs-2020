#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void prime(int p) {
    int base;
    if(read(p, &base, sizeof(base)) == 0) {
        fprintf(2, "Usage: prime error\n");
        exit(1);
    }
    printf("prime %d\n", base);
    int mp[2];
    int num = base;
    pipe(mp);
    while(read(p, &num, sizeof(num))) {
        if(num % base) {
            write(mp[1], &num, sizeof(num));
        }
    }
    close(mp[1]);
    if(num != base && fork() == 0) {
        prime(mp[0]);
    } else {
        wait(0);
    }
    close(mp[0]);
    exit(0);
}

int main(int argc, char *argv[]) {
    int p[2];
    int base = 2;
    pipe(p);
    for(int i = base; i <= 35; i++) {
        if(i != base && i % base == 0) continue ;
        write(p[1], &i, sizeof(i));
    }
    close(p[1]);
    prime(p[0]);
    close(p[0]);
    exit(0);
}