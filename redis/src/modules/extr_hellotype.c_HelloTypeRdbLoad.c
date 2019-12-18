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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  void HelloTypeObject ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  RedisModuleIO ;

/* Variables and functions */
 int /*<<< orphan*/  HelloTypeInsert (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RedisModule_LoadSigned (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_LoadUnsigned (int /*<<< orphan*/ *) ; 
 void* createHelloTypeObject () ; 

void *HelloTypeRdbLoad(RedisModuleIO *rdb, int encver) {
    if (encver != 0) {
        /* RedisModule_Log("warning","Can't load data with version %d", encver);*/
        return NULL;
    }
    uint64_t elements = RedisModule_LoadUnsigned(rdb);
    struct HelloTypeObject *hto = createHelloTypeObject();
    while(elements--) {
        int64_t ele = RedisModule_LoadSigned(rdb);
        HelloTypeInsert(hto,ele);
    }
    return hto;
}