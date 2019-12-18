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
struct TYPE_5__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ intf_thread_t ;
struct TYPE_6__ {int i_map; int /*<<< orphan*/  root; int /*<<< orphan*/  p_connection; TYPE_3__* p_map; } ;
typedef  TYPE_2__ intf_sys_t ;
struct TYPE_7__ {scalar_t__* p_keys; int /*<<< orphan*/  i_modifier; } ;
typedef  TYPE_3__ hotkey_mapping_t ;

/* Variables and functions */
 int /*<<< orphan*/  XCB_GRAB_MODE_ASYNC ; 
 scalar_t__ XCB_NO_SYMBOL ; 
 int /*<<< orphan*/  xcb_grab_key (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Register( intf_thread_t *p_intf )
{
    intf_sys_t *p_sys = p_intf->p_sys;

    for( int i = 0; i < p_sys->i_map; i++ )
    {
        const hotkey_mapping_t *p_map = &p_sys->p_map[i];
        for( int j = 0; p_map->p_keys[j] != XCB_NO_SYMBOL; j++ )
        {
            xcb_grab_key( p_sys->p_connection, true, p_sys->root,
                          p_map->i_modifier, p_map->p_keys[j],
                          XCB_GRAB_MODE_ASYNC, XCB_GRAB_MODE_ASYNC );
        }
    }
}