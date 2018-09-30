#ifndef MGMEMORY_H
#define MGMEMORY_H

#include "mgtypes.h"

void* mgMemory_allocate(Int32 size);
void* mgMemory_resize(void* data, Int32 size);
void mgMemory_free(void* data);

#endif