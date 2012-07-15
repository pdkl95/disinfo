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

#ifndef COMMON_H
#define COMMON_H

#include "config.h"

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "dirname.h"
#include "execute.h"
#include "isdir.h"
#include "full-write.h"
#include "read-file.h"
#include "xalloc.h"
#include "xvasprintf.h"

#define ARGV_SHIFT (argc--, *(argv++))

#ifdef HAVE_VA_ARGS
#  define warn_vfprintf(fmt, ...) do {            \
        if (vfprintf(fmt, __VA_ARGS__) < 0) {     \
            die("failure in vfprintf");           \
        }                                         \
    } while(0)
#else
#  define warn_vfprintf vfpri
#  warn "MISSIN support for __VA_ARGS__"
#  warn "Error checks for some libarary calls are removed!"
#endif


#include "color.h"
#include "indent.h"
#include "framing.h"

#define USAGE_STANDARD_MESSAGE "<your message> [<more mesage> [...]]"
extern char *progname;
extern char *local_usage;

void show_Version(FILE *stream);
void common_options(int *argc, char **argv[]);
void die_usage(char *msg);
void die(char *msg);

char * argv2str(int argc, char *argv[]);
char * strip_escape_codes(char *input_string);

#endif /*COMMON_H*/
