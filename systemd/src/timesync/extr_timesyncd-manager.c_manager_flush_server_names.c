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
struct TYPE_4__ {scalar_t__ fallback_servers; scalar_t__ link_servers; scalar_t__ system_servers; } ;
typedef  scalar_t__ ServerType ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 scalar_t__ SERVER_FALLBACK ; 
 scalar_t__ SERVER_LINK ; 
 scalar_t__ SERVER_SYSTEM ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  server_name_free (scalar_t__) ; 

void manager_flush_server_names(Manager  *m, ServerType t) {
        assert(m);

        if (t == SERVER_SYSTEM)
                while (m->system_servers)
                        server_name_free(m->system_servers);

        if (t == SERVER_LINK)
                while (m->link_servers)
                        server_name_free(m->link_servers);

        if (t == SERVER_FALLBACK)
                while (m->fallback_servers)
                        server_name_free(m->fallback_servers);
}