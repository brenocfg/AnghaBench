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
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  check_p_g_s (char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void test_path_get_session(void) {
        check_p_g_s("/user.slice/user-1000.slice/session-2.scope/foobar.service", 0, "2");
        check_p_g_s("/session-3.scope", 0, "3");
        check_p_g_s("/session-.scope", -ENXIO, NULL);
        check_p_g_s("", -ENXIO, NULL);
}