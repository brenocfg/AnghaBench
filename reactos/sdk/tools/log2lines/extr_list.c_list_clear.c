#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * ptail; TYPE_1__* phead; } ;
struct TYPE_5__ {struct TYPE_5__* pnext; } ;
typedef  TYPE_1__* PLIST_MEMBER ;
typedef  TYPE_2__* PLIST ;

/* Variables and functions */
 int /*<<< orphan*/  entry_delete (TYPE_1__*) ; 

void list_clear(PLIST list)
{
    PLIST_MEMBER pentry = list->phead;
    PLIST_MEMBER pnext;
    while (pentry)
    {
        pnext = pentry->pnext;
        entry_delete(pentry);
        pentry = pnext;
    }
    list->phead = list->ptail = NULL;
}