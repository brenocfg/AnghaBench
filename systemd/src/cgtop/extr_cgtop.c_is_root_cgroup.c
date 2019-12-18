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
 scalar_t__ detect_container () ; 
 int empty_or_root (char const*) ; 

__attribute__((used)) static bool is_root_cgroup(const char *path) {

        /* Returns true if the specified path belongs to the root cgroup. The root cgroup is special on cgroup v2 as it
         * carries only very few attributes in order not to export multiple truth about system state as most
         * information is available elsewhere in /proc anyway. We need to be able to deal with that, and need to get
         * our data from different sources in that case.
         *
         * There's one extra complication in all of this, though 😣: if the path to the cgroup indicates we are in the
         * root cgroup this might actually not be the case, because cgroup namespacing might be in effect
         * (CLONE_NEWCGROUP). Since there's no nice way to distinguish a real cgroup root from a fake namespaced one we
         * do an explicit container check here, under the assumption that CLONE_NEWCGROUP is generally used when
         * container managers are used too.
         *
         * Note that checking for a container environment is kinda ugly, since in theory people could use cgtop from
         * inside a container where cgroup namespacing is turned off to watch the host system. However, that's mostly a
         * theoretic usecase, and if people actually try all they'll lose is accounting for the top-level cgroup. Which
         * isn't too bad. */

        if (detect_container() > 0)
                return false;

        return empty_or_root(path);
}