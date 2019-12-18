#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  STRV_MAKE (char*,...) ; 
 int /*<<< orphan*/  STRV_MAKE_EMPTY ; 
 int /*<<< orphan*/  test_foreach_string () ; 
 int /*<<< orphan*/  test_invalid_unquote (char*) ; 
 int /*<<< orphan*/  test_specifier_printf () ; 
 int /*<<< orphan*/  test_startswith_set () ; 
 int /*<<< orphan*/  test_str_in_set () ; 
 int /*<<< orphan*/  test_strptr_in_set () ; 
 int /*<<< orphan*/  test_strv_equal () ; 
 int /*<<< orphan*/  test_strv_extend () ; 
 int /*<<< orphan*/  test_strv_extend_n () ; 
 int /*<<< orphan*/  test_strv_extend_strv () ; 
 int /*<<< orphan*/  test_strv_extend_strv_concat () ; 
 int /*<<< orphan*/  test_strv_extendf () ; 
 int /*<<< orphan*/  test_strv_find () ; 
 int /*<<< orphan*/  test_strv_find_prefix () ; 
 int /*<<< orphan*/  test_strv_find_startswith () ; 
 int /*<<< orphan*/  test_strv_fnmatch () ; 
 int /*<<< orphan*/  test_strv_foreach () ; 
 int /*<<< orphan*/  test_strv_foreach_backwards () ; 
 int /*<<< orphan*/  test_strv_foreach_pair () ; 
 int /*<<< orphan*/  test_strv_free_free () ; 
 int /*<<< orphan*/  test_strv_from_stdarg_alloca () ; 
 int /*<<< orphan*/  test_strv_insert () ; 
 int /*<<< orphan*/  test_strv_is_uniq () ; 
 int /*<<< orphan*/  test_strv_join () ; 
 int /*<<< orphan*/  test_strv_join_prefix () ; 
 int /*<<< orphan*/  test_strv_make_nulstr () ; 
 int /*<<< orphan*/  test_strv_overlap () ; 
 int /*<<< orphan*/  test_strv_parse_nulstr () ; 
 int /*<<< orphan*/  test_strv_push () ; 
 int /*<<< orphan*/  test_strv_push_prepend () ; 
 int /*<<< orphan*/  test_strv_reverse () ; 
 int /*<<< orphan*/  test_strv_shell_escape () ; 
 int /*<<< orphan*/  test_strv_skip () ; 
 int /*<<< orphan*/  test_strv_sort () ; 
 int /*<<< orphan*/  test_strv_split () ; 
 int /*<<< orphan*/  test_strv_split_empty () ; 
 int /*<<< orphan*/  test_strv_split_extract () ; 
 int /*<<< orphan*/  test_strv_split_newlines () ; 
 int /*<<< orphan*/  test_strv_split_nulstr () ; 
 int /*<<< orphan*/  test_strv_unquote (char*,int /*<<< orphan*/ ) ; 

int main(int argc, char *argv[]) {
        test_specifier_printf();
        test_str_in_set();
        test_strptr_in_set();
        test_startswith_set();
        test_strv_foreach();
        test_strv_foreach_backwards();
        test_strv_foreach_pair();
        test_strv_find();
        test_strv_find_prefix();
        test_strv_find_startswith();
        test_strv_join();
        test_strv_join_prefix();

        test_strv_unquote("    foo=bar     \"waldo\"    zzz    ", STRV_MAKE("foo=bar", "waldo", "zzz"));
        test_strv_unquote("", STRV_MAKE_EMPTY);
        test_strv_unquote(" ", STRV_MAKE_EMPTY);
        test_strv_unquote("   ", STRV_MAKE_EMPTY);
        test_strv_unquote("   x", STRV_MAKE("x"));
        test_strv_unquote("x   ", STRV_MAKE("x"));
        test_strv_unquote("  x   ", STRV_MAKE("x"));
        test_strv_unquote("  \"x\"   ", STRV_MAKE("x"));
        test_strv_unquote("  'x'   ", STRV_MAKE("x"));
        test_strv_unquote("  'x\"'   ", STRV_MAKE("x\""));
        test_strv_unquote("  \"x'\"   ", STRV_MAKE("x'"));
        test_strv_unquote("a  '--b=c \"d e\"'", STRV_MAKE("a", "--b=c \"d e\""));

        /* trailing backslashes */
        test_strv_unquote("  x\\\\", STRV_MAKE("x\\"));
        test_invalid_unquote("  x\\");

        test_invalid_unquote("a  --b='c \"d e\"''");
        test_invalid_unquote("a  --b='c \"d e\" '\"");
        test_invalid_unquote("a  --b='c \"d e\"garbage");
        test_invalid_unquote("'");
        test_invalid_unquote("\"");
        test_invalid_unquote("'x'y'g");

        test_strv_split();
        test_strv_split_empty();
        test_strv_split_extract();
        test_strv_split_newlines();
        test_strv_split_nulstr();
        test_strv_parse_nulstr();
        test_strv_overlap();
        test_strv_sort();
        test_strv_extend_strv();
        test_strv_extend_strv_concat();
        test_strv_extend();
        test_strv_extendf();
        test_strv_from_stdarg_alloca();
        test_strv_insert();
        test_strv_push_prepend();
        test_strv_push();
        test_strv_equal();
        test_strv_is_uniq();
        test_strv_reverse();
        test_strv_shell_escape();
        test_strv_skip();
        test_strv_extend_n();
        test_strv_make_nulstr();
        test_strv_free_free();

        test_foreach_string();
        test_strv_fnmatch();

        return 0;
}