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
typedef  int /*<<< orphan*/ * node ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  int /*<<< orphan*/ * sd_bus ;
typedef  int /*<<< orphan*/  Set ;

/* Variables and functions */
 int ENOMEM ; 
 int add_subtree_to_set (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ **,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int /*<<< orphan*/  set_free_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * set_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_hash_ops ; 

__attribute__((used)) static int get_child_nodes(
                sd_bus *bus,
                const char *prefix,
                struct node *n,
                unsigned flags,
                Set **_s,
                sd_bus_error *error) {

        Set *s = NULL;
        int r;

        assert(bus);
        assert(prefix);
        assert(n);
        assert(_s);

        s = set_new(&string_hash_ops);
        if (!s)
                return -ENOMEM;

        r = add_subtree_to_set(bus, prefix, n, flags, s, error);
        if (r < 0) {
                set_free_free(s);
                return r;
        }

        *_s = s;
        return 0;
}