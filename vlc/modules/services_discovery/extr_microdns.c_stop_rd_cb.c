#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct discovery_sys* p_sys; } ;
typedef  TYPE_1__ vlc_renderer_discovery_t ;
struct discovery_sys {int /*<<< orphan*/  stop; } ;

/* Variables and functions */
 scalar_t__ atomic_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  items_timeout (struct discovery_sys*,int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static bool
stop_rd_cb( void *p_this )
{
    vlc_renderer_discovery_t *p_rd = p_this;
    struct discovery_sys *p_sys = p_rd->p_sys;

    if( atomic_load( &p_sys->stop ) )
        return true;
    else
    {
        items_timeout( p_sys, NULL, p_rd );
        return false;
    }
}