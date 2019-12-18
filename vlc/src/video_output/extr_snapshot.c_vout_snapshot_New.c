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
struct TYPE_4__ {int is_available; int /*<<< orphan*/ * picture; scalar_t__ request_count; int /*<<< orphan*/  wait; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ vout_snapshot_t ;

/* Variables and functions */
 TYPE_1__* malloc (int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_cond_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 

vout_snapshot_t *vout_snapshot_New(void)
{
    vout_snapshot_t *snap = malloc(sizeof (*snap));
    if (unlikely(snap == NULL))
        return NULL;

    vlc_mutex_init(&snap->lock);
    vlc_cond_init(&snap->wait);

    snap->is_available = true;
    snap->request_count = 0;
    snap->picture = NULL;
    return snap;
}