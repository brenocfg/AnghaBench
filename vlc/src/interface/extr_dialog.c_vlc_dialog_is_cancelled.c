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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_3__ {int b_cancelled; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ vlc_dialog_id ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

bool
vlc_dialog_is_cancelled(vlc_object_t *p_obj, vlc_dialog_id *p_id)
{
    (void) p_obj;
    assert(p_id != NULL);

    vlc_mutex_lock(&p_id->lock);
    bool b_cancelled = p_id->b_cancelled;
    vlc_mutex_unlock(&p_id->lock);
    return b_cancelled;
}