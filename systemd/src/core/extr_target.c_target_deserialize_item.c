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
typedef  char const Unit ;
typedef  scalar_t__ TargetState ;
struct TYPE_3__ {scalar_t__ deserialized_state; } ;
typedef  TYPE_1__ Target ;
typedef  char const FDSet ;

/* Variables and functions */
 TYPE_1__* TARGET (char const*) ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int /*<<< orphan*/  log_debug (char*,char const*) ; 
 scalar_t__ streq (char const*,char*) ; 
 scalar_t__ target_state_from_string (char const*) ; 

__attribute__((used)) static int target_deserialize_item(Unit *u, const char *key, const char *value, FDSet *fds) {
        Target *s = TARGET(u);

        assert(u);
        assert(key);
        assert(value);
        assert(fds);

        if (streq(key, "state")) {
                TargetState state;

                state = target_state_from_string(value);
                if (state < 0)
                        log_debug("Failed to parse state value %s", value);
                else
                        s->deserialized_state = state;

        } else
                log_debug("Unknown serialization key '%s'", key);

        return 0;
}