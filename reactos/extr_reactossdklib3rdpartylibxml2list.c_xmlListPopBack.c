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
typedef  TYPE_2__* xmlListPtr ;
struct TYPE_7__ {TYPE_1__* sentinel; } ;
struct TYPE_6__ {int /*<<< orphan*/  prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  xmlLinkDeallocator (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlListEmpty (TYPE_2__*) ; 

void
xmlListPopBack(xmlListPtr l)
{
    if(!xmlListEmpty(l))
        xmlLinkDeallocator(l, l->sentinel->prev);
}