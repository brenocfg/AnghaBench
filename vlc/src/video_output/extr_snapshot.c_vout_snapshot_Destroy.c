#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  wait; TYPE_2__* picture; } ;
typedef  TYPE_1__ vout_snapshot_t ;
struct TYPE_7__ {struct TYPE_7__* p_next; } ;
typedef  TYPE_2__ picture_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  picture_Release (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 

void vout_snapshot_Destroy(vout_snapshot_t *snap)
{
    if (snap == NULL)
        return;

    picture_t *picture = snap->picture;
    while (picture) {
        picture_t *next = picture->p_next;
        picture_Release(picture);
        picture = next;
    }

    vlc_cond_destroy(&snap->wait);
    vlc_mutex_destroy(&snap->lock);
    free(snap);
}