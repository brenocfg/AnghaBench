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
typedef  int /*<<< orphan*/  RedisModuleCtx ;

/* Variables and functions */
 int /*<<< orphan*/  Keyspace ; 
 int /*<<< orphan*/ * RedisModule_DictGet (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int RedisModule_ReplyWithNull (int /*<<< orphan*/ *) ; 
 int RedisModule_ReplyWithString (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int RedisModule_WrongArity (int /*<<< orphan*/ *) ; 

int cmd_GET(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    if (argc != 2) return RedisModule_WrongArity(ctx);
    RedisModuleString *val = RedisModule_DictGet(Keyspace,argv[1],NULL);
    if (val == NULL) {
        return RedisModule_ReplyWithNull(ctx);
    } else {
        return RedisModule_ReplyWithString(ctx, val);
    }
}