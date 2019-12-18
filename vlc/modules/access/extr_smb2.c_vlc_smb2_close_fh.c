#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct access_sys {int /*<<< orphan*/ * smb2fh; int /*<<< orphan*/  smb2; } ;
struct TYPE_6__ {struct access_sys* p_sys; } ;
typedef  TYPE_1__ stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_SMB2_SET_ERROR (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 scalar_t__ smb2_close_async (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  smb2_generic_cb ; 
 int vlc_smb2_mainloop (TYPE_1__*,int) ; 

__attribute__((used)) static int
vlc_smb2_close_fh(stream_t *access)
{
    struct access_sys *sys = access->p_sys;

    assert(sys->smb2fh);

    if (smb2_close_async(sys->smb2, sys->smb2fh, smb2_generic_cb, access) < 0)
    {
        VLC_SMB2_SET_ERROR(access, "smb2_close_async", 1);
        return -1;
    }

    sys->smb2fh = NULL;

    return vlc_smb2_mainloop(access, true);
}