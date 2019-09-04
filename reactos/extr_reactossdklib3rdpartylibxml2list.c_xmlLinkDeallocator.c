#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* xmlListPtr ;
typedef  TYPE_4__* xmlLinkPtr ;
struct TYPE_12__ {TYPE_2__* prev; TYPE_1__* next; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* linkDeallocator ) (TYPE_4__*) ;} ;
struct TYPE_10__ {TYPE_1__* next; } ;
struct TYPE_9__ {TYPE_2__* prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 
 int /*<<< orphan*/  xmlFree (TYPE_4__*) ; 

__attribute__((used)) static void
xmlLinkDeallocator(xmlListPtr l, xmlLinkPtr lk)
{
    (lk->prev)->next = lk->next;
    (lk->next)->prev = lk->prev;
    if(l->linkDeallocator)
        l->linkDeallocator(lk);
    xmlFree(lk);
}