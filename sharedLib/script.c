
#include <stdio.h>
#include "script.h"

char script(unsigned row, unsigned column, unsigned level, char* objectIds) {
    printf("%u %u %u\n|", row, column, level);
    for (unsigned i = 0; i < 4; printf("%c, ", objectIds[i++]));
    printf("|\n");
    return PASS;
}
