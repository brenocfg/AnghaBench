#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * client; int /*<<< orphan*/  module; } ;
struct TYPE_9__ {TYPE_3__* ctx; TYPE_1__* type; } ;
struct TYPE_8__ {int /*<<< orphan*/  module; } ;
typedef  TYPE_2__ RedisModuleIO ;
typedef  TYPE_3__ RedisModuleCtx ;

/* Variables and functions */
 TYPE_3__ REDISMODULE_CTX_INIT ; 
 TYPE_3__* zmalloc (int) ; 

RedisModuleCtx *RM_GetContextFromIO(RedisModuleIO *io) {
    if (io->ctx) return io->ctx; /* Can't have more than one... */
    RedisModuleCtx ctxtemplate = REDISMODULE_CTX_INIT;
    io->ctx = zmalloc(sizeof(RedisModuleCtx));
    *(io->ctx) = ctxtemplate;
    io->ctx->module = io->type->module;
    io->ctx->client = NULL;
    return io->ctx;
}