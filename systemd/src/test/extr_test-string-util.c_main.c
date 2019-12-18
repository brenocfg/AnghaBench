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
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  test_ascii_strcasecmp_n () ; 
 int /*<<< orphan*/  test_ascii_strcasecmp_nn () ; 
 int /*<<< orphan*/  test_ascii_strlower () ; 
 int /*<<< orphan*/  test_cellescape () ; 
 int /*<<< orphan*/  test_delete_chars () ; 
 int /*<<< orphan*/  test_delete_trailing_chars () ; 
 int /*<<< orphan*/  test_delete_trailing_slashes () ; 
 int /*<<< orphan*/  test_endswith () ; 
 int /*<<< orphan*/  test_endswith_no_case () ; 
 int /*<<< orphan*/  test_first_word () ; 
 int /*<<< orphan*/  test_foreach_word () ; 
 int /*<<< orphan*/  test_foreach_word_quoted () ; 
 int /*<<< orphan*/  test_free_and_strndup () ; 
 int /*<<< orphan*/  test_in_charset () ; 
 int /*<<< orphan*/  test_memory_startswith () ; 
 int /*<<< orphan*/  test_memory_startswith_no_case () ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_skip_leading_chars () ; 
 int /*<<< orphan*/  test_split_pair () ; 
 int /*<<< orphan*/  test_strcmp_ptr () ; 
 int /*<<< orphan*/  test_streq_ptr () ; 
 int /*<<< orphan*/  test_strextend () ; 
 int /*<<< orphan*/  test_strextend_with_separator () ; 
 int /*<<< orphan*/  test_string_has_cc () ; 
 int /*<<< orphan*/  test_strjoina () ; 
 int /*<<< orphan*/  test_strlen_ptr () ; 
 int /*<<< orphan*/  test_strrep () ; 
 int /*<<< orphan*/  test_strshorten () ; 
 int /*<<< orphan*/  test_strstrip () ; 

int main(int argc, char *argv[]) {
        test_setup_logging(LOG_DEBUG);

        test_free_and_strndup();
        test_ascii_strcasecmp_n();
        test_ascii_strcasecmp_nn();
        test_cellescape();
        test_streq_ptr();
        test_strstrip();
        test_strextend();
        test_strextend_with_separator();
        test_strrep();
        test_string_has_cc();
        test_ascii_strlower();
        test_strshorten();
        test_strjoina();
        test_strcmp_ptr();
        test_foreach_word();
        test_foreach_word_quoted();
        test_endswith();
        test_endswith_no_case();
        test_delete_chars();
        test_delete_trailing_chars();
        test_delete_trailing_slashes();
        test_skip_leading_chars();
        test_in_charset();
        test_split_pair();
        test_first_word();
        test_strlen_ptr();
        test_memory_startswith();
        test_memory_startswith_no_case();

        return 0;
}