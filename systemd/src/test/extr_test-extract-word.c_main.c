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
 int /*<<< orphan*/  log_open () ; 
 int /*<<< orphan*/  log_parse_environment () ; 
 int /*<<< orphan*/  test_extract_first_word () ; 
 int /*<<< orphan*/  test_extract_first_word_and_warn () ; 
 int /*<<< orphan*/  test_extract_many_words () ; 

int main(int argc, char *argv[]) {
        log_parse_environment();
        log_open();

        test_extract_first_word();
        test_extract_first_word_and_warn();
        test_extract_many_words();

        return 0;
}