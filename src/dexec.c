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

#include <common.h>

char *local_usage = "<message> <fail_message> <command> [<param> [...]]";

char *message;

int main(int argc, char *argv[])
{
    int i;
    common_options(&argc, &argv);

    if (argc < 4) {
        die_usage("missing requried parameters!");
    }

    argv++;

    char *message = *argv; argv++; argc--;
    char *failmsg = *argv; argv++; argc--;
    if (strlen(failmsg) < 1) {
        failmsg = message;
    }

    dbegin("%s", message);

    argc--;

    char *prog = strip_escape_codes(*argv);
    char **prog_args = malloc(sizeof(char *) * (argc+1));

    for (i=0; i<argc; i++) {
        prog_args[i] = strip_escape_codes(argv[i]);
    }
    prog_args[i] = NULL;

    int retval = execute(prog, prog, prog_args,
                         false, /*ignore_sigpipe*/
                         false, /*null_stdin*/
                         false, /*null_stdout*/
                         false, /*null_stderr*/
                         true,  /*slave_process*/
                         false, /*exit_on_error*/
                         NULL); /*termsigp*/

    dend(retval, "%s", failmsg);
    return retval;
}
