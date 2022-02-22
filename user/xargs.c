#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    if(argc < 2) {
        fprintf(2, "usages: xargs conmmand\n");
        exit(1);
    }
    char buf[1024];
    char *argvs[MAXARG + 1];
    int n, args = 0;
    for(int i = 1; i < argc; i++) {
        argvs[args++] = argv[i];
    }
    // int len = 0;
    int m = 0;
    char tmp[1024];
    char *p = tmp;
    while((n = read(0, buf, sizeof(buf))) > 0) {
        for(int i = 0; i < n; i++) {
            if(buf[i] == '\n') {
                tmp[m++] = '\0';
                // printf("%s\n", p);
                argvs[args++] = p;
                p = tmp;
                m = 0;
                args = argc - 1;
                if(fork() == 0) {
                    exec(argv[1], argvs);
                }
                wait(0);
                break ;
            } else if(buf[i] == ' ') {
                tmp[m++] = '\0';
                argvs[args++] = p;
                p = tmp + m;
            } else {
                tmp[m++] = buf[i];
            }
        }
    }
    exit(0);
}