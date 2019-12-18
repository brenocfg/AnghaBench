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
struct track_item {int /*<<< orphan*/  name; int /*<<< orphan*/  slot; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 struct track_item* mfree (struct track_item*) ; 
 int /*<<< orphan*/  sd_bus_slot_unref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct track_item* track_item_free(struct track_item *i) {

        if (!i)
                return NULL;

        sd_bus_slot_unref(i->slot);
        free(i->name);
        return mfree(i);
}