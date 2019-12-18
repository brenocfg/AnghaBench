#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_1__* manager; } ;
struct TYPE_14__ {scalar_t__ devnode; } ;
struct TYPE_13__ {int /*<<< orphan*/ * swaps_by_devnode; } ;
typedef  TYPE_2__ Swap ;
typedef  int /*<<< orphan*/  Hashmap ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  LIST_PREPEND (int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*) ; 
 TYPE_7__* UNIT (TYPE_2__*) ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int hashmap_ensure_allocated (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 TYPE_2__* hashmap_get (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  hashmap_remove (int /*<<< orphan*/ *,scalar_t__) ; 
 int hashmap_replace (int /*<<< orphan*/ *,scalar_t__,TYPE_2__*) ; 
 scalar_t__ mfree (scalar_t__) ; 
 int /*<<< orphan*/  path_hash_ops ; 
 int /*<<< orphan*/  same_devnode ; 
 scalar_t__ strdup (char const*) ; 

__attribute__((used)) static int swap_set_devnode(Swap *s, const char *devnode) {
        Hashmap *swaps;
        Swap *first;
        int r;

        assert(s);

        r = hashmap_ensure_allocated(&UNIT(s)->manager->swaps_by_devnode, &path_hash_ops);
        if (r < 0)
                return r;

        swaps = UNIT(s)->manager->swaps_by_devnode;

        if (s->devnode) {
                first = hashmap_get(swaps, s->devnode);

                LIST_REMOVE(same_devnode, first, s);
                if (first)
                        hashmap_replace(swaps, first->devnode, first);
                else
                        hashmap_remove(swaps, s->devnode);

                s->devnode = mfree(s->devnode);
        }

        if (devnode) {
                s->devnode = strdup(devnode);
                if (!s->devnode)
                        return -ENOMEM;

                first = hashmap_get(swaps, s->devnode);
                LIST_PREPEND(same_devnode, first, s);

                return hashmap_replace(swaps, first->devnode, first);
        }

        return 0;
}