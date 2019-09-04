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
typedef  TYPE_1__* xmlDictPtr ;
struct TYPE_3__ {int /*<<< orphan*/  ref_counter; } ;

/* Variables and functions */
 int /*<<< orphan*/  __xmlInitializeDict () ; 
 int /*<<< orphan*/  xmlDictInitialized ; 
 int /*<<< orphan*/  xmlDictMutex ; 
 int /*<<< orphan*/  xmlRMutexLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlRMutexUnlock (int /*<<< orphan*/ ) ; 

int
xmlDictReference(xmlDictPtr dict) {
    if (!xmlDictInitialized)
        if (!__xmlInitializeDict())
            return(-1);

    if (dict == NULL) return -1;
    xmlRMutexLock(xmlDictMutex);
    dict->ref_counter++;
    xmlRMutexUnlock(xmlDictMutex);
    return(0);
}