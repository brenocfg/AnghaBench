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
struct TYPE_8__ {int /*<<< orphan*/  storage_socket; int /*<<< orphan*/  name; TYPE_1__* manager; } ;
struct TYPE_7__ {int /*<<< orphan*/  dynamic_users; } ;
typedef  TYPE_2__ DynamicUser ;

/* Variables and functions */
 int /*<<< orphan*/  hashmap_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* mfree (TYPE_2__*) ; 
 int /*<<< orphan*/  safe_close_pair (int /*<<< orphan*/ ) ; 

__attribute__((used)) static DynamicUser* dynamic_user_free(DynamicUser *d) {
        if (!d)
                return NULL;

        if (d->manager)
                (void) hashmap_remove(d->manager->dynamic_users, d->name);

        safe_close_pair(d->storage_socket);
        return mfree(d);
}