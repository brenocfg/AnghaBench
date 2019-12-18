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
struct TYPE_3__ {scalar_t__ result; scalar_t__ deserialized_state; } ;
typedef  scalar_t__ PathState ;
typedef  scalar_t__ PathResult ;
typedef  TYPE_1__ Path ;
typedef  char const FDSet ;

/* Variables and functions */
 TYPE_1__* PATH (char const*) ; 
 scalar_t__ PATH_SUCCESS ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int /*<<< orphan*/  log_unit_debug (char const*,char*,char const*) ; 
 scalar_t__ path_result_from_string (char const*) ; 
 scalar_t__ path_state_from_string (char const*) ; 
 scalar_t__ streq (char const*,char*) ; 

__attribute__((used)) static int path_deserialize_item(Unit *u, const char *key, const char *value, FDSet *fds) {
        Path *p = PATH(u);

        assert(u);
        assert(key);
        assert(value);
        assert(fds);

        if (streq(key, "state")) {
                PathState state;

                state = path_state_from_string(value);
                if (state < 0)
                        log_unit_debug(u, "Failed to parse state value: %s", value);
                else
                        p->deserialized_state = state;

        } else if (streq(key, "result")) {
                PathResult f;

                f = path_result_from_string(value);
                if (f < 0)
                        log_unit_debug(u, "Failed to parse result value: %s", value);
                else if (f != PATH_SUCCESS)
                        p->result = f;

        } else
                log_unit_debug(u, "Unknown serialization key: %s", key);

        return 0;
}