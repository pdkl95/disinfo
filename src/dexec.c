#include <common.h>

char *progname;
char *message;

void usage(void)
{
    fprintf(stderr,
            "usage: %s <msg> <command> [<args_for_command> ...]\n",
            progname);
}

int main(int argc, char *argv[])
{
    int retval;

    progname = base_name(argv[0]);

    if (argc < 2) {
        usage();
        exit(EXIT_FAILURE);
    }

    message = argv[1];
    ebegin("%s", message);


    eend(retval, "%s", message);
    return retval;
}
