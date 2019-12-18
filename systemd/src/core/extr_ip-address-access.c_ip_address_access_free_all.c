#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* items_next; } ;
typedef  TYPE_1__ IPAddressAccessItem ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

IPAddressAccessItem* ip_address_access_free_all(IPAddressAccessItem *first) {
        IPAddressAccessItem *next, *p = first;

        while (p) {
                next = p->items_next;
                free(p);

                p = next;
        }

        return NULL;
}