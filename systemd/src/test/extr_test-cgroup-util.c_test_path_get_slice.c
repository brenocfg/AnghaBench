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
 char* SPECIAL_ROOT_SLICE ; 
 int /*<<< orphan*/  check_p_g_slice (char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void test_path_get_slice(void) {
        check_p_g_slice("/user.slice", 0, "user.slice");
        check_p_g_slice("/foobar", 0, SPECIAL_ROOT_SLICE);
        check_p_g_slice("/user.slice/user-waldo.slice", 0, "user-waldo.slice");
        check_p_g_slice("", 0, SPECIAL_ROOT_SLICE);
        check_p_g_slice("foobar", 0, SPECIAL_ROOT_SLICE);
        check_p_g_slice("foobar.slice", 0, "foobar.slice");
        check_p_g_slice("foo.slice/foo-bar.slice/waldo.service", 0, "foo-bar.slice");
}