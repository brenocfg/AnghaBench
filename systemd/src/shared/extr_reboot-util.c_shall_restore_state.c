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
 int proc_cmdline_get_bool (char*,int*) ; 

int shall_restore_state(void) {
        bool ret;
        int r;

        r = proc_cmdline_get_bool("systemd.restore_state", &ret);
        if (r < 0)
                return r;

        return r > 0 ? ret : true;
}