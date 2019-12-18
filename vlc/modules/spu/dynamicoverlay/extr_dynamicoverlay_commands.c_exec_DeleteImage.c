#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ filter_t ;
struct TYPE_9__ {int b_updated; int /*<<< orphan*/  overlays; } ;
typedef  TYPE_2__ filter_sys_t ;
struct TYPE_10__ {int /*<<< orphan*/  i_id; } ;
typedef  TYPE_3__ commandparams_t ;

/* Variables and functions */
 int ListRemove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLC_UNUSED (TYPE_3__*) ; 

__attribute__((used)) static int exec_DeleteImage( filter_t *p_filter,
                             const commandparams_t *p_params,
                             commandparams_t *p_results )
{
    VLC_UNUSED(p_results);
    filter_sys_t *p_sys = p_filter->p_sys;
    p_sys->b_updated = true;

    return ListRemove( &p_sys->overlays, p_params->i_id );
}