//
// Created by Simon Gong on 2026-02-27.
//
#include <sys/types.h>
#include <errno.h>

extern char _end;
static char *heap_end;

caddr_t _sbrk(int incr) {
    if (heap_end == NULL) {
        heap_end = &_end;
    }

    char *prev_heap_end = heap_end;
    heap_end += incr;
    return (caddr_t)prev_heap_end;
}