#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  (* pf_display_progress ) (int /*<<< orphan*/ ,TYPE_3__*,char const*,char*,int,float,char const*) ;int /*<<< orphan*/ * pf_cancel; int /*<<< orphan*/ * pf_update_progress; } ;
struct TYPE_10__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  p_cbs_data; TYPE_1__ cbs; } ;
typedef  TYPE_2__ vlc_dialog_provider ;
struct TYPE_11__ {int b_progress_indeterminate; char* psz_progress_text; } ;
typedef  TYPE_3__ vlc_dialog_id ;
typedef  int /*<<< orphan*/  va_list ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_DIALOG_PROGRESS ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 TYPE_3__* dialog_add_locked (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_3__*,char const*,char*,int,float,char const*) ; 
 int vasprintf (char**,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
display_progress_va(vlc_dialog_provider *p_provider, vlc_dialog_id **pp_id,
                    bool b_indeterminate, float f_position,
                    const char *psz_cancel, const char *psz_title,
                    const char *psz_fmt, va_list ap)
{
    vlc_mutex_lock(&p_provider->lock);
    if (p_provider->cbs.pf_display_progress == NULL
     || p_provider->cbs.pf_update_progress == NULL
     || p_provider->cbs.pf_cancel == NULL)
    {
        vlc_mutex_unlock(&p_provider->lock);
        return VLC_EGENERIC;
    }

    char *psz_text;
    if (vasprintf(&psz_text, psz_fmt, ap) == -1)
    {
        vlc_mutex_unlock(&p_provider->lock);
        return VLC_ENOMEM;
    }

    vlc_dialog_id *p_id = dialog_add_locked(p_provider, VLC_DIALOG_PROGRESS);
    if (p_id == NULL)
    {
        free(psz_text);
        vlc_mutex_unlock(&p_provider->lock);
        return VLC_ENOMEM;
    }
    p_id->b_progress_indeterminate = b_indeterminate;
    p_id->psz_progress_text = psz_text;
    p_provider->cbs.pf_display_progress(p_provider->p_cbs_data, p_id, psz_title,
                                        psz_text, b_indeterminate, f_position,
                                        psz_cancel);
    vlc_mutex_unlock(&p_provider->lock);
    *pp_id = p_id;

    return VLC_SUCCESS;
}