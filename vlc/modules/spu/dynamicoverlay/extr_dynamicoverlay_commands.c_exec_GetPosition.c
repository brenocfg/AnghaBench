#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  i_y; int /*<<< orphan*/  i_x; } ;
typedef  TYPE_1__ overlay_t ;
struct TYPE_10__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ filter_t ;
struct TYPE_11__ {int /*<<< orphan*/  overlays; } ;
typedef  TYPE_3__ filter_sys_t ;
struct TYPE_12__ {int /*<<< orphan*/  i_y; int /*<<< orphan*/  i_x; int /*<<< orphan*/  i_id; } ;
typedef  TYPE_4__ commandparams_t ;

/* Variables and functions */
 TYPE_1__* ListGet (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 

__attribute__((used)) static int exec_GetPosition( filter_t *p_filter,
                             const commandparams_t *p_params,
                             commandparams_t *p_results )
{
    filter_sys_t *p_sys = p_filter->p_sys;
    overlay_t *p_ovl = ListGet( &p_sys->overlays, p_params->i_id );
    if( p_ovl == NULL )
        return VLC_EGENERIC;

    p_results->i_x = p_ovl->i_x;
    p_results->i_y = p_ovl->i_y;
    return VLC_SUCCESS;
}