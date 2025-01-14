// -- system includes
#include <stdlib.h>
#include <string.h>

// -- libs includes
#include "core/cmemory.h"

// -- include the guts of the memory allocator
//#include "core/dlmalloc.c"

// ================================================================================================
// Make a new allocation of the give size
// ================================================================================================
vpointer CMemory::Alloc(nuint size) {
    return malloc(size);
}

// ================================================================================================
// Adjust the given allocation (or make a new one if NULL is passed in) to be the new size
// ================================================================================================
vpointer CMemory::ReAlloc(vpointer mem, nuint size) {
    return realloc(mem, size);
}

// ================================================================================================
// Allocate memory and clear it with all zeros
// ================================================================================================
vpointer CMemory::CAlloc(nuint size) {
    return calloc(size, 1);
}

// ================================================================================================
// Free the given memory
// ================================================================================================
void CMemory::Free(vpointer mem) {
    free(mem);
}

// ================================================================================================
// Move memory from one place to another
// ================================================================================================
void CMemory::Move(vpointer to, vpointer from, nuint size) {
    memmove(to, from, size);
}

