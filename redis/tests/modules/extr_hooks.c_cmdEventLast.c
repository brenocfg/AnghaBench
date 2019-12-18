#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  last_val_int; scalar_t__ last_val_string; } ;
typedef  int /*<<< orphan*/  RedisModuleString ;
typedef  int /*<<< orphan*/  RedisModuleCtx ;
typedef  TYPE_1__ EventElement ;

/* Variables and functions */
 int REDISMODULE_OK ; 
 TYPE_1__* RedisModule_DictGet (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_ReplyWithLongLong (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RedisModule_ReplyWithNull (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_ReplyWithString (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  RedisModule_WrongArity (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_log ; 

int cmdEventLast(RedisModuleCtx *ctx, RedisModuleString **argv, int argc)
{
    if (argc != 2){
        RedisModule_WrongArity(ctx);
        return REDISMODULE_OK;
    }

    EventElement *event = RedisModule_DictGet(event_log, argv[1], NULL);
    if (event && event->last_val_string)
        RedisModule_ReplyWithString(ctx, event->last_val_string);
    else if (event)
        RedisModule_ReplyWithLongLong(ctx, event->last_val_int);
    else
        RedisModule_ReplyWithNull(ctx);
    return REDISMODULE_OK;
}