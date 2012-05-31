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
