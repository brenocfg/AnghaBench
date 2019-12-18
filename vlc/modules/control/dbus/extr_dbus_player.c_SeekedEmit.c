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
struct TYPE_6__ {TYPE_1__* p_sys; } ;
typedef  TYPE_2__ intf_thread_t ;
struct TYPE_5__ {int /*<<< orphan*/  p_conn; scalar_t__ b_dead; } ;

/* Variables and functions */
 int /*<<< orphan*/  SeekedSignal (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int VLC_SUCCESS ; 

int SeekedEmit( intf_thread_t * p_intf )
{
    if( p_intf->p_sys->b_dead )
        return VLC_SUCCESS;

    SeekedSignal( p_intf->p_sys->p_conn, p_intf );
    return VLC_SUCCESS;
}