#include "common.h"

static VOID *
xmalloc(size_t n)
{
    VOID *p;
    p = malloc(n);
    if (p == 0) {
        fprintf(stderr, "dinfo: Memory exhausted");
        exit(EXIT_FAILURE);
    }
    return p;
}

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
