#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  vlc_dialog_provider ;
typedef  int /*<<< orphan*/  va_list ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int /*<<< orphan*/  VLC_MSG_ERR ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int dialog_display_error_va (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_dialog_provider (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  msg_GenericVa (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

int
vlc_dialog_display_error_va(vlc_object_t *p_obj, const char *psz_title,
                            const char *psz_fmt, va_list ap)
{
    assert(p_obj != NULL && psz_title != NULL && psz_fmt != NULL);
    int i_ret;
    vlc_dialog_provider *p_provider = get_dialog_provider(p_obj, true);

    if (p_provider != NULL)
        i_ret = dialog_display_error_va(p_provider, psz_title, psz_fmt, ap);
    else
        i_ret = VLC_EGENERIC;

    if (i_ret != VLC_SUCCESS)
    {
        msg_Err(p_obj, "%s", psz_title);
        msg_GenericVa(p_obj, VLC_MSG_ERR, psz_fmt, ap);
    }
    return i_ret;
}