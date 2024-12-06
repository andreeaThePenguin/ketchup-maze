#include <Uefi.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseLib.h>
#ifndef _SIZE_T
typedef UINTN size_t;
#define _SIZE_T
#endif

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"

static void * memcpy ( void * dest, const void * source, size_t count)
{
    return CopyMem(dest,source,(UINTN)(count));
}

#pragma GCC diagnostic pop
