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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  dictEntry ;
typedef  int /*<<< orphan*/  dict ;

/* Variables and functions */
 int /*<<< orphan*/ * dictAddRaw (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 int dictGetUnsignedIntegerVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictSetUnsignedIntegerVal (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  serverAssert (int /*<<< orphan*/ ) ; 

int sentinelLeaderIncr(dict *counters, char *runid) {
    dictEntry *existing, *de;
    uint64_t oldval;

    de = dictAddRaw(counters,runid,&existing);
    if (existing) {
        oldval = dictGetUnsignedIntegerVal(existing);
        dictSetUnsignedIntegerVal(existing,oldval+1);
        return oldval+1;
    } else {
        serverAssert(de != NULL);
        dictSetUnsignedIntegerVal(de,1);
        return 1;
    }
}