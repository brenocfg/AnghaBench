#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ vlc_dialog_provider ;
typedef  int /*<<< orphan*/  vlc_dialog_id ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dialog_cancel_locked (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dialog_remove_locked (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* get_dialog_provider (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void
vlc_dialog_release(vlc_object_t *p_obj, vlc_dialog_id *p_id)
{
    assert(p_obj != NULL && p_id != NULL);
    vlc_dialog_provider *p_provider = get_dialog_provider(p_obj, false);

    vlc_mutex_lock(&p_provider->lock);
    dialog_cancel_locked(p_provider, p_id);
    dialog_remove_locked(p_provider, p_id);
    vlc_mutex_unlock(&p_provider->lock);
}