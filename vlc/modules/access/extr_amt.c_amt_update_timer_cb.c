#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ stream_t ;
struct TYPE_5__ {int /*<<< orphan*/  qqic; } ;
struct TYPE_7__ {TYPE_1__ relay_igmp_query; int /*<<< orphan*/  updateTimer; int /*<<< orphan*/  relayDisco; } ;
typedef  TYPE_3__ access_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_TICK_FROM_SEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amt_send_mem_update (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vlc_timer_schedule (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void amt_update_timer_cb( void *data )
{
    stream_t     *p_access = (stream_t*) data;
    access_sys_t *sys = p_access->p_sys;

    amt_send_mem_update( p_access, sys->relayDisco, false );

    /* Arms the timer again for a single shot from this callback. That way, the
     * time spent in amt_send_mem_update() is taken into consideration. */
    vlc_timer_schedule( sys->updateTimer, false,
                        VLC_TICK_FROM_SEC( sys->relay_igmp_query.qqic ), 0 );
}