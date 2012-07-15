#ifndef COLOR_H
#define COLOR_H

#define STREAM_INFO  stdout
#define STREAM_WARN  stdout
#define STREAM_ERROR stderr

#define MARKER_INFO  "*"
#define MARKER_WARN  "*"
#define MARKER_ERROR "*"

#define COLOR_NC    "\e[0m"
#define COLOR_INFO  "\e[1;32m"
#define COLOR_WARN  "\e[1;33m"
#define COLOR_ERROR "\e[1;31m"

#define COLOR_BRACKET "\e[1;37m"

#define DMARK_INFO  (COLOR_INFO  MARKER_INFO  COLOR_NC)
#define DMARK_WARN  (COLOR_WARN  MARKER_WARN  COLOR_NC)
#define DMARK_ERROR (COLOR_ERROR MARKER_ERROR COLOR_NC)

#define PAD " "
#define DMARK_INFO_PAD  (PAD COLOR_INFO  MARKER_INFO  COLOR_NC PAD)
#define DMARK_WARN_PAD  (PAD COLOR_WARN  MARKER_WARN  COLOR_NC PAD)
#define DMARK_ERROR_PAD (PAD COLOR_ERROR MARKER_ERROR COLOR_NC PAD)


void dmarker_info(FILE *stream, bool pad);
void dmarker_warn(FILE *stream, bool pad);
void dmarker_error(FILE *stream, bool pad);

int s_dinfo(FILE *stream, char *fmt, ...);
int s_dwarn(FILE *stream, char *fmt, ...);
int s_derror(FILE *stream, char *fmt, ...);

int dinfo(char *fmt, ...);
int dwarn(char *fmt, ...);
int derror(char *fmt, ...);

#endif /*COLOR_H*/
