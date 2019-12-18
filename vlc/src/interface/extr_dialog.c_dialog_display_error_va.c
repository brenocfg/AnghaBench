#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* pf_display_error ) (int /*<<< orphan*/ ,char const*,char*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  p_cbs_data; TYPE_1__ cbs; } ;
typedef  TYPE_2__ vlc_dialog_provider ;
typedef  int /*<<< orphan*/  va_list ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char const*,char*) ; 
 int vasprintf (char**,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dialog_display_error_va(vlc_dialog_provider *p_provider, const char *psz_title,
                        const char *psz_fmt, va_list ap)
{
    vlc_mutex_lock(&p_provider->lock);
    if (p_provider->cbs.pf_display_error == NULL)
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

    p_provider->cbs.pf_display_error(p_provider->p_cbs_data, psz_title, psz_text);
    free(psz_text);
    vlc_mutex_unlock(&p_provider->lock);

    return VLC_SUCCESS;
}