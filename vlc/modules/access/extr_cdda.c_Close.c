#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  vcddev_t ;
struct TYPE_2__ {int /*<<< orphan*/ * pf_readdir; void* p_sys; } ;
typedef  TYPE_1__ stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  AccessClose (void*) ; 
 int /*<<< orphan*/  access_sys_t ; 
 int /*<<< orphan*/  demux_sys_t ; 
 int /*<<< orphan*/  ioctl_Close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  static_assert (int,char*) ; 
 int /*<<< orphan*/  vcddev ; 

__attribute__((used)) static void Close(vlc_object_t *obj)
{
    stream_t *stream = (stream_t *)obj;
    void *sys = stream->p_sys;

    if (stream->pf_readdir != NULL)
        AccessClose(sys);

    static_assert(offsetof(demux_sys_t, vcddev) == 0, "Invalid cast");
    static_assert(offsetof(access_sys_t, vcddev) == 0, "Invalid cast");
    ioctl_Close(obj, *(vcddev_t **)sys);
}