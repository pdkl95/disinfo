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
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <einfo.h>

#include "dirname.h"
#include "execute.h"
#include "xalloc.h"

#include "color.h"

#define USAGE_STANDARD_MESSAGE "<your message> [<more mesage> [...]]"
extern char *progname;
extern char *local_usage;


void show_Version(FILE *stream);
void common_options(int *argc, char **argv[]);
void die_usage(char *msg);
void die(char *msg);

char * argv2str(int argc, char *argv[]);
char * strip_escape_codes(char *input_string);

int dbegin(char *fmt, ...);
int dend(int retval, char *fmt, ...);

int dindent(void);
int doutdent(void);

#endif /*COMMON_H*/
