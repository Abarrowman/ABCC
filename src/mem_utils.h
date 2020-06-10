#ifndef ABCC_MEM_UTILS
#define ABCC_MEM_UTILS

#include <stdio.h>
#include <stdlib.h>

inline void* xmalloc(size_t size) {
  void* m = malloc(size);
  if (m == NULL) {
    fprintf(stderr, "[%s:%d] Failed to malloc %zu bytes.", __FILE__, __LINE__, size);
    exit(1);
  }
  return m;
}

#endif
