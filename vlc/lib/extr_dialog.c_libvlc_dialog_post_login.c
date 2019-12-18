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
typedef  int /*<<< orphan*/  vlc_dialog_id ;
typedef  int /*<<< orphan*/  libvlc_dialog_id ;

/* Variables and functions */
 int VLC_SUCCESS ; 
 int vlc_dialog_id_post_login (int /*<<< orphan*/ *,char const*,char const*,int) ; 

int
libvlc_dialog_post_login(libvlc_dialog_id *p_id, const char *psz_username,
                         const char *psz_password, bool b_store)
{
    int i_ret = vlc_dialog_id_post_login((vlc_dialog_id *)p_id, psz_username,
                                         psz_password, b_store);
    return i_ret == VLC_SUCCESS ? 0 : -1;
}