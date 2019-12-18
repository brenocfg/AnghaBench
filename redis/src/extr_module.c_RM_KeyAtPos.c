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
struct TYPE_3__ {int flags; int* keys_pos; int keys_count; } ;
typedef  TYPE_1__ RedisModuleCtx ;

/* Variables and functions */
 int REDISMODULE_CTX_KEYS_POS_REQUEST ; 
 int* zrealloc (int*,int) ; 

void RM_KeyAtPos(RedisModuleCtx *ctx, int pos) {
    if (!(ctx->flags & REDISMODULE_CTX_KEYS_POS_REQUEST)) return;
    if (pos <= 0) return;
    ctx->keys_pos = zrealloc(ctx->keys_pos,sizeof(int)*(ctx->keys_count+1));
    ctx->keys_pos[ctx->keys_count++] = pos;
}