#ifndef INDENT_H
#define INDENT_H

#include "common.h"

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "isdir.h"
#include "full-write.h"
#include "read-file.h"
#include "xvasprintf.h"

#define INDENT_MAX 40

extern int istate_depth;
extern char *istate_depth_string;

void indent_common_options(int *argc, char **argv[]);
int dindent(void);
int doutdent(void);


#endif /*INDENT_H*/
