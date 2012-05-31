#include <common.h>

char *progname;
char *message;

void usage(void)
{
    fprintf(stderr,
            "usage: %s <message> <fail_message> <command> [<param> [...]]\n",
            progname);
}

int main(int argc, char *argv[])
{
    progname = base_name(*argv); argv++;

    if (argc < 4) {
        usage();
        exit(EXIT_FAILURE);
    }

    char *message = *argv; argv++;
    char *failmsg = *argv; argv++;
    if (strlen(failmsg) < 1) {
        failmsg = message;
    }

    ebegin("%s", message);

    char *prog = *argv;
    int retval = execute(prog, prog, argv,
                         false, /*ignore_sigpipe*/
                         false, /*null_stdin*/
                         false, /*null_stdout*/
                         false, /*null_stderr*/
                         true,  /*slave_process*/
                         false, /*exit_on_error*/
                         NULL); /*termsigp*/

    eend(retval, "%s", failmsg);
    return retval;
}
