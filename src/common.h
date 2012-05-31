#ifndef COMMON_H
#define COMMON_H

#include "config.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <einfo.h>

#include "dirname.h"

#if __STDC__
# define VOID void
#else
# define VOID char
#endif

char * argv2str(int argc, char *argv[]);


#endif /*COMMON_H*/
