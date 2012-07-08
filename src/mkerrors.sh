#!/bin/bash

OUT="error_code_macros.h"
HDR_LIST="\
/usr/include/asm-generic/errno-base.h \
/usr/include/asm-generic/errno.h"


HDR_RE="#define[[:space:]]+E[[:upper:][:digit:]]+[[:space:]]+[[:digit:]]+"

rm -f $OUT

errno_defines() {
    #echo grep -E --no-messages --no-filename --only-matching "${HDR_RE}" ${HEADERS} 1>&2
    grep -E --no-messages --no-filename --only-matching "${HDR_RE}" ${HDR_LIST}
}

errno_list() {
    errno_defines | cut -c 9- | sed -re 's/[[:space:]]+/ /g'
}

convert_to_macros() {
    sed -re 's/E([^[:space:]]+)[[:space:]][[:digit:]]+/E(\1);/'
}

errno_macros() {
    errno_list | convert_to_macros
}

errno_macros > $OUT
