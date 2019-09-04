#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  client ;
struct TYPE_5__ {int flags; int /*<<< orphan*/ * client; TYPE_1__* blocked_client; } ;
struct TYPE_4__ {int /*<<< orphan*/ * reply_client; } ;
typedef  TYPE_2__ RedisModuleCtx ;

/* Variables and functions */
 int REDISMODULE_CTX_THREAD_SAFE ; 

client *moduleGetReplyClient(RedisModuleCtx *ctx) {
    if (ctx->flags & REDISMODULE_CTX_THREAD_SAFE) {
        if (ctx->blocked_client)
            return ctx->blocked_client->reply_client;
        else
            return NULL;
    } else {
        /* If this is a non thread safe context, just return the client
         * that is running the command if any. This may be NULL as well
         * in the case of contexts that are not executed with associated
         * clients, like timer contexts. */
        return ctx->client;
    }
}