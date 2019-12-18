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
struct TYPE_5__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ filter_t ;
struct TYPE_6__ {scalar_t__ i_last_olen; scalar_t__ last_soxr; } ;
typedef  TYPE_2__ filter_sys_t ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SoXR_Resample (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static block_t *
Drain( filter_t *p_filter )
{
    filter_sys_t *p_sys = p_filter->p_sys;

    if( p_sys->last_soxr && p_sys->i_last_olen )
        return SoXR_Resample( p_filter, p_sys->last_soxr, NULL,
                              p_sys->i_last_olen );
    else
        return NULL;
}