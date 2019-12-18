#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  audio_output_t ;
struct TYPE_7__ {int /*<<< orphan*/  lock; } ;
struct TYPE_8__ {TYPE_4__* list; int /*<<< orphan*/  lock; } ;
struct TYPE_9__ {int /*<<< orphan*/  lock; TYPE_1__ vp; TYPE_2__ dev; int /*<<< orphan*/  refs; } ;
typedef  TYPE_3__ aout_owner_t ;
struct TYPE_10__ {struct TYPE_10__* name; struct TYPE_10__* next; } ;
typedef  TYPE_4__ aout_dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_OBJECT (int /*<<< orphan*/ *) ; 
 TYPE_3__* aout_owner (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_fetch_sub_explicit (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_thread_fence (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 int /*<<< orphan*/  memory_order_acquire ; 
 int /*<<< orphan*/  memory_order_release ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_object_delete (int /*<<< orphan*/ ) ; 

void aout_Release(audio_output_t *aout)
{
    aout_owner_t *owner = aout_owner(aout);

    if (atomic_fetch_sub_explicit(&owner->refs, 1, memory_order_release))
        return;

    atomic_thread_fence(memory_order_acquire);

    vlc_mutex_destroy (&owner->dev.lock);
    for (aout_dev_t *dev = owner->dev.list, *next; dev != NULL; dev = next)
    {
        next = dev->next;
        free (dev->name);
        free (dev);
    }

    vlc_mutex_destroy (&owner->vp.lock);
    vlc_mutex_destroy (&owner->lock);
    vlc_object_delete(VLC_OBJECT(aout));
}