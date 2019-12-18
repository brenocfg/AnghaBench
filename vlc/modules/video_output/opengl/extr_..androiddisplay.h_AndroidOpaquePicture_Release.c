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
struct TYPE_4__ {int i_index; int /*<<< orphan*/  lock; scalar_t__ p_dec; int /*<<< orphan*/  (* pf_release ) (scalar_t__,unsigned int,int) ;} ;
struct TYPE_5__ {int b_locked; TYPE_1__ hw; } ;
typedef  TYPE_2__ picture_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,unsigned int,int) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
AndroidOpaquePicture_Release(picture_sys_t *p_picsys, bool b_render)
{
    if (!p_picsys->b_locked)
        return;
    vlc_mutex_lock(&p_picsys->hw.lock);
    if (p_picsys->hw.i_index >= 0)
    {
        assert(p_picsys->hw.pf_release && p_picsys->hw.p_dec);
        p_picsys->hw.pf_release(p_picsys->hw.p_dec,
                                (unsigned int) p_picsys->hw.i_index,
                                b_render);
        p_picsys->hw.i_index = -1;
    }
    vlc_mutex_unlock(&p_picsys->hw.lock);
    p_picsys->b_locked = false;
}