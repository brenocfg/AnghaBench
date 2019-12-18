#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sd_id128_t ;
struct TYPE_8__ {scalar_t__* invocation_id_string; int /*<<< orphan*/  invocation_id; TYPE_1__* manager; } ;
typedef  TYPE_2__ Unit ;
struct TYPE_7__ {int /*<<< orphan*/  units_by_invocation_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  SD_ID128_NULL ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int hashmap_ensure_allocated (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int hashmap_put (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  hashmap_remove_value (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  id128_hash_ops ; 
 scalar_t__ sd_id128_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sd_id128_is_null (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_id128_to_string (int /*<<< orphan*/ ,scalar_t__*) ; 

int unit_set_invocation_id(Unit *u, sd_id128_t id) {
        int r;

        assert(u);

        /* Set the invocation ID for this unit. If we cannot, this will not roll back, but reset the whole thing. */

        if (sd_id128_equal(u->invocation_id, id))
                return 0;

        if (!sd_id128_is_null(u->invocation_id))
                (void) hashmap_remove_value(u->manager->units_by_invocation_id, &u->invocation_id, u);

        if (sd_id128_is_null(id)) {
                r = 0;
                goto reset;
        }

        r = hashmap_ensure_allocated(&u->manager->units_by_invocation_id, &id128_hash_ops);
        if (r < 0)
                goto reset;

        u->invocation_id = id;
        sd_id128_to_string(id, u->invocation_id_string);

        r = hashmap_put(u->manager->units_by_invocation_id, &u->invocation_id, u);
        if (r < 0)
                goto reset;

        return 0;

reset:
        u->invocation_id = SD_ID128_NULL;
        u->invocation_id_string[0] = 0;
        return r;
}