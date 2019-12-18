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
typedef  TYPE_1__ DnsTxtItem ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

DnsTxtItem *dns_txt_item_free_all(DnsTxtItem *i) {
        DnsTxtItem *n;

        if (!i)
                return NULL;

        n = i->items_next;

        free(i);
        return dns_txt_item_free_all(n);
}