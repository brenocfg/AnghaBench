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
typedef  int RedisModuleTimerID ;
typedef  int /*<<< orphan*/  RedisModuleString ;
typedef  int /*<<< orphan*/  RedisModuleCtx ;

/* Variables and functions */
 int /*<<< orphan*/  REDISMODULE_NOT_USED (int) ; 
 char* RedisModule_Alloc (int) ; 
 int RedisModule_CreateTimer (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*) ; 
 int RedisModule_ReplyWithSimpleString (int /*<<< orphan*/ *,char*) ; 
 int rand () ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  timerHandler ; 

int TimerCommand_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    REDISMODULE_NOT_USED(argv);
    REDISMODULE_NOT_USED(argc);

    for (int j = 0; j < 10; j++) {
        int delay = rand() % 5000;
        char *buf = RedisModule_Alloc(256);
        snprintf(buf,256,"After %d", delay);
        RedisModuleTimerID tid = RedisModule_CreateTimer(ctx,delay,timerHandler,buf);
        REDISMODULE_NOT_USED(tid);
    }
    return RedisModule_ReplyWithSimpleString(ctx, "OK");
}