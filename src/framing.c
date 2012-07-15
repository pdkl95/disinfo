#include "common.h"
#include <termcap.h>

int dbegin(char *fmt, ...)
{
    int result;
    va_list args;
    va_start(args, fmt);

    dmarker_info(stdout, true);

    result = vfprintf(stdout, fmt, args);
    fputs(" ...\n",stdout);

    dindent();

    va_end(args);
    return result;
}

void rprint(FILE *stream, char *msg)
{
    char *up = "\033A";


    char *cm = (char *)tgetstr("cm", NULL);

    int cols = 80;
    cols -= strlen(msg) + 5;

    if (cols > 0) {
        fprintf(stream, "%s%s [ %s ]\n",
                "\033A", tgoto(cm,  0, cols), msg);
    } else {
        fprintf(stream, " [ %s ]\n", msg);
    }
}

#define TPUT_RIGHT_ALIGN "tput cuu1 ; tput hpa $(( $(tput cols) - 6 ))"
int dend(int retval, char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    if (retval) {
        dmarker_error(stdout, true);
        warn_vfprintf(stdout, fmt, args);
    }

    system(TPUT_RIGHT_ALIGN);

    if (retval) {
        rprint("[ FAIL!! ]\n",stdout);
    } else {
        ("[ OK ]\n",stdout);
    }

    doutdent();

    va_end(args);
    return retval;
}

int
dexec_argv(int argc, char **argv)
{
    int i;

    char *prog = strip_escape_codes(ARGV_SHIFT);
    char **arglist = malloc(sizeof(char *) * (argc+1));

    /* for (i=0; i<argc; i++) { */
    /*     arglist[i] = strip_escape_codes(argv[i]); */
    /* } */

    arglist[0] = prog;
    i=1;

    while(argc) {
        arglist[i] = ARGV_SHIFT;
        i++;
    }

    return execute(prog, prog, arglist,
                   false, /*ignore_sigpipe*/
                   false, /*null_stdin*/
                   false, /*null_stdout*/
                   false, /*null_stderr*/
                   true,  /*slave_process*/
                   false, /*exit_on_error*/
                   NULL); /*termsigp*/
}

int
dexec(char *message, char *failmsg, int argc, char **argv)
{
    dbegin("%s", message);
    return dend(dexec_argv(argc, argv),
                "%s", failmsg);
}

int
dshowexec(int argc, char **argv)
{
    char *cmdline = argv2str(argc, argv);
    return dexec(cmdline, cmdline, argc, argv);
    //dbegin("%s", cmdline);
    //return dend(dexec(argc, argv), "%s", cmdline);
}
