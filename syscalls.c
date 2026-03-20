#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdint.h>

extern char _end;        // linker symbol (start of heap)
extern char _estack;     // top of RAM (from linker)

static char *heap_end = 0;

caddr_t _sbrk(int incr)
{
    if (heap_end == 0)
    {
        heap_end = &_end;
    }

    char *prev_heap_end = heap_end;

    // Prevent heap growing into stack
    if (heap_end + incr > &_estack)
    {
        errno = ENOMEM;
        return (caddr_t)-1;
    }

    heap_end += incr;
    return (caddr_t)prev_heap_end;
}

/* Minimal stubs required by newlib */

int _write(int file, char *ptr, int len)
{
    // Optional: send to UART here
    // sys_usart3_send((uint8_t*)ptr, len);
    return len;
}

int _close(int file) { return -1; }

int _fstat(int file, struct stat *st)
{
    st->st_mode = S_IFCHR;
    return 0;
}

int _isatty(int file) { return 1; }

int _lseek(int file, int ptr, int dir) { return 0; }

int _read(int file, char *ptr, int len) { return 0; }

int _getpid(void) { return 1; }

int _kill(int pid, int sig)
{
    errno = EINVAL;
    return -1;
}

void _exit(int status) { while (1) {} }