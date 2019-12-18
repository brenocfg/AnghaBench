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
struct TYPE_3__ {TYPE_2__* p_sys; int /*<<< orphan*/ * pf_read; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_4__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_2__ access_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  DirClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_close (int /*<<< orphan*/ ) ; 

void FileClose (vlc_object_t * p_this)
{
    stream_t     *p_access = (stream_t*)p_this;

    if (p_access->pf_read == NULL)
    {
        DirClose (p_this);
        return;
    }

    access_sys_t *p_sys = p_access->p_sys;

    vlc_close (p_sys->fd);
}