#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* current_server_name; int /*<<< orphan*/  fallback_servers; int /*<<< orphan*/  link_servers; int /*<<< orphan*/  system_servers; } ;
struct TYPE_9__ {scalar_t__ type; int /*<<< orphan*/  string; TYPE_7__* manager; } ;
typedef  TYPE_1__ ServerName ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ SERVER_FALLBACK ; 
 scalar_t__ SERVER_LINK ; 
 scalar_t__ SERVER_SYSTEM ; 
 int /*<<< orphan*/  assert_not_reached (char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  manager_set_server_name (TYPE_7__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* mfree (TYPE_1__*) ; 
 int /*<<< orphan*/  names ; 
 int /*<<< orphan*/  server_name_flush_addresses (TYPE_1__*) ; 

ServerName *server_name_free(ServerName *n) {
        if (!n)
                return NULL;

        server_name_flush_addresses(n);

        if (n->manager) {
                if (n->type == SERVER_SYSTEM)
                        LIST_REMOVE(names, n->manager->system_servers, n);
                else if (n->type == SERVER_LINK)
                        LIST_REMOVE(names, n->manager->link_servers, n);
                else if (n->type == SERVER_FALLBACK)
                        LIST_REMOVE(names, n->manager->fallback_servers, n);
                else
                        assert_not_reached("Unknown server type");

                if (n->manager->current_server_name == n)
                        manager_set_server_name(n->manager, NULL);
        }

        log_debug("Removed server %s.", n->string);

        free(n->string);
        return mfree(n);
}