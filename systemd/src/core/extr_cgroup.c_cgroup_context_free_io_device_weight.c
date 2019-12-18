#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct TYPE_8__* path; int /*<<< orphan*/  io_device_weights; } ;
typedef  TYPE_1__ CGroupIODeviceWeight ;
typedef  TYPE_1__ CGroupContext ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  device_weights ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void cgroup_context_free_io_device_weight(CGroupContext *c, CGroupIODeviceWeight *w) {
        assert(c);
        assert(w);

        LIST_REMOVE(device_weights, c->io_device_weights, w);
        free(w->path);
        free(w);
}