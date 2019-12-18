#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  char* sds ;
struct TYPE_3__ {char* value; } ;
typedef  TYPE_1__ listNode ;
typedef  int /*<<< orphan*/  listIter ;
typedef  int /*<<< orphan*/  list ;

/* Variables and functions */
 TYPE_1__* listNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRewind (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void clusterManagerPrintSlotsList(list *slots) {
    listIter li;
    listNode *ln;
    listRewind(slots, &li);
    sds first = NULL;
    while ((ln = listNext(&li)) != NULL) {
        sds slot = ln->value;
        if (!first) first = slot;
        else printf(", ");
        printf("%s", slot);
    }
    printf("\n");
}