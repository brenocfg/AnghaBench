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
typedef  TYPE_1__ filter_t ;
struct TYPE_5__ {int b_atomic; } ;
typedef  TYPE_2__ filter_sys_t ;
typedef  int /*<<< orphan*/  const commandparams_t ;

/* Variables and functions */
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int exec_StartAtomic( filter_t *p_filter,
                             const commandparams_t *p_params,
                             commandparams_t *p_results )
{
    filter_sys_t *p_sys = p_filter->p_sys;
    VLC_UNUSED(p_params);
    VLC_UNUSED(p_results);

    p_sys->b_atomic = true;
    return VLC_SUCCESS;
}