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

char *local_usage = "<ERRNO> [<calling_program_name>]";

char *err;
char *srcprog;

int   errnum;
char *errmsg;

#define ERR_UNKNOWN -1



int parse_err_name(char *str)
{
#define E(name) if (!strcmp("E" #name, str)) { return E##name; }
#define REPL(A,B) if (!strcmp(#A, str)) { str = #B; }

    REPL(EDEADLOCK,   EDEADLK);
    REPL(EWOULDBLOCK, EAGAIN);

#include "error_code_macros.h"

#undef REPL
#undef E

    return ERR_UNKNOWN;
}

bool is_int(char *s)
{
    for (; *s; s++) {
        if (!isdigit(*s)) {
            return false;
        }
    }
    return true;
}

int main(int argc, char *argv[])
{
    common_options(&argc, &argv);

    if (argc > 0) {
        err = argv[1];
        argc--;
        argv++;
    } else {
        die_usage("Missing: <errno>");
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


    if (errnum) {
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
    } else {
        errmsg = "success";
        if (srcprog) {
            einfo("%s: %s", srcprog, errmsg);
        } else {
            einfo("%s", errmsg);
        }
    }

    // force all out-of-range codes to a generic code
    if (errnum > 127) {
        return EXIT_FAILURE;
    } else {
        return errnum;
    }
}
