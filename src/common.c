/************************************************************************
 * This file is part of disinfo                                        *
 *                                                                      *
 * Copyright 2012 Brent Sanders                                         *
 *                                                                      *
 * disinfo is free software: you can redistribute it and/or modify     *
 * it under the terms of the GNU General Public License as published by *
 * the Free Software Foundation, either version 3 of the License, or    *
 * (at your option) any later version.                                  *
 *                                                                      *
 * disinfo is distributed in the hope that it will be useful,          *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
 * GNU General Public License for more details.                         *
 *                                                                      *
 * You should have received a copy of the GNU General Public License    *
 * along with disinfo.  If not, see <http://www.gnu.org/licenses/>.    *
 ************************************************************************/

#include "common.h"

char *progname;

void
show_version(FILE *stream)
{
    fprintf(stream, "%s %s\n", progname, PACKAGE_VERSION);
    fprintf(stream, "%s %s\n", PACKAGE_NAME, PACKAGE_VERSION);
    fprintf(stream, "\nWritten by %s.\n", "Brent Sanders");
    fprintf(stream, "Send bugs to: <%s>\n", PACKAGE_BUGREPORT);
    fprintf(stream, "\nCopyright (C) %s %s\n%s", "2012", "Brent Sanders", "\
This program is free software; you may redistribute it under the terms of\n\
the GNU General Public License.  This program has absolutely no warranty.\n");
}


static void
show_usage(FILE *stream)
{
    fprintf(stream, "usage: %s %s\n", progname, local_usage);
}

void
common_options(int *argc_ptr, char **argv_ptr[])
{
    // local alias for the sake of pointer sanity
    int    argc = *argc_ptr;
    char **argv = *argv_ptr;

    progname = base_name(ARGV_SHIFT);

    if (argc > 1) {
        if (!strcmp(argv[1], "--help")) {
            show_usage(stdout);
            exit(EXIT_SUCCESS);
        } else if (!strcmp(argv[1], "--version")) {
            show_version(stdout);
            exit(EXIT_SUCCESS);
        }
    }

    // undo the local alias so any changes are
    // passed back to the caller
    *argc_ptr = argc;
    *argv_ptr = argv;
}

void
die_usage(char *msg)
{
    show_usage(stderr);
    die(msg);
}

void
die(char *msg)
{
    fprintf(stderr, "%s: ERROR: %s\n", progname, msg);
    exit(EXIT_FAILURE);
}

void
die_errno(char *msg)
{
    fprintf(stderr, "%s: ERROR: %s: %s\n", progname, msg, strerror(errno));
    exit(EXIT_FAILURE);
}

char *
argv2str(int argc, char *argv[])
{
    int len=0;
    int i;
    char *str, *p;

    for(i=0; i<argc; i++) {
        len += 1 + strlen(argv[i]);
    }

    p = str = (char *)xmalloc(1 + len * sizeof(char));

    for(i=0; i<argc; i++) {
        sprintf(p, "%s ", argv[i]);
        p += strlen(p);
    }

    /* change the last (trailing) space into an extra \0 */
    str[len-1] = '\0';

    return str;
}


char *
strip_escape_codes(char *input_string)
{
    char *str = strdup(input_string);
    char *in, *out;
    int c;

    for (out = in = str; *in;  in++, out++) {
        if (*in == '\e' && *(in+1) == '[') {
            c=0;
            do {
                if (*in == '\0') {
                    fprintf(stderr, "error: hit end of string while trying to stirp an escape code!\n");
                    return str;
                }
                if (c > 20) {
                    fprintf(stderr, "error: input has suspiciously long \"\\e[...m\" style escape code! giving up on filtering it!\n");
                    return str;
                } else {
                    c++;
                }
                in++;
            } while (*in != 'm');
            in++;
        }
        *out = *in;
    }
    *out = '\0';
    return str;
}
