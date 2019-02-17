#ifndef MGMEMORY_H
#define MGMEMORY_H

#include "mgtypes.h"

void* MgMemory_allocate(UInt32 size);
void* MgMemory_resize(void* data, UInt32 size);
void MgMemory_free(void* data);

#endif
