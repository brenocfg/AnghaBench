#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* value; struct TYPE_4__* key; struct TYPE_4__* nextPtr; } ;
typedef  TYPE_1__ list_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void
list_free(list_item_t **listPtrPtr)
{
    list_item_t *tmpPtr, *listPtr = *listPtrPtr;
    while (listPtr) {
	tmpPtr = listPtr;
	listPtr = listPtr->nextPtr;
	free(tmpPtr->key);
	free(tmpPtr->value);
	free(tmpPtr);
    }
}