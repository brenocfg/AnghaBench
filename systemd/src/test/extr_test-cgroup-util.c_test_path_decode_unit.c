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
 int /*<<< orphan*/  check_p_d_u (char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void test_path_decode_unit(void) {
        check_p_d_u("getty@tty2.service", 0, "getty@tty2.service");
        check_p_d_u("getty@tty2.service/", 0, "getty@tty2.service");
        check_p_d_u("getty@tty2.service/xxx", 0, "getty@tty2.service");
        check_p_d_u("getty@.service/", -ENXIO, NULL);
        check_p_d_u("getty@.service", -ENXIO, NULL);
        check_p_d_u("getty.service", 0, "getty.service");
        check_p_d_u("getty", -ENXIO, NULL);
        check_p_d_u("getty/waldo", -ENXIO, NULL);
        check_p_d_u("_cpu.service", 0, "cpu.service");
}