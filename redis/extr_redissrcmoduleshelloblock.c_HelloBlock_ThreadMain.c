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
typedef  int /*<<< orphan*/  RedisModuleBlockedClient ;

/* Variables and functions */
 int* RedisModule_Alloc (int) ; 
 int /*<<< orphan*/  RedisModule_Free (void**) ; 
 int /*<<< orphan*/  RedisModule_UnblockClient (int /*<<< orphan*/ *,int*) ; 
 int rand () ; 
 int /*<<< orphan*/  sleep (long long) ; 

void *HelloBlock_ThreadMain(void *arg) {
    void **targ = arg;
    RedisModuleBlockedClient *bc = targ[0];
    long long delay = (unsigned long)targ[1];
    RedisModule_Free(targ);

    sleep(delay);
    int *r = RedisModule_Alloc(sizeof(int));
    *r = rand();
    RedisModule_UnblockClient(bc,r);
    return NULL;
}