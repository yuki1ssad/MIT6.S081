#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(2, "Missing an argument ...\n");
        exit(1);
    }
    int sleep_time = atoi(argv[1]);

    if (sleep_time <= 0) {
        fprintf(2, "Invalid sleep time ...\n");
        exit(1);
    }
    sleep(sleep_time);
    exit(0);
}

