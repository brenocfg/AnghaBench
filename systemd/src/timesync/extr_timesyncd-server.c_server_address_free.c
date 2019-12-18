#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_2__* current_server_address; } ;
struct TYPE_10__ {TYPE_1__* name; } ;
struct TYPE_9__ {TYPE_7__* manager; int /*<<< orphan*/  addresses; } ;
typedef  TYPE_2__ ServerAddress ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  addresses ; 
 int /*<<< orphan*/  manager_set_server_address (TYPE_7__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* mfree (TYPE_2__*) ; 

ServerAddress* server_address_free(ServerAddress *a) {
        if (!a)
                return NULL;

        if (a->name) {
                LIST_REMOVE(addresses, a->name->addresses, a);

                if (a->name->manager && a->name->manager->current_server_address == a)
                        manager_set_server_address(a->name->manager, NULL);
        }

        return mfree(a);
}