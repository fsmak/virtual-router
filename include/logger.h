#ifndef __LOGGER__
#define __LOGGER__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>

#include "utils.h"

#define LOG_TO_SCREEN(format, info_args...)     \
    do {                                        \
        log_to_screen( format, ##info_args );   \
    } while(0)

static inline int
log_to_screen(char *info_args, ...)
{
    char *loginfo = NULL; 
    va_list ap;
    va_start(ap, info_args); 
    int size = vsnprintf(loginfo, size, info_args, ap);
    va_end(ap);

    size++; // for `\n`
    SAVE_ALLOC(loginfo, size, char);
    va_start(ap, info_args);
    size=vsnprintf(loginfo, size, info_args, ap);
    va_end(ap);
    loginfo[size]='\n'; // next-line

    fprintf(stdout, "%s", loginfo);
    return 0;
}

#endif