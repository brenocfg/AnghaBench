#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlListPtr ;
typedef  TYPE_2__* xmlLinkPtr ;
struct TYPE_5__ {struct TYPE_5__* prev; struct TYPE_5__* next; } ;
struct TYPE_4__ {TYPE_2__* sentinel; } ;

/* Variables and functions */

void
xmlListReverse(xmlListPtr l)
{
    xmlLinkPtr lk;
    xmlLinkPtr lkPrev;

    if (l == NULL)
        return;
    lkPrev = l->sentinel;
    for (lk = l->sentinel->next; lk != l->sentinel; lk = lk->next) {
        lkPrev->next = lkPrev->prev;
        lkPrev->prev = lk;
        lkPrev = lk;
    }
    /* Fix up the last node */
    lkPrev->next = lkPrev->prev;
    lkPrev->prev = lk;
}