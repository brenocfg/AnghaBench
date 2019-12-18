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
 int /*<<< orphan*/  rand_r (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rand_seed ; 
 int /*<<< orphan*/  srand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int xmlDictInitialized ; 
 int /*<<< orphan*/ * xmlDictMutex ; 
 int /*<<< orphan*/ * xmlNewRMutex () ; 
 int /*<<< orphan*/  xmlRMutexLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlRMutexUnlock (int /*<<< orphan*/ *) ; 

int __xmlInitializeDict(void) {
    if (xmlDictInitialized)
        return(1);

    if ((xmlDictMutex = xmlNewRMutex()) == NULL)
        return(0);
    xmlRMutexLock(xmlDictMutex);

#ifdef DICT_RANDOMIZATION
#ifdef HAVE_RAND_R
    rand_seed = time(NULL);
    rand_r(& rand_seed);
#else
    srand(time(NULL));
#endif
#endif
    xmlDictInitialized = 1;
    xmlRMutexUnlock(xmlDictMutex);
    return(1);
}