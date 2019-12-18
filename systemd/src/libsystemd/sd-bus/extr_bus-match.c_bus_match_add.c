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
struct match_callback {int dummy; } ;
typedef  struct match_callback bus_match_node ;
struct bus_match_component {int /*<<< orphan*/  value_str; int /*<<< orphan*/  value_u8; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct match_callback*) ; 
 int bus_match_add_compare_value (struct match_callback*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct match_callback**) ; 
 int bus_match_add_leaf (struct match_callback*,struct match_callback*) ; 

int bus_match_add(
                struct bus_match_node *root,
                struct bus_match_component *components,
                unsigned n_components,
                struct match_callback *callback) {

        unsigned i;
        struct bus_match_node *n;
        int r;

        assert(root);
        assert(callback);

        n = root;
        for (i = 0; i < n_components; i++) {
                r = bus_match_add_compare_value(
                                n, components[i].type,
                                components[i].value_u8, components[i].value_str, &n);
                if (r < 0)
                        return r;
        }

        return bus_match_add_leaf(n, callback);
}