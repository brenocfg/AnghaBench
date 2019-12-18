#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  dialog_array; } ;
typedef  TYPE_1__ vlc_dialog_provider ;
struct TYPE_8__ {scalar_t__ i_refcount; int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__ vlc_dialog_id ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dialog_id_release (TYPE_2__*) ; 
 scalar_t__ vlc_array_index_of_item (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_array_remove (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dialog_remove_locked(vlc_dialog_provider *p_provider, vlc_dialog_id *p_id)
{
    ssize_t i_idx = vlc_array_index_of_item(&p_provider->dialog_array, p_id);
    assert(i_idx >= 0);
    vlc_array_remove(&p_provider->dialog_array, i_idx);

    vlc_mutex_lock(&p_id->lock);
    p_id->i_refcount--;
    if (p_id->i_refcount == 0)
    {
        vlc_mutex_unlock(&p_id->lock);
        dialog_id_release(p_id);
    }
    else
        vlc_mutex_unlock(&p_id->lock);
}