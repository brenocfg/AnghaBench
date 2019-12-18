#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  client ;
struct TYPE_4__ {int postponed_arrays_count; int /*<<< orphan*/ * postponed_arrays; } ;
typedef  TYPE_1__ RedisModuleCtx ;

/* Variables and functions */
 int REDISMODULE_OK ; 
 long REDISMODULE_POSTPONED_ARRAY_LEN ; 
 int /*<<< orphan*/  addReplyArrayLen (int /*<<< orphan*/ *,long) ; 
 int /*<<< orphan*/  addReplyDeferredLen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * moduleGetReplyClient (TYPE_1__*) ; 
 int /*<<< orphan*/ * zrealloc (int /*<<< orphan*/ *,int) ; 

int RM_ReplyWithArray(RedisModuleCtx *ctx, long len) {
    client *c = moduleGetReplyClient(ctx);
    if (c == NULL) return REDISMODULE_OK;
    if (len == REDISMODULE_POSTPONED_ARRAY_LEN) {
        ctx->postponed_arrays = zrealloc(ctx->postponed_arrays,sizeof(void*)*
                (ctx->postponed_arrays_count+1));
        ctx->postponed_arrays[ctx->postponed_arrays_count] =
            addReplyDeferredLen(c);
        ctx->postponed_arrays_count++;
    } else {
        addReplyArrayLen(c,len);
    }
    return REDISMODULE_OK;
}