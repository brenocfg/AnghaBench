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
 int /*<<< orphan*/  test_ascii_is_valid () ; 
 int /*<<< orphan*/  test_ascii_is_valid_n () ; 
 int /*<<< orphan*/  test_utf16_to_utf8 () ; 
 int /*<<< orphan*/  test_utf8_console_width () ; 
 int /*<<< orphan*/  test_utf8_encoded_valid_unichar () ; 
 int /*<<< orphan*/  test_utf8_escape_invalid () ; 
 int /*<<< orphan*/  test_utf8_escape_non_printable () ; 
 int /*<<< orphan*/  test_utf8_escape_non_printable_full () ; 
 int /*<<< orphan*/  test_utf8_is_printable () ; 
 int /*<<< orphan*/  test_utf8_is_valid () ; 
 int /*<<< orphan*/  test_utf8_n_codepoints () ; 
 int /*<<< orphan*/  test_utf8_to_utf16 () ; 

int main(int argc, char *argv[]) {
        test_utf8_is_valid();
        test_utf8_is_printable();
        test_ascii_is_valid();
        test_ascii_is_valid_n();
        test_utf8_encoded_valid_unichar();
        test_utf8_escape_invalid();
        test_utf8_escape_non_printable();
        test_utf8_escape_non_printable_full();
        test_utf16_to_utf8();
        test_utf8_n_codepoints();
        test_utf8_console_width();
        test_utf8_to_utf16();

        return 0;
}