#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int b_enabled; int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {TYPE_1__ still; int /*<<< orphan*/  dvdnav; } ;
typedef  TYPE_2__ demux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  dvdnav_still_skip (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void StillTimer( void *p_data )
{
    demux_sys_t    *p_sys = p_data;

    vlc_mutex_lock( &p_sys->still.lock );
    if( likely(p_sys->still.b_enabled) )
    {
        p_sys->still.b_enabled = false;
        dvdnav_still_skip( p_sys->dvdnav );
    }
    vlc_mutex_unlock( &p_sys->still.lock );
}