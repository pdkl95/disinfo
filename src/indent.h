#ifndef INDENT_H
#define INDENT_H

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "xvasprintf.h"

#define ISTATE_DEPTH_DIGITS 2
#define ISTATE_BUFLEN (1+ISTATE_DEPTH_DIGITS)

extern int istate_depth;
extern char istate_depth_string[];

int get_current_indent(void);
int dindent(void);
int doutdent(void);


#endif /*INDENT_H*/
