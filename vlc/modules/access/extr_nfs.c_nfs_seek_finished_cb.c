#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ stream_t ;
struct TYPE_6__ {int b_done; } ;
struct TYPE_7__ {TYPE_1__ seek; } ;
struct TYPE_9__ {TYPE_2__ res; } ;
typedef  TYPE_4__ access_sys_t ;

/* Variables and functions */

__attribute__((used)) static bool
nfs_seek_finished_cb(stream_t *p_access)
{
    access_sys_t *p_sys = p_access->p_sys;
    return p_sys->res.seek.b_done;
}