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
 int /*<<< orphan*/  MSGTYPE_PING ; 
 int /*<<< orphan*/  REDISMODULE_NOT_USED (int) ; 
 int RedisModule_ReplyWithSimpleString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  RedisModule_SendClusterMessage (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*,int) ; 

int PingallCommand_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    REDISMODULE_NOT_USED(argv);
    REDISMODULE_NOT_USED(argc);

    RedisModule_SendClusterMessage(ctx,NULL,MSGTYPE_PING,(unsigned char*)"Hey",3);
    return RedisModule_ReplyWithSimpleString(ctx, "OK");
}