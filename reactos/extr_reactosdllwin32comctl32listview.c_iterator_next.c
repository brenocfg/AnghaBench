#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int upper; int lower; } ;
struct TYPE_7__ {int nItem; int nSpecial; scalar_t__ index; TYPE_2__ range; TYPE_1__* ranges; } ;
struct TYPE_5__ {int /*<<< orphan*/  hdpa; } ;
typedef  TYPE_2__ RANGE ;
typedef  TYPE_3__ ITERATOR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ DPA_GetPtr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ DPA_GetPtrCount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static inline BOOL iterator_next(ITERATOR* i)
{
    if (i->nItem == -1)
    {
	i->nItem = i->nSpecial;
	if (i->nItem != -1) return TRUE;
    }
    if (i->nItem == i->nSpecial)
    {
	if (i->ranges) i->index = 0;
	goto pickarange;
    }

    i->nItem++;
testitem:
    if (i->nItem == i->nSpecial) i->nItem++;
    if (i->nItem < i->range.upper) return TRUE;

pickarange:
    if (i->ranges)
    {
	if (i->index < DPA_GetPtrCount(i->ranges->hdpa))
	    i->range = *(RANGE*)DPA_GetPtr(i->ranges->hdpa, i->index++);
	else goto end;
    }
    else if (i->nItem >= i->range.upper) goto end;

    i->nItem = i->range.lower;
    if (i->nItem >= 0) goto testitem;
end:
    i->nItem = -1;
    return FALSE;
}