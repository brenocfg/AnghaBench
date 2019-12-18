#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  const sd_bus ;
typedef  int /*<<< orphan*/  UnitInfo ;

/* Variables and functions */
 int /*<<< orphan*/  DEP_ALL ; 
 int /*<<< orphan*/  DEP_ORDER ; 
 int /*<<< orphan*/  DEP_REQUIRE ; 
 scalar_t__ IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arg_dot ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/  const*) ; 
 int graph_one_property (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,char*,char*,char**,char**,char**) ; 

__attribute__((used)) static int graph_one(sd_bus *bus, const UnitInfo *u, char *patterns[], char *from_patterns[], char *to_patterns[]) {
        int r;

        assert(bus);
        assert(u);

        if (IN_SET(arg_dot, DEP_ORDER, DEP_ALL)) {
                r = graph_one_property(bus, u, "After", "green", patterns, from_patterns, to_patterns);
                if (r < 0)
                        return r;
        }

        if (IN_SET(arg_dot, DEP_REQUIRE, DEP_ALL)) {
                r = graph_one_property(bus, u, "Requires", "black", patterns, from_patterns, to_patterns);
                if (r < 0)
                        return r;
                r = graph_one_property(bus, u, "Requisite", "darkblue", patterns, from_patterns, to_patterns);
                if (r < 0)
                        return r;
                r = graph_one_property(bus, u, "Wants", "grey66", patterns, from_patterns, to_patterns);
                if (r < 0)
                        return r;
                r = graph_one_property(bus, u, "Conflicts", "red", patterns, from_patterns, to_patterns);
                if (r < 0)
                        return r;
        }

        return 0;
}