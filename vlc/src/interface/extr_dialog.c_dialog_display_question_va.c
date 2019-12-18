#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_dialog_question_type ;
struct TYPE_5__ {int /*<<< orphan*/  (* pf_display_question ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,char*,int /*<<< orphan*/ ,char const*,char const*,char const*) ;int /*<<< orphan*/ * pf_cancel; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  p_cbs_data; TYPE_1__ cbs; } ;
typedef  TYPE_2__ vlc_dialog_provider ;
typedef  int /*<<< orphan*/  vlc_dialog_id ;
typedef  int /*<<< orphan*/  va_list ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_DIALOG_QUESTION ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/ * dialog_add_locked (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,char*,int /*<<< orphan*/ ,char const*,char const*,char const*) ; 
 int vasprintf (char**,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dialog_display_question_va(vlc_dialog_provider *p_provider, vlc_dialog_id **pp_id,
                           vlc_dialog_question_type i_type,
                           const char *psz_cancel, const char *psz_action1,
                           const char *psz_action2, const char *psz_title,
                           const char *psz_fmt, va_list ap)
{
    vlc_mutex_lock(&p_provider->lock);
    if (p_provider->cbs.pf_display_question == NULL
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

    vlc_dialog_id *p_id = dialog_add_locked(p_provider, VLC_DIALOG_QUESTION);
    if (p_id == NULL)
    {
        free(psz_text);
        vlc_mutex_unlock(&p_provider->lock);
        return VLC_ENOMEM;
    }
    p_provider->cbs.pf_display_question(p_provider->p_cbs_data, p_id, psz_title,
                                        psz_text, i_type, psz_cancel, psz_action1,
                                        psz_action2);
    free(psz_text);
    vlc_mutex_unlock(&p_provider->lock);
    *pp_id = p_id;

    return VLC_SUCCESS;
}