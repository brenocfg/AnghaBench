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
 int /*<<< orphan*/  assert_se (int) ; 
 int env_name_is_valid (char*) ; 

__attribute__((used)) static void test_env_name_is_valid(void) {
        assert_se(env_name_is_valid("test"));

        assert_se(!env_name_is_valid(NULL));
        assert_se(!env_name_is_valid(""));
        assert_se(!env_name_is_valid("xxx\a"));
        assert_se(!env_name_is_valid("xxx\007b"));
        assert_se(!env_name_is_valid("\007\009"));
        assert_se(!env_name_is_valid("5_starting_with_a_number_is_wrong"));
        assert_se(!env_name_is_valid("#¤%&?_only_numbers_letters_and_underscore_allowed"));
}