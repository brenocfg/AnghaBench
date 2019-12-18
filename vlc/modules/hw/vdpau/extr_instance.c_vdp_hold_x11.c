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
typedef  int /*<<< orphan*/  vdp_t ;
struct TYPE_3__ {scalar_t__ refs; int /*<<< orphan*/  device; struct TYPE_3__* next; int /*<<< orphan*/ * vdp; } ;
typedef  TYPE_1__ vdp_instance_t ;
typedef  int /*<<< orphan*/  VdpDevice ;

/* Variables and functions */
 scalar_t__ UINTPTR_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* list ; 
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

vdp_t *vdp_hold_x11(vdp_t *vdp, VdpDevice *restrict devp)
{
    vdp_instance_t *vi, **pp = &list;

    pthread_mutex_lock(&lock);
    for (;;)
    {
        vi = *pp;
        assert(vi != NULL);
        if (vi->vdp == vdp)
            break;
        pp = &vi->next;
    }

    assert(vi->refs < UINTPTR_MAX);
    vi->refs++;
    pthread_mutex_unlock(&lock);

    if (devp != NULL)
        *devp = vi->device;
   return vdp;
}