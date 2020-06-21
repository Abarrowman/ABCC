#ifndef ABCC_TEST_UTILS
#define ABCC_TEST_UTILS

#include <stdio.h>

#include "str_utils.h"

#define test_size_t_equal(left, right) \
if (left != right) { fprintf(stderr, "[%s:%d] %zu != %zu", __FILE__, __LINE__, left, right); exit(1); }

#define test_str_view_equal(left, right) \
if (!str_view_equals_str_view(left, right)) {\
fprintf(stderr, "[%s:%d] \"%.*s\" != \"%.*s\"", __FILE__, __LINE__, (int)left.len, left.start, (int)right.len, right.start);\
exit(1); }

#endif