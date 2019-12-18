#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ i_schedule; int /*<<< orphan*/ * schedule; } ;
typedef  TYPE_1__ vlm_t ;

/* Variables and functions */
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  vlm_ScheduleDelete (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vlm_ControlScheduleClear( vlm_t *p_vlm )
{
    while( p_vlm->i_schedule > 0 )
        vlm_ScheduleDelete( p_vlm, p_vlm->schedule[0] );

    return VLC_SUCCESS;
}