#ifndef ABCC_STR_UTILS
#define ABCC_STR_UTILS

#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "mem_utils.h"

/*
No ownership is implied by a str_view.
*/
typedef struct str_view {
  char const* start;
  size_t len;
} str_view;

/*
Unique ownership is implied by a str_owner.
*/
typedef struct str_owner {
  char* start;
  size_t len;
} str_owner;

// str_view functions


inline str_view str_view_empty() {
  return (str_view) {
    .start = NULL, .len = 0
  };
}

/*
Safety: Unsafe, unbound strlen.
*/
inline str_view str_view_from_c_str(char* c_str) {
  return (str_view) {
    .start = c_str, .len = strlen(c_str)
  };
}

inline str_view str_view_from_str_owner(str_owner* o) {
  return (str_view) {
    .start = o->start, .len = o->len
  };
}

inline size_t str_view_char_index_of(str_view s, char c) {
  for (size_t n = 0; n < s.len; ++n) {
    if (s.start[n] == c) {
      return n;
    }
  }
  return SIZE_MAX;
}

inline str_view* str_view_skip(str_view* s, size_t len) {
  if (s->len < len) {
    fprintf(stderr, "[%s:%d] str_vew with length %zu cannot skip %zu bytes.", __FILE__, __LINE__, s->len, len);
    exit(1);
  }

  s->len -= len;
  s->start += len;

  return s;
}


inline str_view str_view_sub_prefix(str_view s, size_t len) {
  if (s.len < len) {
    fprintf(stderr, "[%s:%d] str_vew with length %zu cannot support a substring of length %zu.", __FILE__, __LINE__, s.len, len);
    exit(1);
  }

  return (str_view) {
    .start = s.start, .len = len
  };
}

inline bool str_view_equals_str_view(str_view l, str_view r) {
  if (l.len != r.len) {
    return false;
  }
  return memcmp(l.start, r.start, l.len) == 0;
}

// str_owner functions

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

// other

inline bool str_owner_equals_str_view(str_owner* o, str_view* v) {
  if (o->len != v->len) {
    return false;
  }
  return memcmp(o->start, v->start, o->len) == 0;
}


#endif 
