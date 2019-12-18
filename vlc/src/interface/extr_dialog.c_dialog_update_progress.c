#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* pf_update_progress ) (int /*<<< orphan*/ ,TYPE_3__*,float,char*) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  p_cbs_data; TYPE_1__ cbs; } ;
typedef  TYPE_2__ vlc_dialog_provider ;
struct TYPE_10__ {char* psz_progress_text; scalar_t__ b_progress_indeterminate; } ;
typedef  TYPE_3__ vlc_dialog_id ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_2__* get_dialog_provider (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_3__*,float,char*) ; 
 scalar_t__ vlc_dialog_is_cancelled (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dialog_update_progress(vlc_object_t *p_obj, vlc_dialog_id *p_id, float f_value,
                       char *psz_text)
{
    assert(p_obj != NULL && p_id != NULL);
    vlc_dialog_provider *p_provider = get_dialog_provider(p_obj, false);

    vlc_mutex_lock(&p_provider->lock);
    if (p_provider->cbs.pf_update_progress == NULL ||
        vlc_dialog_is_cancelled(p_obj, p_id))
    {
        vlc_mutex_unlock(&p_provider->lock);
        free(psz_text);
        return VLC_EGENERIC;
    }

    if (p_id->b_progress_indeterminate)
        f_value = 0.0f;

    if (psz_text != NULL)
    {
        free(p_id->psz_progress_text);
        p_id->psz_progress_text = psz_text;
    }
    p_provider->cbs.pf_update_progress(p_provider->p_cbs_data, p_id, f_value,
                                       p_id->psz_progress_text);

    vlc_mutex_unlock(&p_provider->lock);
    return VLC_SUCCESS;
}