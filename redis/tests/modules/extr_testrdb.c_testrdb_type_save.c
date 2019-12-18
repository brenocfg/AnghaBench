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
typedef  int /*<<< orphan*/  RedisModuleString ;
typedef  int /*<<< orphan*/  RedisModuleIO ;

/* Variables and functions */
 int /*<<< orphan*/  RedisModule_SaveFloat (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  RedisModule_SaveLongDouble (int /*<<< orphan*/ *,long double) ; 
 int /*<<< orphan*/  RedisModule_SaveSigned (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RedisModule_SaveString (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void testrdb_type_save(RedisModuleIO *rdb, void *value) {
    RedisModuleString *str = (RedisModuleString*)value;
    RedisModule_SaveSigned(rdb, 1);
    RedisModule_SaveString(rdb, str);
    RedisModule_SaveFloat(rdb, 1.5);
    RedisModule_SaveLongDouble(rdb, 0.333333333333333333L);
}