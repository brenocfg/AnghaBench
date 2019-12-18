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
struct TYPE_6__ {int /*<<< orphan*/ * display_pool; scalar_t__ private_pool; } ;
typedef  TYPE_2__ vout_thread_sys_t ;
typedef  int /*<<< orphan*/  vout_display_t ;

/* Variables and functions */
 int /*<<< orphan*/  Forward ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  picture_pool_Release (scalar_t__) ; 
 int /*<<< orphan*/  var_DelCallback (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vout_display_Delete (int /*<<< orphan*/ *) ; 

void vout_CloseWrapper(vout_thread_t *vout, vout_display_t *vd)
{
    vout_thread_sys_t *sys = vout->p;

    assert(sys->display_pool && sys->private_pool);

    picture_pool_Release(sys->private_pool);
    sys->display_pool = NULL;

#ifdef _WIN32
    var_DelCallback(vout, "video-wallpaper", Forward, vd);
#endif

    vout_display_Delete(vd);
}