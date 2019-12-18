#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ type; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ Unit ;
struct TYPE_13__ {scalar_t__ load_state; int /*<<< orphan*/  id; } ;
struct TYPE_12__ {int /*<<< orphan*/  service; } ;
typedef  int /*<<< orphan*/  Service ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/ * SERVICE (int /*<<< orphan*/ ) ; 
 TYPE_3__* SOCKET (TYPE_1__*) ; 
 TYPE_8__* UNIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UNIT_DEREF (int /*<<< orphan*/ ) ; 
 scalar_t__ UNIT_ISSET (int /*<<< orphan*/ ) ; 
 scalar_t__ UNIT_LOADED ; 
 scalar_t__ UNIT_SOCKET ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  log_unit_debug (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_unit_error (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int log_unit_error_errno (TYPE_1__*,int,char*) ; 
 int socket_instantiate_service (TYPE_3__*) ; 

__attribute__((used)) static int verify_socket(Unit *u) {
        int r;

        assert(u);

        if (u->type != UNIT_SOCKET)
                return 0;

        /* Cannot run this without the service being around */

        /* This makes sure instance is created if necessary. */
        r = socket_instantiate_service(SOCKET(u));
        if (r < 0)
                return log_unit_error_errno(u, r, "Socket cannot be started, failed to create instance: %m");

        /* This checks both type of sockets */
        if (UNIT_ISSET(SOCKET(u)->service)) {
                Service *service;

                service = SERVICE(UNIT_DEREF(SOCKET(u)->service));
                log_unit_debug(u, "Using %s", UNIT(service)->id);

                if (UNIT(service)->load_state != UNIT_LOADED) {
                        log_unit_error(u, "Service %s not loaded, %s cannot be started.", UNIT(service)->id, u->id);
                        return -ENOENT;
                }
        }

        return 0;
}