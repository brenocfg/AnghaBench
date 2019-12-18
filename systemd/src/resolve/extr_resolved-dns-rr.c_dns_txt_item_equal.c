#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ length; struct TYPE_4__* items_next; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ DnsTxtItem ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

bool dns_txt_item_equal(DnsTxtItem *a, DnsTxtItem *b) {

        if (a == b)
                return true;

        if (!a != !b)
                return false;

        if (!a)
                return true;

        if (a->length != b->length)
                return false;

        if (memcmp(a->data, b->data, a->length) != 0)
                return false;

        return dns_txt_item_equal(a->items_next, b->items_next);
}