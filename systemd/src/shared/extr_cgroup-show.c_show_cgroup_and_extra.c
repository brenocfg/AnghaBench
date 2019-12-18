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
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  OutputFlags ;

/* Variables and functions */
 int /*<<< orphan*/  assert (char const*) ; 
 int show_cgroup (char const*,char const*,char const*,size_t,int /*<<< orphan*/ ) ; 
 int show_extra_pids (char const*,char const*,char const*,size_t,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ ) ; 

int show_cgroup_and_extra(
                const char *controller,
                const char *path,
                const char *prefix,
                size_t n_columns,
                const pid_t extra_pids[],
                unsigned n_extra_pids,
                OutputFlags flags) {

        int r;

        assert(path);

        r = show_cgroup(controller, path, prefix, n_columns, flags);
        if (r < 0)
                return r;

        return show_extra_pids(controller, path, prefix, n_columns, extra_pids, n_extra_pids, flags);
}