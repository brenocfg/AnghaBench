#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlListPtr ;
typedef  TYPE_2__* xmlLinkPtr ;
struct TYPE_7__ {struct TYPE_7__* next; } ;
struct TYPE_6__ {TYPE_2__* sentinel; } ;

/* Variables and functions */
 int /*<<< orphan*/  xmlLinkDeallocator (TYPE_1__*,TYPE_2__*) ; 

void
xmlListClear(xmlListPtr l)
{
    xmlLinkPtr  lk;

    if (l == NULL)
        return;
    lk = l->sentinel->next;
    while(lk != l->sentinel) {
        xmlLinkPtr next = lk->next;

        xmlLinkDeallocator(l, lk);
        lk = next;
    }
}