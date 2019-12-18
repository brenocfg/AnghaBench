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
 int /*<<< orphan*/  check_p_g_u (char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void test_path_get_unit(void) {
        check_p_g_u("/system.slice/foobar.service/sdfdsaf", 0, "foobar.service");
        check_p_g_u("/system.slice/getty@tty5.service", 0, "getty@tty5.service");
        check_p_g_u("/system.slice/getty@tty5.service/aaa/bbb", 0, "getty@tty5.service");
        check_p_g_u("/system.slice/getty@tty5.service/", 0, "getty@tty5.service");
        check_p_g_u("/system.slice/getty@tty6.service/tty5", 0, "getty@tty6.service");
        check_p_g_u("sadfdsafsda", -ENXIO, NULL);
        check_p_g_u("/system.slice/getty####@tty6.service/xxx", -ENXIO, NULL);
        check_p_g_u("/system.slice/system-waldo.slice/foobar.service/sdfdsaf", 0, "foobar.service");
        check_p_g_u("/system.slice/system-waldo.slice/_cpu.service/sdfdsaf", 0, "cpu.service");
        check_p_g_u("/user.slice/user-1000.slice/user@1000.service/server.service", 0, "user@1000.service");
        check_p_g_u("/user.slice/user-1000.slice/user@.service/server.service", -ENXIO, NULL);
}