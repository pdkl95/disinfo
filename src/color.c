#include "common.h"


/*char *c_nc    = "\e[0m";
char *c_info  = "\e[1;32m";
char *c_warn  = "\e[1;33m";
char *c_error = "\e[1;31m";*/

void dmarker_info(FILE *stream, bool pad)
{
    if (pad) {
        fputs(DMARK_INFO_PAD, stream);
    } else {
        fputs(DMARK_INFO, stream);
    }
}

void dmarker_warn(FILE *stream, bool pad)
{
    if (pad) {
        fputs(DMARK_WARN_PAD, stream);
    } else {
        fputs(DMARK_WARN, stream);
    }
}

void dmarker_error(FILE *stream, bool pad)
{
    if (pad) {
        fputs(DMARK_ERROR_PAD, stream);
    } else {
        fputs(DMARK_ERROR, stream);
    }
}

/****************************/

int s_dinfo(FILE *stream, char *fmt, ...)
{
    int result;
    va_list args;
    va_start(args, fmt);
    dmarker_info(stream, true);
    result = vfprintf(stream, fmt, args);
    fputs("\n",stream);
    va_end(args);
    return result;
}


int s_dwarn(FILE *stream, char *fmt, ...)
{
    int result;
    va_list args;
    va_start(args, fmt);
    dmarker_warn(stream, true);
    result = vfprintf(stream, fmt, args);
    fputs("\n",stream);
    va_end(args);
    return result;
}

int s_derror(FILE *stream, char *fmt, ...)
{
    int result;
    va_list args;
    va_start(args, fmt);
    dmarker_error(stream, true);
    result = vfprintf(stream, fmt, args);
    fputs("\n",stream);
    va_end(args);
    return result;
}


/*****************************/

int dinfo(char *fmt, ...)
{
    int result;
    va_list args;
    va_start(args, fmt);
    dmarker_info(STREAM_INFO, true);
    result = vfprintf(STREAM_INFO, fmt, args);
    fputs("\n",STREAM_INFO);
    va_end(args);
    return result;
}


int dwarn(char *fmt, ...)
{
    int result;
    va_list args;
    va_start(args, fmt);
    dmarker_warn(STREAM_WARN, true);
    result = vfprintf(STREAM_WARN, fmt, args);
    fputs("\n",STREAM_WARN);
    va_end(args);
    return result;
}

int derror(char *fmt, ...)
{
    int result;
    va_list args;
    va_start(args, fmt);
    dmarker_error(STREAM_ERROR, true);
    result = vfprintf(STREAM_ERROR, fmt, args);
    fputs("\n",STREAM_ERROR);
    va_end(args);
    return result;
}
