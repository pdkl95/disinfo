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

char *local_usage = "<ERRNO> [<calling_program_name>]";




#define ERR_UNKNOWN -1

int
parse_err_name(char *str)
{

#define REPL(A,B) do {                          \
        if (!strcmp("E" #A, str) ||             \
            !strcmp(#A, str)) {                 \
            str = #B;                           \
        }                                       \
    } while(0)

    REPL(DEADLOCK,   EDEADLK);
    REPL(WOULDBLOCK, EAGAIN);

#define E(name) do {               \
        if (!strcmp("E" #name, str) ||          \
            !strcmp(#name, str)) {              \
            return E##name;                     \
        }                                       \
    } while(0)


#include "error_code_macros.h"

#undef REPL
#undef E

    return ERR_UNKNOWN;
}

bool
is_int(char *s)
{
    for (; *s; s++) {
        if (!isdigit(*s)) {
            return false;
        }
    }
    return true;
}

int
derrmsg_print(int (*func)(char *, ...), char *errstr,
              char *program_name, char *extra_message)
{
    if (program_name) {
        if (extra_message) {
            func("%s: %s - %s", program_name, errstr, extra_message);
        } else {
            func("%s: %s", program_name, errstr);
        }
    } else {
        func("%s", errstr);
    }
}

int
derrmsg(int errnum, char *program_name, char *extra_message)
{
    if (errnum) {
        if (ERR_UNKNOWN == errnum) {
            derrmsg_print(derror, "unknown error",
                          program_name, extra_message);
        } else {
            derrmsg_print(derror, strerror(errnum),
                          program_name, extra_message);
        }
    } else {
        derrmsg_print(dinfo, "success",
                      program_name, extra_message);
    }

    if (errnum > 127) {
        return EXIT_FAILURE;
    } else {
        return errnum;
    }
}

int
main(int argc, char *argv[])
{
    char *err;
    int   errnum;
    char *srcprog;
    char *extra = NULL;

    common_options(&argc, &argv);

    if (argc > 0) {
        err = ARGV_SHIFT;
    } else {
        die_usage("Missing: <errno>");
    }

    srcprog =  (argc > 0) ? ARGV_SHIFT           : NULL;
    errnum  = is_int(err) ? atoi(err)            : parse_err_name(err);
    extra   =        argc ? argv2str(argc, argv) : NULL;

    return derrmsg(errnum, srcprog, extra);
}
