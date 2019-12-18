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
struct TYPE_3__ {int /*<<< orphan*/  poll; int /*<<< orphan*/  client; } ;
typedef  TYPE_1__ discovery_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  avahi_client_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avahi_threaded_poll_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avahi_threaded_poll_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void CloseCommon( discovery_sys_t *p_sys )
{
    avahi_threaded_poll_stop( p_sys->poll );

    avahi_client_free( p_sys->client );
    avahi_threaded_poll_free( p_sys->poll );

}