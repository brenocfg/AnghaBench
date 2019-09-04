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
 int REDISMODULE_OK ; 
 int /*<<< orphan*/  RedisModule_Call (int /*<<< orphan*/ *,char*,char*,char*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  RedisModule_Log (int /*<<< orphan*/ *,char*,char*,int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RedisModule_StringPtrLen (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int NotifyCallback(RedisModuleCtx *ctx, int type, const char *event,
                   RedisModuleString *key) {
  /* Increment a counter on the notifications: for each key notified we
   * increment a counter */
  RedisModule_Log(ctx, "notice", "Got event type %d, event %s, key %s", type,
                  event, RedisModule_StringPtrLen(key, NULL));

  RedisModule_Call(ctx, "HINCRBY", "csc", "notifications", key, "1");
  return REDISMODULE_OK;
}