#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int count; TYPE_1__** value; } ;
struct TYPE_9__ {int rtfKHash; int /*<<< orphan*/ * rtfKStr; } ;
typedef  TYPE_1__ RTFKey ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int Hash (int /*<<< orphan*/ *) ; 
 TYPE_1__** heap_alloc (int) ; 
 TYPE_1__** heap_realloc (TYPE_1__**,int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* rtfHashTable ; 
 TYPE_1__* rtfKey ; 

void LookupInit(void)
{
	RTFKey	*rp;

	memset(rtfHashTable, 0, sizeof rtfHashTable);
	for (rp = rtfKey; rp->rtfKStr != NULL; rp++)
	{
		int index;

		rp->rtfKHash = Hash (rp->rtfKStr);
		index = rp->rtfKHash % (ARRAY_SIZE(rtfKey) * 2);
		if (!rtfHashTable[index].count)
			rtfHashTable[index].value = heap_alloc(sizeof(RTFKey *));
		else
			rtfHashTable[index].value = heap_realloc(rtfHashTable[index].value, sizeof(RTFKey *) * (rtfHashTable[index].count + 1));
		rtfHashTable[index].value[rtfHashTable[index].count++] = rp;
	}
}