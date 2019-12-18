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
typedef  void RedisModuleString ;
typedef  int /*<<< orphan*/  RedisModuleIO ;

/* Variables and functions */
 scalar_t__ RedisModule_IsIOError (int /*<<< orphan*/ *) ; 
 float RedisModule_LoadFloat (int /*<<< orphan*/ *) ; 
 long double RedisModule_LoadLongDouble (int /*<<< orphan*/ *) ; 
 int RedisModule_LoadSigned (int /*<<< orphan*/ *) ; 
 void* RedisModule_LoadString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 

void *testrdb_type_load(RedisModuleIO *rdb, int encver) {
    int count = RedisModule_LoadSigned(rdb);
    RedisModuleString *str = RedisModule_LoadString(rdb);
    float f = RedisModule_LoadFloat(rdb);
    long double ld = RedisModule_LoadLongDouble(rdb);
    if (RedisModule_IsIOError(rdb))
        return NULL;
    /* Using the values only after checking for io errors. */
    assert(count==1);
    assert(encver==1);
    assert(f==1.5f);
    assert(ld==0.333333333333333333L);
    return str;
}