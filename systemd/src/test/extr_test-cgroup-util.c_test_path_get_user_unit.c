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
 int /*<<< orphan*/  check_p_g_u_u (char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void test_path_get_user_unit(void) {
        check_p_g_u_u("/user.slice/user-1000.slice/session-2.scope/foobar.service", 0, "foobar.service");
        check_p_g_u_u("/user.slice/user-1000.slice/session-2.scope/waldo.slice/foobar.service", 0, "foobar.service");
        check_p_g_u_u("/user.slice/user-1002.slice/session-2.scope/foobar.service/waldo", 0, "foobar.service");
        check_p_g_u_u("/user.slice/user-1000.slice/session-2.scope/foobar.service/waldo/uuuux", 0, "foobar.service");
        check_p_g_u_u("/user.slice/user-1000.slice/session-2.scope/waldo/waldo/uuuux", -ENXIO, NULL);
        check_p_g_u_u("/user.slice/user-1000.slice/session-2.scope/foobar@pie.service/pa/po", 0, "foobar@pie.service");
        check_p_g_u_u("/session-2.scope/foobar@pie.service/pa/po", 0, "foobar@pie.service");
        check_p_g_u_u("/xyz.slice/xyz-waldo.slice/session-77.scope/foobar@pie.service/pa/po", 0, "foobar@pie.service");
        check_p_g_u_u("/meh.service", -ENXIO, NULL);
        check_p_g_u_u("/session-3.scope/_cpu.service", 0, "cpu.service");
        check_p_g_u_u("/user.slice/user-1000.slice/user@1000.service/server.service", 0, "server.service");
        check_p_g_u_u("/user.slice/user-1000.slice/user@1000.service/foobar.slice/foobar@pie.service", 0, "foobar@pie.service");
        check_p_g_u_u("/user.slice/user-1000.slice/user@.service/server.service", -ENXIO, NULL);
}