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
struct TYPE_5__ {int type; void* ptr; } ;
struct TYPE_4__ {int flags; int amqueue_used; scalar_t__ amqueue_len; TYPE_2__* amqueue; } ;
typedef  TYPE_1__ RedisModuleCtx ;

/* Variables and functions */
#define  REDISMODULE_AM_DICT 131 
#define  REDISMODULE_AM_KEY 130 
#define  REDISMODULE_AM_REPLY 129 
#define  REDISMODULE_AM_STRING 128 
 int REDISMODULE_CTX_AUTO_MEMORY ; 
 int /*<<< orphan*/  RM_CloseKey (void*) ; 
 int /*<<< orphan*/  RM_FreeCallReply (void*) ; 
 int /*<<< orphan*/  RM_FreeDict (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  decrRefCount (void*) ; 
 int /*<<< orphan*/  zfree (TYPE_2__*) ; 

void autoMemoryCollect(RedisModuleCtx *ctx) {
    if (!(ctx->flags & REDISMODULE_CTX_AUTO_MEMORY)) return;
    /* Clear the AUTO_MEMORY flag from the context, otherwise the functions
     * we call to free the resources, will try to scan the auto release
     * queue to mark the entries as freed. */
    ctx->flags &= ~REDISMODULE_CTX_AUTO_MEMORY;
    int j;
    for (j = 0; j < ctx->amqueue_used; j++) {
        void *ptr = ctx->amqueue[j].ptr;
        switch(ctx->amqueue[j].type) {
        case REDISMODULE_AM_STRING: decrRefCount(ptr); break;
        case REDISMODULE_AM_REPLY: RM_FreeCallReply(ptr); break;
        case REDISMODULE_AM_KEY: RM_CloseKey(ptr); break;
        case REDISMODULE_AM_DICT: RM_FreeDict(NULL,ptr); break;
        }
    }
    ctx->flags |= REDISMODULE_CTX_AUTO_MEMORY;
    zfree(ctx->amqueue);
    ctx->amqueue = NULL;
    ctx->amqueue_len = 0;
    ctx->amqueue_used = 0;
}