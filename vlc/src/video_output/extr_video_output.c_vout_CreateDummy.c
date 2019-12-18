#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* p; } ;
typedef  TYPE_1__ vout_thread_t ;
struct TYPE_6__ {int dummy; } ;
typedef  TYPE_2__ vout_thread_sys_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;

/* Variables and functions */
 TYPE_1__* vout_CreateCommon (int /*<<< orphan*/ *) ; 

vout_thread_t *vout_CreateDummy(vlc_object_t *object)
{
    vout_thread_t *vout = vout_CreateCommon(object);
    if (!vout)
        return NULL;

    vout_thread_sys_t *sys = vout->p;
    sys->dummy = true;
    return vout;
}