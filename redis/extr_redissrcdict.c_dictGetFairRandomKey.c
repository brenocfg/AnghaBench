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
typedef  int /*<<< orphan*/  dictEntry ;
typedef  int /*<<< orphan*/  dict ;

/* Variables and functions */
 int GETFAIR_NUM_ENTRIES ; 
 int /*<<< orphan*/ * dictGetRandomKey (int /*<<< orphan*/ *) ; 
 unsigned int dictGetSomeKeys (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int) ; 
 unsigned int rand () ; 

dictEntry *dictGetFairRandomKey(dict *d) {
    dictEntry *entries[GETFAIR_NUM_ENTRIES];
    unsigned int count = dictGetSomeKeys(d,entries,GETFAIR_NUM_ENTRIES);
    /* Note that dictGetSomeKeys() may return zero elements in an unlucky
     * run() even if there are actually elements inside the hash table. So
     * when we get zero, we call the true dictGetRandomKey() that will always
     * yeld the element if the hash table has at least one. */
    if (count == 0) return dictGetRandomKey(d);
    unsigned int idx = rand() % count;
    return entries[idx];
}