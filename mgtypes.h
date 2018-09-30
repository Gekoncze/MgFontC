#ifndef MGTYPES_H
#define MGTYPES_H

#include <stdint.h>

typedef int8_t Int8;
typedef int16_t Int16;
typedef int32_t Int32;
typedef int64_t Int64;

typedef uint8_t UInt8;
typedef uint16_t UInt16;
typedef uint32_t UInt32;
typedef uint64_t UInt64;

typedef float Float32;
typedef double Float64;

#ifndef NULL
#define NULL ((void *)0)
#endif

typedef Int32 MgError;

Int32 mgTypes_UInt32_to_Int32(UInt32 value);

#endif