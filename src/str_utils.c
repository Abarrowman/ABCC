#include "str_utils.h"

extern inline void str_owner_free(str_owner* o);

extern inline str_owner str_owner_new_empty();

extern inline str_owner str_owner_new(size_t len);

extern inline str_owner str_owner_new_from_c_str(char* c_str);

extern inline void str_owner_move(str_owner* from, str_owner* to);

extern inline bool str_owner_equals_c_str(str_owner* o, char* c_str);

extern inline bool str_owner_starts_with(str_owner* o, char c);
