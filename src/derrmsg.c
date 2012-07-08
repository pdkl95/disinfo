/************************************************************************
 * This file is part of edisinfo                                        *
 *                                                                      *
 * Copyright 2012 Brent Sanders                                         *
 *                                                                      *
 * edisinfo is free software: you can redistribute it and/or modify     *
 * it under the terms of the GNU General Public License as published by *
 * the Free Software Foundation, either version 3 of the License, or    *
 * (at your option) any later version.                                  *
 *                                                                      *
 * edisinfo is distributed in the hope that it will be useful,          *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
 * GNU General Public License for more details.                         *
 *                                                                      *
 * You should have received a copy of the GNU General Public License    *
 * along with edisinfo.  If not, see <http://www.gnu.org/licenses/>.    *
 ************************************************************************/

#include "common.h"

char *progname;


char *err;
char *srcprog;

int   errnum;
char *errmsg;

#define ERR_UNKNOWN -1

#define E(name) if (!strcmp("E" #name, str)) { return E##name; }

int parse_err_name(char *str)
{
    E(PERM);
    E(NOENT);
    E(SRCH);
    E(IO);
    E(NXIO);
    E(2BIG);

    return ERR_UNKNOWN;
}

BOOL is_int(char *s) {
    for (; *s; s++) {
        if (!is_digit(*s)) {
            return 0;
        }
    }
    return 1;
}

void usage(void)
{
    fprintf(stderr,
            "usage: %s <ERRNO> [<calling_program_name>]\n",
            progname);
}

int main(int argc, char *argv[])
{
    progname = *argv;

    if (argc > 0) {
        err = argv[1];
        argc--;
        argv++;
    } else {
        usage();
        exit(EXIT_FAILURE);
    }

    if (argc > 0) {
        srcprog = argv[1];
        argc--;
        argv++;
    } else {
        srcprog = NULL;
    }

    if (is_int(err)) {
        errnum = atoi(err);
    } else {
        errnum = parse_err_name(err);
    }

    if (ERR_UNKNOWN == errnum) {
        errmsg = "unknown error";
    } else {
        errmsg = strerror(errnum);
    }

    if (srcprog) {
        eerror("%s: %s", srcprog, errmsg);
    } else {
        eerror("%s", errmsg);
    }

    // force all out-of-range codes to a generic code
    if (errnum > 127) {
        return EXIT_FAILURE;
    } else {
        return errnum;
    }
}
