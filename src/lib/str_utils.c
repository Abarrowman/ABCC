#include "str_utils.h"

// str_view functions

extern inline str_view str_view_empty();

extern inline str_view str_view_from_c_str(char* c_str);

extern inline str_view str_view_from_str_owner(str_owner* o);

extern inline size_t str_view_char_index_of(str_view s, char c);

extern inline str_view str_view_sub_prefix(str_view s, size_t len);

extern inline str_view* str_view_skip(str_view* s, size_t len);

extern inline bool str_view_equals_str_view(str_view l, str_view r);


// str_owner functions

extern inline void str_owner_free(str_owner* o);

extern inline str_owner str_owner_new_empty();

extern inline str_owner str_owner_new(size_t len);

extern inline str_owner str_owner_new_from_c_str(char* c_str);

extern inline void str_owner_move(str_owner* from, str_owner* to);

extern inline bool str_owner_equals_c_str(str_owner* o, char* c_str);

extern inline bool str_owner_starts_with(str_owner* o, char c);

// other

extern inline bool str_owner_equals_str_view(str_owner* o, str_view* v);
