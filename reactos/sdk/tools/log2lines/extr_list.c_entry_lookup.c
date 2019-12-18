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
struct TYPE_6__ {TYPE_1__* phead; } ;
struct TYPE_5__ {struct TYPE_5__* pnext; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__* PLIST_MEMBER ;
typedef  TYPE_2__* PLIST ;

/* Variables and functions */
 scalar_t__ PATHCMP (char*,int /*<<< orphan*/ ) ; 

PLIST_MEMBER
entry_lookup(PLIST list, char *name)
{
    PLIST_MEMBER pprev = NULL;
    PLIST_MEMBER pnext;

    if (!name || !name[0])
        return NULL;

    pnext = list->phead;
    while (pnext != NULL)
    {
        if (PATHCMP(name, pnext->name) == 0)
        {
            if (pprev)
            {   // move to head for faster lookup next time
                pprev->pnext = pnext->pnext;
                pnext->pnext = list->phead;
                list->phead = pnext;
            }
            return pnext;
        }
        pprev = pnext;
        pnext = pnext->pnext;
    }
    return NULL;
}