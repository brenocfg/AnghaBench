#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct access_sys {int /*<<< orphan*/  encoded_url; int /*<<< orphan*/  smb2; int /*<<< orphan*/ * share_enum; int /*<<< orphan*/ * smb2dir; int /*<<< orphan*/ * smb2fh; } ;
struct TYPE_4__ {struct access_sys* p_sys; } ;
typedef  TYPE_1__ stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  smb2_closedir (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smb2_destroy_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smb2_free_data (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_UrlClean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 
 int /*<<< orphan*/  vlc_smb2_close_fh (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_smb2_disconnect_share (TYPE_1__*) ; 

__attribute__((used)) static void
Close(vlc_object_t *p_obj)
{
    stream_t *access = (stream_t *)p_obj;
    struct access_sys *sys = access->p_sys;

    if (sys->smb2fh != NULL)
        vlc_smb2_close_fh(access);
    else if (sys->smb2dir != NULL)
        smb2_closedir(sys->smb2, sys->smb2dir);
    else if (sys->share_enum != NULL)
        smb2_free_data(sys->smb2, sys->share_enum);
    else
        vlc_assert_unreachable();

    vlc_smb2_disconnect_share(access);
    smb2_destroy_context(sys->smb2);

    vlc_UrlClean(&sys->encoded_url);
}