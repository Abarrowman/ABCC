#include "test_utils.h"

void test_test_utils() {
  test_size_t_equal((size_t)1, (size_t)1);

  str_view l = str_view_from_c_str("hello");
  str_view r = str_view_from_c_str("hello");
  test_str_view_equal(l, r);
}

#include "preprocessor.h"

void test_preprocessor() {
  str_view header_name = str_view_from_c_str("<stdio.h>");
  str_view empty = str_view_empty();

  str_view pried = pry_header_name(&header_name);
  str_view expected = str_view_from_c_str("stdio.h");
  test_str_view_equal(pried, expected);
  test_str_view_equal(header_name, empty);

  header_name = str_view_from_c_str("\"stdlib.h\"\nint main(){\n;return 0;\n}\n");
  str_view const remaining_program = str_view_from_c_str("\nint main(){\n;return 0;\n}\n");

  pried = pry_header_name(&header_name);
  expected = str_view_from_c_str("stdlib.h");
  test_str_view_equal(pried, expected);
  test_str_view_equal(header_name, remaining_program);
}

int main() {

  test_test_utils();
  test_preprocessor();

  return 0;
}
