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
 int ENOMEM ; 
 int /*<<< orphan*/  SIZE_MAX ; 
 int /*<<< orphan*/  assert (char**) ; 
 scalar_t__ detect_container () ; 
 int get_process_cmdline (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int read_one_line_file (char*,char**) ; 
 char* secure_getenv (char*) ; 
 char* strdup (char const*) ; 

int proc_cmdline(char **ret) {
        const char *e;
        assert(ret);

        /* For testing purposes it is sometimes useful to be able to override what we consider /proc/cmdline to be */
        e = secure_getenv("SYSTEMD_PROC_CMDLINE");
        if (e) {
                char *m;

                m = strdup(e);
                if (!m)
                        return -ENOMEM;

                *ret = m;
                return 0;
        }

        if (detect_container() > 0)
                return get_process_cmdline(1, SIZE_MAX, 0, ret);
        else
                return read_one_line_file("/proc/cmdline", ret);
}