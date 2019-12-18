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
struct bus_match_component {int dummy; } ;
typedef  enum bus_match_scope { ____Placeholder_bus_match_scope } bus_match_scope ;

/* Variables and functions */
 int /*<<< orphan*/  assert_se (int) ; 
 int bus_match_get_scope (struct bus_match_component*,unsigned int) ; 
 scalar_t__ bus_match_parse (char const*,struct bus_match_component**,unsigned int*) ; 
 int /*<<< orphan*/  bus_match_parse_free (struct bus_match_component*,unsigned int) ; 

__attribute__((used)) static void test_match_scope(const char *match, enum bus_match_scope scope) {
        struct bus_match_component *components = NULL;
        unsigned n_components = 0;

        assert_se(bus_match_parse(match, &components, &n_components) >= 0);
        assert_se(bus_match_get_scope(components, n_components) == scope);
        bus_match_parse_free(components, n_components);
}