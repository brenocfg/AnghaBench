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
struct TYPE_11__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ stream_t ;
typedef  int ssize_t ;
struct TYPE_10__ {int i_len; void* p_buf; } ;
struct TYPE_9__ {TYPE_2__ read; } ;
struct TYPE_12__ {TYPE_1__ res; int /*<<< orphan*/  p_nfsfh; int /*<<< orphan*/  p_nfs; scalar_t__ b_eof; } ;
typedef  TYPE_4__ access_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  msg_Err (TYPE_3__*,char*) ; 
 scalar_t__ nfs_read_async (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  nfs_read_cb ; 
 int /*<<< orphan*/  nfs_read_finished_cb ; 
 scalar_t__ vlc_nfs_mainloop (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
FileRead(stream_t *p_access, void *p_buf, size_t i_len)
{
    access_sys_t *p_sys = p_access->p_sys;

    if (p_sys->b_eof)
        return 0;

    p_sys->res.read.i_len = 0;
    p_sys->res.read.p_buf = p_buf;
    if (nfs_read_async(p_sys->p_nfs, p_sys->p_nfsfh, i_len, nfs_read_cb,
                       p_access) < 0)
    {
        msg_Err(p_access, "nfs_read_async failed");
        return -1;
    }

    if (vlc_nfs_mainloop(p_access, nfs_read_finished_cb) < 0)
        return -1;

    return p_sys->res.read.i_len;
}