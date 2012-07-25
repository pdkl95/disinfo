#ifndef FRAMING_H
#define FRAMING_H

#define DEFAULT_TERMINAL_COLUMNS 80

int dbegin(char *fmt, ...);
int dend(int retval, char *fmt, ...);
int dexec_argv(int argc, char **argv);
int dexec(char *success, char *failure, int argc, char **argv);
int dshowexec(int argc, char **argv);
int dshowonerror(int argc, char **argv);

#endif /*FRAMING_H*/
