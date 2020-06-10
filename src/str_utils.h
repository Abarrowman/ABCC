#ifndef ABCC_STR_UTILS
#define ABCC_STR_UTILS

#define __STDC_WANT_LIB_EXT1__ 1
#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "mem_utils.h"

/*
No ownership is implied by a str_view.
*/
typedef struct str_view {
  char* start;
  size_t len;
} str_view;

/*
Unique ownership is implied by a str_owner.
*/
typedef struct str_owner {
  char* start;
  size_t len;
} str_owner;


inline void str_owner_free(str_owner* o) {
  free(o->start);
  o->start = NULL;
  o->len = 0;
}

inline str_owner str_owner_new_empty() {
  return (str_owner) {
    .start = 0, .len = 0
  };
}

inline str_owner str_owner_new(size_t len) {
  return (str_owner) {
    .start = xmalloc(sizeof(char) * len), .len = len
  };
}

/*
Safety: Unsafe, unbound strlen.
*/
inline str_owner str_owner_new_from_c_str(char* c_str) {
  if (c_str == NULL) {
    fprintf(stderr, "[%s:%d] Unexpected null pointer.", __FILE__, __LINE__);
    exit(1);
  }
  size_t len = strlen(c_str);
  str_owner s = str_owner_new(len);

  memcpy(s.start, c_str, len);
  return s;
}


inline void str_owner_move(str_owner* from, str_owner* to) {
  str_owner_free(to);
  to->start = from->start;
  to->len = from->len;
  from->start = NULL;
  from->len = 0;
}

/*
Safety: Unsafe, unbound strlen.
*/
inline bool str_owner_equals_c_str(str_owner* o, char* c_str) {
  size_t c_str_len = strlen(c_str);
  if (c_str_len != o->len) {
    return false;
  }

  return memcmp(o->start, c_str, o->len) == 0;
}


inline bool str_owner_starts_with(str_owner* o, char c) {
  if (o->len == 0) {
    return false;
  } else {
    return o->start[0] == c;
  }
}

#endif 
