#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  array ;
struct TYPE_6__ {struct TYPE_6__* next; struct TYPE_6__* down; } ;
typedef  size_t SORT_ORDER ;
typedef  TYPE_1__ Entry ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__** HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  qsort (TYPE_1__**,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sortFunctions ; 

__attribute__((used)) static void SortDirectory(Entry* dir, SORT_ORDER sortOrder)
{
	Entry* entry;
	Entry** array, **p;
	int len;

	len = 0;
	for(entry=dir->down; entry; entry=entry->next)
		len++;

	if (len) {
		array = HeapAlloc(GetProcessHeap(), 0, len*sizeof(Entry*));

		p = array;
		for(entry=dir->down; entry; entry=entry->next)
			*p++ = entry;

		/* call qsort with the appropriate compare function */
		qsort(array, len, sizeof(array[0]), sortFunctions[sortOrder]);

		dir->down = array[0];

		for(p=array; --len; p++)
			p[0]->next = p[1];

		(*p)->next = 0;

                HeapFree(GetProcessHeap(), 0, array);
	}
}