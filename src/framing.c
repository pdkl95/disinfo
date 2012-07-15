#include "common.h"
#include <sys/ioctl.h>
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

static const char *term = NULL;
static char *termcapbuf = NULL;
static char *term_up = NULL;
static char *term_ch = NULL;
static char *term_cm = NULL;
static char *term_w = NULL;
static char *term_h = NULL;
static char *bp;

bool init_term_features(FILE *stream)
{
    int retval;

    if (!isatty(fileno(stream))) {
        return false;
    }

    if (!term) {
        term = getenv("TERM");
        if (!term) {
            return false;
        }
    }

    retval = tgetent(termcapbuf, term);
    if (retval < 0) {
        fprintf(stream, "could not access the termcap database\n");
        return true;
    }
    if (retval == 0) {
        fprintf(stream, "terminal type '%s' was not found\n", term);
        return true;
    }

    char *bp = termcapbuf;
    if (NULL == (term_up = tgetstr("up", &bp))) {
        return false;
    }
    if (NULL == (term_ch = tgetstr("ch", &bp))) {
        return false;
    }
    if (NULL == (term_cm = tgetstr("cm", &bp))) {
        return false;
    }

    return true;
}

int get_cols(FILE *stream)
{
    struct winsize ws;
	char *env = getenv("COLUMNS");
	char *p;
	int i;

	if (env) {
		i = strtoimax(env, &p, 10);
        if (!*p) {
			return i;
        }
	}

    if (ioctl(fileno(stream), TIOCGWINSZ, &ws) == 0) {
		return ws.ws_col;
    }

    return DEFAULT_TERMINAL_COLUMNS;
}


int rprint_fallback(FILE *stream, char *msg)
{
    return fprintf(stream, " [ %s ]\n", msg);
}

int rprint(FILE *stream, char *msg_color, char *msg)
{

    int cols;
    char *bracket_color = COLOR_BRACKET;

    if (!init_term_features(stream)) {
        return rprint_fallback(stream, msg);
    }

    cols = get_cols(stream);
    cols -= (strlen(msg) + 5);

    if (cols < 0) {
        return rprint_fallback(stream, msg);
    }

    char *term_mv = tgoto(term_ch, 0, cols);
    return fprintf(stream, "%s%s %s[%s %s %s]%s\n", term_up, term_mv,
                   bracket_color, msg_color, msg,
                   bracket_color, COLOR_NC);
}

int dend(int retval, char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    if (retval) {
        dmarker_error(stdout, true);
        warn_vfprintf(stdout, fmt, args);
        fputs("\n", stdout);
    }

    if (retval) {
        rprint(stdout, COLOR_ERROR, "*ERR*");
    } else {
        rprint(stdout, COLOR_INFO, "OK");
    }

    doutdent();

    va_end(args);
    return retval;
}

int
dexec_argv(int argc, char **argv)
{
    int i;
    char * add_indent;

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

    if (asprintf(&add_indent, "%d", get_indent()) < 0) {
        dwarn("disinfo: asprintf error: %s", strerror(errno));
    }
    setenv(ENVNAME_ADD_INDENT, add_indent, 1);

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
