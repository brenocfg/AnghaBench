#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  poll; int /*<<< orphan*/  parent; } ;
typedef  TYPE_1__ discovery_sys_t ;
typedef  scalar_t__ AvahiClientState ;
typedef  int /*<<< orphan*/  AvahiClient ;

/* Variables and functions */
 scalar_t__ AVAHI_CLIENT_FAILURE ; 
 scalar_t__ AVAHI_ERR_DISCONNECTED ; 
 scalar_t__ avahi_client_errno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avahi_threaded_poll_quit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void client_callback( AvahiClient *c, AvahiClientState state,
                             void * userdata )
{
    discovery_sys_t *p_sys = userdata;

    if( state == AVAHI_CLIENT_FAILURE &&
        (avahi_client_errno(c) == AVAHI_ERR_DISCONNECTED) )
    {
        msg_Err( p_sys->parent, "avahi client disconnected" );
        avahi_threaded_poll_quit( p_sys->poll );
    }
}