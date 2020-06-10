#ifndef ABCC_FILE_UTILS
#define ABCC_FILE_UTILS

#include <stdio.h>
#include <errno.h>

#include "str_utils.h"


inline str_owner read_file_to_memory(char const* filename) {
  if (filename == NULL) {
    fprintf(stderr, "[%s:%d] Unexpected null pointer.", __FILE__, __LINE__);
    exit(1);
  }

  FILE* f = fopen(filename, "rb");
  if (f == NULL) {
    fprintf(stderr, "[%s:%d] Failed to fopen_s file [%s].", __FILE__, __LINE__, filename);
    exit(1);
  }
  if (fseek(f, 0, SEEK_END)) {
    fprintf(stderr, "[%s:%d] Failed to fseek file [%s].", __FILE__, __LINE__, filename);
    exit(1);
  }

  long file_length = ftell(f);
  if (errno) {
    fprintf(stderr, "[%s:%d] Failed to ftell file [%s].", __FILE__, __LINE__, filename);
    exit(1);
  }

  rewind(f);

  str_owner o = str_owner_new(file_length);
  if (fread(o.start, file_length, 1, f) != 1) {
    fprintf(stderr, "[%s:%d] Failed to fread file [%s].", __FILE__, __LINE__, filename);
    exit(1);
  }

  if (fclose(f)) {
    fprintf(stderr, "[%s:%d] Failed to fclose file [%s].", __FILE__, __LINE__, filename);
    exit(1);
  }

  return o;
}

#endif 
