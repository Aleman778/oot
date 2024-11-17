#include "stdio.h"
#include "windows.h"


void
__puts(const char* fmt) {
    printf(fmt);
}

void
__assert(const char* assertion, const char* file, int line) {
    printf("%s:%d assert failed: %s\n", file, line, assertion);
    fflush(stdout);
    fflush(stderr);
    
    *(int *)0 = 0; // crash on purpose
}
