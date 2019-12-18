#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  vlc_dialog_provider ;
typedef  int /*<<< orphan*/  vlc_dialog_id ;
typedef  int /*<<< orphan*/  va_list ;
struct TYPE_3__ {char* psz_username; char* psz_password; int b_store; } ;
struct TYPE_4__ {TYPE_1__ login; } ;
struct dialog_answer {TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_DIALOG_LOGIN ; 
 int VLC_EGENERIC ; 
 int /*<<< orphan*/  assert (int) ; 
 int dialog_display_login_va (int /*<<< orphan*/ *,int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ) ; 
 int dialog_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct dialog_answer*) ; 
 int /*<<< orphan*/ * get_dialog_provider (int /*<<< orphan*/ *,int) ; 

int
vlc_dialog_wait_login_va(vlc_object_t *p_obj,  char **ppsz_username,
                         char **ppsz_password, bool *p_store,
                         const char *psz_default_username,
                         const char *psz_title, const char *psz_fmt, va_list ap)
{
    assert(p_obj != NULL && ppsz_username != NULL && ppsz_password != NULL
        && psz_fmt != NULL && psz_title != NULL);

    vlc_dialog_provider *p_provider = get_dialog_provider(p_obj, true);
    if (p_provider == NULL)
        return VLC_EGENERIC;

    vlc_dialog_id *p_id;
    int i_ret = dialog_display_login_va(p_provider, &p_id, psz_default_username,
                                        p_store != NULL, psz_title, psz_fmt, ap);
    if (i_ret < 0 || p_id == NULL)
        return i_ret;

    struct dialog_answer answer;
    i_ret = dialog_wait(p_provider, p_id, VLC_DIALOG_LOGIN, &answer);
    if (i_ret <= 0)
        return i_ret;

    *ppsz_username = answer.u.login.psz_username;
    *ppsz_password = answer.u.login.psz_password;
    if (p_store != NULL)
        *p_store = answer.u.login.b_store;

    return 1;
}