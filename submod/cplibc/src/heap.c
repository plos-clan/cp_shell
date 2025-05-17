#include "string.h"
#include "stdlib.h"
#include "alloc/area.h"
#include "posix.h"

static struct mpool pool;

void *calloc(size_t n, size_t size) {
    if (__builtin_mul_overflow(n, size, &size)) return NULL;
    void *ptr = malloc(size);
    if (ptr == NULL) return NULL;
    memset(ptr, 0, size);
    return ptr;
}

void *malloc(size_t size) {
    void *ptr = mpool_alloc(&pool, size);
    return ptr;
}

void free(void *ptr) {
    mpool_free(&pool, ptr);
}

void *xmalloc(size_t size) {
    void *ptr = malloc(size);
    return ptr;
}

void *realloc(void *ptr, size_t newsize) {
    void *n_ptr = mpool_realloc(&pool, ptr, newsize);
    return n_ptr;
}

void *reallocarray(void *ptr, size_t n, size_t size) {
    return realloc(ptr, n * size);
}

void *aligned_alloc(size_t align, size_t size) {
    void *ptr = mpool_aligned_alloc(&pool, size, align);
    return ptr;
}

size_t malloc_usable_size(void *ptr) {
    size_t size = mpool_msize(&pool, ptr);
    return size;
}

void *memalign(size_t align, size_t size) {
    void *ptr = mpool_aligned_alloc(&pool, size, align);
    return ptr;
}

int posix_memalign(void **memptr, size_t alignment, size_t size) {
    void *ptr = mpool_aligned_alloc(&pool, size, alignment);
    if (ptr == NULL) return 1;
    *memptr = ptr;
    return 0;
}

void *valloc(size_t size) {
    void *ptr = mpool_aligned_alloc(&pool, size, 4096);
    return ptr;
}

void *pvalloc(size_t size) {
    void *ptr = mpool_aligned_alloc(&pool, size, 4096);
    return ptr;
}

void init_heap() {
    uint64_t start_addr = 0x0000100000000000;
    size_t size  = 0x800000;
    mmap((void*)start_addr, size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS,0,0);
    mpool_init(&pool, (void*)start_addr, size);
}
