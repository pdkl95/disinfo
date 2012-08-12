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

char *err;
char *srcprog;

int   errnum;
char *errmsg;

#define ERR_UNKNOWN -1

int parse_err_name(char *str)
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
        err = ARGV_SHIFT;
    } else {
        die_usage("Missing: <errno>");
    }

    if (argc > 0) {
        srcprog = ARGV_SHIFT;
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
            if (argc) {
                derror("%s: %s - %s", srcprog, errmsg, argv2str(argc, argv));
            } else {
                derror("%s: %s", srcprog, errmsg);
            }
        } else {
            derror("%s", errmsg);
        }
    } else {
        errmsg = "success";
        if (srcprog) {
            if (argc) {
                dinfo("%s: %s - %s", srcprog, errmsg, argv2str(argc, argv));
            } else {
                dinfo("%s: %s", srcprog, errmsg);
            }
        } else {
            dinfo("%s", errmsg);
        }
    }

    // force all out-of-range codes to a generic code
    if (errnum > 127) {
        return EXIT_FAILURE;
    } else {
        return errnum;
    }
}
