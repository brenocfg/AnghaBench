#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  __xmlInitializeDict () ; 
 int rand () ; 
 int rand_r (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rand_seed ; 
 scalar_t__ xmlDictInitialized ; 
 int /*<<< orphan*/  xmlDictMutex ; 
 int /*<<< orphan*/  xmlRMutexLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlRMutexUnlock (int /*<<< orphan*/ ) ; 

int __xmlRandom(void) {
    int ret;

    if (xmlDictInitialized == 0)
        __xmlInitializeDict();

    xmlRMutexLock(xmlDictMutex);
#ifdef HAVE_RAND_R
    ret = rand_r(& rand_seed);
#else
    ret = rand();
#endif
    xmlRMutexUnlock(xmlDictMutex);
    return(ret);
}