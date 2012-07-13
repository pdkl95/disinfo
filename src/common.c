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

char *
argv2str(int argc, char *argv[])
{
    int len=0;
    int i;
    char *str, *p;

    for(i=1; i<argc; i++) {
        len += 1 + strlen(argv[i]);
    }

    p = str = (char *)xmalloc(1 + len * sizeof(char));

    for(i=1; i<argc; i++) {
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
                    fprintf(stderr, "error: hit end of string while trying to stirp an escape code!");
                    return str;
                }
                if (c > 20) {
                    fprintf(stderr, "error: input has suspiciously long \"\\e[...m\" style escape code! giving up on filtering it!");
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
