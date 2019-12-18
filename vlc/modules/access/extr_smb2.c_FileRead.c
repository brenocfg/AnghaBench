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
struct TYPE_8__ {int len; } ;
struct TYPE_9__ {TYPE_1__ read; } ;
struct access_sys {scalar_t__ error_status; TYPE_2__ res; int /*<<< orphan*/  smb2fh; int /*<<< orphan*/  smb2; scalar_t__ eof; } ;
struct TYPE_10__ {struct access_sys* p_sys; } ;
typedef  TYPE_3__ stream_t ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_SMB2_SET_ERROR (TYPE_3__*,char*,int) ; 
 scalar_t__ smb2_read_async (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  smb2_read_cb ; 
 scalar_t__ vlc_smb2_mainloop (TYPE_3__*,int) ; 

__attribute__((used)) static ssize_t
FileRead(stream_t *access, void *buf, size_t len)
{
    struct access_sys *sys = access->p_sys;

    if (sys->error_status != 0)
        return -1;

    if (sys->eof)
        return 0;

    sys->res.read.len = 0;
    if (smb2_read_async(sys->smb2, sys->smb2fh, buf, len,
                        smb2_read_cb, access) < 0)
    {
        VLC_SMB2_SET_ERROR(access, "smb2_read_async", 1);
        return -1;
    }

    if (vlc_smb2_mainloop(access, false) < 0)
        return -1;

    return sys->res.read.len;
}