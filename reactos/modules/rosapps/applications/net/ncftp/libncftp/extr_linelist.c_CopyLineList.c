#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* first; } ;
struct TYPE_8__ {int /*<<< orphan*/ * line; struct TYPE_8__* next; } ;
typedef  TYPE_1__* LinePtr ;
typedef  TYPE_2__* LineListPtr ;

/* Variables and functions */
 int /*<<< orphan*/ * AddLine (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DisposeLineListContents (TYPE_2__*) ; 
 int /*<<< orphan*/  InitLineList (TYPE_2__*) ; 

int
CopyLineList(LineListPtr dst, LineListPtr src)
{
	LinePtr lp, lp2;

	InitLineList(dst);
	for (lp = src->first; lp != NULL; ) {
		lp2 = lp;
		lp = lp->next;
		if (lp2->line != NULL) {
			if (AddLine(dst, lp2->line) == NULL) {
				DisposeLineListContents(dst);
				return (-1);
			}
		}
	}
	return (0);
}