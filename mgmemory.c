#include "mgmemory.h"
#include <stdlib.h>

#define MIN_ALLOCATION 1
#define MAX_ALLOCATION 1000000

void* mgMemory_allocate(Int32 size)
{
    if(size < MIN_ALLOCATION) size = MIN_ALLOCATION;
    if(size > MAX_ALLOCATION) return NULL;
    return malloc(size);
}

void* mgMemory_resize(void* data, Int32 size)
{
    if(size < MIN_ALLOCATION) size = MIN_ALLOCATION;
    if(size > MAX_ALLOCATION) return NULL;
    return realloc(data, size);
}

void mgMemory_free(void* data)
{
    free(data);
}