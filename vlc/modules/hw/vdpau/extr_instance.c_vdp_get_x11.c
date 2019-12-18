#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vdp_t ;
struct TYPE_6__ {int /*<<< orphan*/  device; int /*<<< orphan*/ * vdp; struct TYPE_6__* next; } ;
typedef  TYPE_1__ vdp_instance_t ;
typedef  scalar_t__ VdpStatus ;
typedef  int /*<<< orphan*/  VdpDevice ;

/* Variables and functions */
 scalar_t__ VDP_STATUS_ERROR ; 
 scalar_t__ VDP_STATUS_OK ; 
 scalar_t__ VDP_STATUS_RESOURCES ; 
 char* getenv (char*) ; 
 TYPE_1__* list ; 
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 scalar_t__ vdp_instance_create (char const*,int,TYPE_1__**) ; 
 int /*<<< orphan*/  vdp_instance_destroy (TYPE_1__*) ; 
 TYPE_1__* vdp_instance_lookup (char const*,int) ; 

VdpStatus vdp_get_x11(const char *display_name, int snum,
                      vdp_t **restrict vdpp, VdpDevice *restrict devicep)
{
    vdp_instance_t *vi, *vi2;
    VdpStatus err = VDP_STATUS_RESOURCES;

    if (display_name == NULL)
    {
        display_name = getenv("DISPLAY");
        if (display_name == NULL)
            return VDP_STATUS_ERROR;
    }

    pthread_mutex_lock(&lock);
    vi = vdp_instance_lookup(display_name, snum);
    pthread_mutex_unlock(&lock);
    if (vi != NULL)
        goto found;

    err = vdp_instance_create(display_name, snum, &vi);
    if (err != VDP_STATUS_OK)
        return err;

    pthread_mutex_lock(&lock);
    vi2 = vdp_instance_lookup(display_name, snum);
    if (unlikely(vi2 != NULL))
    {   /* Another thread created the instance (race condition corner case) */
        pthread_mutex_unlock(&lock);
        vdp_instance_destroy(vi);
        vi = vi2;
    }
    else
    {
        vi->next = list;
        list = vi;
        pthread_mutex_unlock(&lock);
    }
found:
    *vdpp = vi->vdp;
    *devicep = vi->device;
    return VDP_STATUS_OK;
}