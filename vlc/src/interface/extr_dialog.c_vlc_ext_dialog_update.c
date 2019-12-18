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
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  p_ext_data; int /*<<< orphan*/  (* pf_ext_update ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ vlc_dialog_provider ;
typedef  int /*<<< orphan*/  extension_dialog_t ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_1__* get_dialog_provider (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

int
vlc_ext_dialog_update(vlc_object_t *p_obj, extension_dialog_t *p_ext_dialog)
{
    assert(p_obj != NULL);
    vlc_dialog_provider *p_provider = get_dialog_provider(p_obj, false);

    vlc_mutex_lock(&p_provider->lock);
    if (p_provider->pf_ext_update == NULL)
    {
        vlc_mutex_unlock(&p_provider->lock);
        return VLC_EGENERIC;
    }
    p_provider->pf_ext_update(p_ext_dialog, p_provider->p_ext_data);
    vlc_mutex_unlock(&p_provider->lock);
    return VLC_SUCCESS;
}