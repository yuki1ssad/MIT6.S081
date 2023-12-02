#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"

#define  MSGSIZE 32

int
main(int argc, char *argv[])
{
    sleep(10);
    /*
       sleep(10); 的原因：
       如果不sleep的话，在执行 sh < xargstest.sh 时，看不到 3 个 hello，
       应该是因为 find 执行的太慢了
    */
    char buf[MSGSIZE];
    read(0, buf, MSGSIZE); // 0 表示标准化输入文件描述符
    // printf("buf: %s\n", buf);
    
    char *xargv[MAXARG];
    int xargc = 0;
    for (int i = 1; i < argc; i++) {
        xargv[xargc] = argv[i];
        // printf("xargv[%d]: %s\n", xargc, xargv[xargc]);
        xargc++;
    }
    char *p = buf;
    // printf("p: %s\n", p);
    for (int i = 0; i < MSGSIZE; i++) {
        if (buf[i] == '\n') {
            // printf("i = %d\n", i);
            int pid = fork();
            if (pid > 0) {
                p = &buf[i + 1];
                wait(0);
            } else {
                buf[i] = 0;
                xargv[xargc] = p;
                xargc++;
                xargv[xargc] = 0;
                xargc++;
                // printf("exec %s\n", xargv[0]);
                exec(xargv[0], xargv);
                exit(0);
            }
        }
    }
    wait(0);
    exit(0);
}