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
struct evictionPoolEntry {scalar_t__ dbid; int /*<<< orphan*/  cached; int /*<<< orphan*/ * key; scalar_t__ idle; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVPOOL_CACHED_SDS_SIZE ; 
 int EVPOOL_SIZE ; 
 struct evictionPoolEntry* EvictionPoolLRU ; 
 int /*<<< orphan*/  sdsnewlen (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct evictionPoolEntry* zmalloc (int) ; 

void evictionPoolAlloc(void) {
    struct evictionPoolEntry *ep;
    int j;

    ep = zmalloc(sizeof(*ep)*EVPOOL_SIZE);
    for (j = 0; j < EVPOOL_SIZE; j++) {
        ep[j].idle = 0;
        ep[j].key = NULL;
        ep[j].cached = sdsnewlen(NULL,EVPOOL_CACHED_SDS_SIZE);
        ep[j].dbid = 0;
    }
    EvictionPoolLRU = ep;
}