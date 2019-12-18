#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char const* options; } ;
struct TYPE_5__ {char const* options; } ;
struct TYPE_7__ {TYPE_2__ parameters_fragment; scalar_t__ from_fragment; TYPE_1__ parameters_proc_self_mountinfo; scalar_t__ from_proc_self_mountinfo; } ;
typedef  TYPE_3__ Mount ;

/* Variables and functions */

__attribute__((used)) static const char *mount_get_options(const Mount *m) {
        if (m->from_proc_self_mountinfo && m->parameters_proc_self_mountinfo.options)
                return m->parameters_proc_self_mountinfo.options;
        if (m->from_fragment && m->parameters_fragment.options)
                return m->parameters_fragment.options;
        return NULL;
}