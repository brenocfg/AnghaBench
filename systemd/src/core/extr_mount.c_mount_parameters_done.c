#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* fstype; void* options; void* what; } ;
typedef  TYPE_1__ MountParameters ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 void* mfree (void*) ; 

__attribute__((used)) static void mount_parameters_done(MountParameters *p) {
        assert(p);

        p->what = mfree(p->what);
        p->options = mfree(p->options);
        p->fstype = mfree(p->fstype);
}