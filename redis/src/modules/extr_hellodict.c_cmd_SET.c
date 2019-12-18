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
 int /*<<< orphan*/  RedisModule_DictSet (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int RedisModule_ReplyWithSimpleString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  RedisModule_RetainString (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int RedisModule_WrongArity (int /*<<< orphan*/ *) ; 

int cmd_SET(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    if (argc != 3) return RedisModule_WrongArity(ctx);
    RedisModule_DictSet(Keyspace,argv[1],argv[2]);
    /* We need to keep a reference to the value stored at the key, otherwise
     * it would be freed when this callback returns. */
    RedisModule_RetainString(NULL,argv[2]);
    return RedisModule_ReplyWithSimpleString(ctx, "OK");
}