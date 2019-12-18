#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_11__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ stream_t ;
struct TYPE_9__ {int b_done; } ;
struct TYPE_10__ {TYPE_1__ seek; } ;
struct TYPE_12__ {int b_eof; int /*<<< orphan*/  p_nfsfh; int /*<<< orphan*/  p_nfs; TYPE_2__ res; } ;
typedef  TYPE_4__ access_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  msg_Err (TYPE_3__*,char*) ; 
 scalar_t__ nfs_lseek_async (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  nfs_seek_cb ; 
 int /*<<< orphan*/  nfs_seek_finished_cb ; 
 scalar_t__ vlc_nfs_mainloop (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
FileSeek(stream_t *p_access, uint64_t i_pos)
{
    access_sys_t *p_sys = p_access->p_sys;

    p_sys->res.seek.b_done = false;
    if (nfs_lseek_async(p_sys->p_nfs, p_sys->p_nfsfh, i_pos, SEEK_SET,
                        nfs_seek_cb, p_access) < 0)
    {
        msg_Err(p_access, "nfs_seek_async failed");
        return VLC_EGENERIC;
    }

    if (vlc_nfs_mainloop(p_access, nfs_seek_finished_cb) < 0)
        return VLC_EGENERIC;

    p_sys->b_eof = false;

    return VLC_SUCCESS;
}