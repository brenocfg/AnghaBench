#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__** argv; } ;
struct TYPE_6__ {TYPE_3__* client; } ;
struct TYPE_5__ {scalar_t__ ptr; } ;
typedef  TYPE_2__ RedisModuleCtx ;

/* Variables and functions */
 int REDISMODULE_OK ; 
 int /*<<< orphan*/  addReplyErrorFormat (TYPE_3__*,char*,char*) ; 

int RM_WrongArity(RedisModuleCtx *ctx) {
    addReplyErrorFormat(ctx->client,
        "wrong number of arguments for '%s' command",
        (char*)ctx->client->argv[0]->ptr);
    return REDISMODULE_OK;
}