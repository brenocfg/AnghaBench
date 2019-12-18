#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  strm_value ;
typedef  int /*<<< orphan*/  strm_array ;
struct TYPE_8__ {int /*<<< orphan*/  lval; } ;
typedef  TYPE_1__ parser_state ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int FALSE ; 
 void* TRUE ; 
 int /*<<< orphan*/  dump_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char const) ; 
 scalar_t__ node_parse_file (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  node_parse_free (TYPE_1__*) ; 
 int /*<<< orphan*/  node_parse_init (TYPE_1__*) ; 
 int node_parse_input (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ node_parse_string (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  node_run (TYPE_1__*) ; 
 int /*<<< orphan*/  node_stop () ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  strm_ary_new (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * strm_ary_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_ary_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_loop () ; 
 void* strm_option_verbose ; 
 int /*<<< orphan*/  strm_str_new (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_str_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_var_def (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

int
main(int argc, const char**argv)
{
  const char *prog = argv[0];
  const char *e_prog = NULL;
  int i, n = 0, verbose = FALSE, check = FALSE;
  parser_state state;

  while (argc > 1 && argv[1][0] == '-') {
    const char *s = argv[1]+1;
    while (*s) {
      switch (*s) {
      case 'v':
        verbose = TRUE;
        /* fall through */
      case 'w':
        strm_option_verbose = TRUE;
        break;
      case 'c':
        check = TRUE;
        break;
      case 'e':
        if (s[1] == '\0') {
          e_prog = argv[2];
          argc--; argv++;
        }
        else {
          e_prog = &s[1];
        }
        goto next_arg;
      default:
        fprintf(stderr, "%s: unknown option -%c\n", prog, *s);
      }
      s++;
    }
  next_arg:
    argc--; argv++;
  }
  node_parse_init(&state);

  if (e_prog) {
    n += node_parse_string(&state, e_prog);
  }
  else if (argc == 1) {              /* no args */
    n = node_parse_input(&state, stdin, "stdin");
  }
  else {
    for (i=1; i<argc; i++) {
      n += node_parse_file(&state, argv[i]);
    }
  }

  if (n == 0) {
    if (verbose) {
      dump_node(state.lval, 0);
    }
    if (check) {
      puts("Syntax OK");
    }
    else {
      strm_array av = strm_ary_new(NULL, argc);
      strm_value* buf = strm_ary_ptr(av);
      int i;

      for (i=0; i<argc; i++) {
        buf[i] = strm_str_value(strm_str_new(argv[i], strlen(argv[i])));
      }
      strm_var_def(NULL, "ARGV", strm_ary_value(av));
      node_run(&state);
      strm_loop();
      node_stop();
    }
  }
  else if (check) {
    puts("Syntax NG");
  }
  node_parse_free(&state);
  return n > 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}