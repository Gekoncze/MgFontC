#include <limits.h>

#include "mgtypes.h"

Int32 mgTypes_UInt32_to_Int32(UInt32 value)
{
    if(value > INT32_MAX) return INT32_MAX;
    else return (Int32)value;
}