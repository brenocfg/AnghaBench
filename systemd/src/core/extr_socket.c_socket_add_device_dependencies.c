#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  bind_to_device; } ;
typedef  TYPE_1__ Socket ;

/* Variables and functions */
 int /*<<< orphan*/  UNIT (TYPE_1__*) ; 
 int /*<<< orphan*/  UNIT_BINDS_TO ; 
 int /*<<< orphan*/  UNIT_DEPENDENCY_FILE ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 scalar_t__ streq (int /*<<< orphan*/ ,char*) ; 
 char* strjoina (char*,int /*<<< orphan*/ ) ; 
 int unit_add_node_dependency (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int socket_add_device_dependencies(Socket *s) {
        char *t;

        assert(s);

        if (!s->bind_to_device || streq(s->bind_to_device, "lo"))
                return 0;

        t = strjoina("/sys/subsystem/net/devices/", s->bind_to_device);
        return unit_add_node_dependency(UNIT(s), t, UNIT_BINDS_TO, UNIT_DEPENDENCY_FILE);
}