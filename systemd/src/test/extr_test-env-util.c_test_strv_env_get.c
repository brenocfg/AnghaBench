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
 char** STRV_MAKE (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  assert_se (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  streq (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strv_env_get (char**,char*) ; 

__attribute__((used)) static void test_strv_env_get(void) {
        char **l;

        l = STRV_MAKE("ONE_OR_TWO=1", "THREE=3", "ONE_OR_TWO=2", "FOUR=4");

        assert_se(streq(strv_env_get(l, "ONE_OR_TWO"), "2"));
        assert_se(streq(strv_env_get(l, "THREE"), "3"));
        assert_se(streq(strv_env_get(l, "FOUR"), "4"));
}