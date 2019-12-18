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
struct TYPE_3__ {scalar_t__ server_socket; scalar_t__ event_timer; scalar_t__ resolve_query; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */

__attribute__((used)) static bool manager_is_connected(Manager *m) {
        /* Return true when the manager is sending a request, resolving a server name, or
         * in a poll interval. */
        return m->server_socket >= 0 || m->resolve_query || m->event_timer;
}