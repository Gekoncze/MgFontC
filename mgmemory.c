#include "mgmemory.h"
#include <stdlib.h>

#define MIN_ALLOCATION 1
#define MAX_ALLOCATION 1000000

void* MgMemory_allocate(UInt32 size)
{
    if(size < MIN_ALLOCATION) size = MIN_ALLOCATION;
    if(size > MAX_ALLOCATION) return NULL;
    return malloc(size);
}

void* MgMemory_resize(void* data, UInt32 size)
{
    if(size < MIN_ALLOCATION) size = MIN_ALLOCATION;
    if(size > MAX_ALLOCATION) return NULL;
    return realloc(data, size);
}

void MgMemory_free(void* data)
{
    free(data);
}
