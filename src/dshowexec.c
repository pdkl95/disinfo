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

char *progname;
char *message;

void usage(void)
{
    fprintf(stderr,
            "usage: %s <command> [<param> [...]]\n",
            progname);
}

int main(int argc, char *argv[])
{
    progname = *argv; //base_name(*argv); argv++;

    if (argc < 2) {
        usage();
        exit(EXIT_FAILURE);
    }

    char *cmdline = argv2str(argc, argv);

    argv++;
    char *prog = *argv;
    char **prog_args = argv;

    ebegin("EXEC: %s", cmdline);

    int retval = execute(prog, prog, prog_args,
                         false, /*ignore_sigpipe*/
                         false, /*null_stdin*/
                         false, /*null_stdout*/
                         false, /*null_stderr*/
                         true,  /*slave_process*/
                         false, /*exit_on_error*/
                         NULL); /*termsigp*/

    eend(retval, "FAILED: %s", cmdline);
    return retval;
}
