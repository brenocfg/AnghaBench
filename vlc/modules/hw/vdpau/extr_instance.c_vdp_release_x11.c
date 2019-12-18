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
typedef  int /*<<< orphan*/  vdp_t ;
struct TYPE_4__ {scalar_t__ refs; struct TYPE_4__* next; int /*<<< orphan*/ * vdp; } ;
typedef  TYPE_1__ vdp_instance_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* list ; 
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vdp_instance_destroy (TYPE_1__*) ; 

void vdp_release_x11(vdp_t *vdp)
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

    assert(vi->refs > 0);
    vi->refs--;
    if (vi->refs > 0)
        vi = NULL; /* Keep the instance for now */
    else
        *pp = vi->next; /* Unlink the instance */
    pthread_mutex_unlock(&lock);

    if (vi != NULL)
        vdp_instance_destroy(vi);
}