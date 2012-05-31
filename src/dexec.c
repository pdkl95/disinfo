#include <common.h>

char *progname;

void usage(void)
{
    fprintf(stderr,
            "usage: %s <msg> <command> [<args_for_command> ...]\n",
            progname);
}

int main(int argc, char *argv[])
{
#ifdef HAVE_LIBGEN_H
    /* XPG version */
# ifdef HAVE_STRDUPA
    char *progpath = strdupa(argv[0]);
# else
    char *progpath = strdup(argv[0]);
# endif
    progname = basename(progpath);
#else
    /* GNU version */
    progname = argv[0];
    progname = basename(argv[0]);
#endif

    if (argc < 2) {
        usage();
        exit(EXIT_FAILURE);
    }


}
