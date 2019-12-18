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
typedef  TYPE_1__ intf_thread_t ;
struct TYPE_6__ {scalar_t__ last_state; } ;
typedef  TYPE_2__ intf_sys_t ;

/* Variables and functions */
 scalar_t__ VLC_PLAYER_STATE_PAUSED ; 
 scalar_t__ VLC_PLAYER_STATE_PLAYING ; 
 int /*<<< orphan*/  msg_print (TYPE_1__*,char*,int) ; 

__attribute__((used)) static void IsPlaying(intf_thread_t *intf)
{
    intf_sys_t *sys = intf->p_sys;

    msg_print(intf, "%d",
              sys->last_state == VLC_PLAYER_STATE_PLAYING ||
              sys->last_state == VLC_PLAYER_STATE_PAUSED);
}