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
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_5__ {int /*<<< orphan*/ * psz_url_decoded_slash; int /*<<< orphan*/ * p_nfsdir; int /*<<< orphan*/ * p_nfsfh; } ;
typedef  TYPE_2__ access_sys_t ;

/* Variables and functions */

__attribute__((used)) static bool
nfs_mount_open_finished_cb(stream_t *p_access)
{
    access_sys_t *p_sys = p_access->p_sys;
    return p_sys->p_nfsfh != NULL || p_sys->p_nfsdir != NULL
        || p_sys->psz_url_decoded_slash != NULL;
}