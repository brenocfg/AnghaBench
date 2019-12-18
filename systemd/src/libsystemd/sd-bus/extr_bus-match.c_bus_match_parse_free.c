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
struct bus_match_component {struct bus_match_component* value_str; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct bus_match_component*) ; 

void bus_match_parse_free(struct bus_match_component *components, unsigned n_components) {
        unsigned i;

        for (i = 0; i < n_components; i++)
                free(components[i].value_str);

        free(components);
}