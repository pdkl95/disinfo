#include "common.h"

int main(int argc, char *argv[])
{
    int retval=0;
    if (argc > 1) {
        retval = atoi(argv[1]);
        argc--;
        argv++;
    }
    eend(retval, "%s",argv2str(argc, argv));
    return EXIT_SUCCESS;
}
