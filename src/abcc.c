#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "file_utils.h"
#include "str_utils.h"

// global constants
char const abcc_c_str[] = "abcc";

//

typedef struct abcc_cli_args {
  str_owner input_file;
} abcc_cli_args;

void abcc_cli_args_free(abcc_cli_args* a) {
  str_owner_free(&(a->input_file));
}

void help(bool asked_for_help) {
  fprintf(stderr,
    "abcc - Adam Barrowman's C Compiler\n"
    "usage: abcc [options] input_file\n"
    "optional arguments:\n"
    "-h/--help - Shows this help instead of normal compilation.\n"
    "positional arguments:\n"
    "input_file - The file to compile.\n"
  );
  exit(asked_for_help ? 0 : 1);
}

abcc_cli_args parse_args(int argc, char** argv) {
  abcc_cli_args args = {
    .input_file = str_owner_new_empty(),
  };

  if (argc < 2) {
    fprintf(stderr, "[%s:%d] abcc requires at least 2 arguments.\n", __FILE__, __LINE__);
    help(false);
  }

  // ignore the first argument

  bool expect_options = true;
  for (int n = 1; n < argc; ++n) {
    str_owner arg = str_owner_new_from_c_str(argv[n]);
    if (expect_options && str_owner_starts_with(&arg, '-')) {
      if (str_owner_equals_c_str(&arg, "-h") || str_owner_equals_c_str(&arg, "-h")) {
        help(true);
      } else if (str_owner_equals_c_str(&arg, "--")) {
        expect_options = false;
      } else {
        fprintf(stderr, "[%s:%d] abcc does not support unknown option \"%.*s\".\n", __FILE__, __LINE__, (int)arg.len, arg.start);
        help(false);
      }

    } else { // positional arguments
      str_owner_move(&arg, &(args.input_file));
      expect_options = false;
    }
    str_owner_free(&arg);
  }

  if (expect_options) {
    fprintf(stderr, "[%s:%d] abcc requires at least 1 argument\n", __FILE__, __LINE__);
    help(false);
  }

  return args;
}


int main(int argc, char** argv) {
  abcc_cli_args args = parse_args(argc, argv);

  // TODO

  abcc_cli_args_free(&args);
  return 0;
}
