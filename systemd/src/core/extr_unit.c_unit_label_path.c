#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* fragment_path; scalar_t__ source_path; } ;
typedef  TYPE_1__ Unit ;

/* Variables and functions */
 scalar_t__ path_equal (char const*,char*) ; 

const char *unit_label_path(Unit *u) {
        const char *p;

        /* Returns the file system path to use for MAC access decisions, i.e. the file to read the SELinux label off
         * when validating access checks. */

        p = u->source_path ?: u->fragment_path;
        if (!p)
                return NULL;

        /* If a unit is masked, then don't read the SELinux label of /dev/null, as that really makes no sense */
        if (path_equal(p, "/dev/null"))
                return NULL;

        return p;
}