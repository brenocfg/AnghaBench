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
struct TYPE_3__ {scalar_t__ request_count; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ vout_snapshot_t ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

bool vout_snapshot_IsRequested(vout_snapshot_t *snap)
{
    if (snap == NULL)
        return false;

    bool has_request = false;
    if (!vlc_mutex_trylock(&snap->lock)) {
        has_request = snap->request_count > 0;
        vlc_mutex_unlock(&snap->lock);
    }
    return has_request;
}