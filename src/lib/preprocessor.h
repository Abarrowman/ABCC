#ifndef ABCC_PREPROCESSOR
#define ABCC_PREPROCESSOR

#include "str_utils.h"

inline void pry_punctuator() {

}

inline void pry_string_literal() {
}

inline void pry_character_constant() {
}

inline void pry_pp_number() {
  // [0-9]+(\.[0-9]*)?
}


inline void pry_identifier() {
  //[a-zA-Z]+[a-zA-Z0-9]*
}

inline str_view pry_header_name(str_view* view) {
  if (view->len < 2) {
    fprintf(stderr, "[%s:%d] str_view is too short for a header_name.", __FILE__, __LINE__);
    exit(1);
  }

  char first = *(view->start);
  char last;
  if (first == '<') {
    last = '>';
  } else if (first == '"') {
    last = '"';
  } else {
    fprintf(stderr, "[%s:%d] header_name must start with \" or <", __FILE__, __LINE__);
    exit(1);
  }

  str_view_skip(view, 1);
  size_t index = str_view_char_index_of(*view, last);
  if (index == SIZE_MAX) {
    fprintf(stderr, "[%s:%d] header_name that starts with %c must end with %c", __FILE__, __LINE__, first, last);
    exit(1);
  }

  str_view header = str_view_sub_prefix(*view, index);
  str_view_skip(view, index + 1);
  return header;
}

inline void pry_preprocessing_token() {
}

inline str_owner preprocess(str_view in) {
  // TODO
  return str_owner_new_empty();
}

#endif
