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
typedef  int* sds ;
struct TYPE_4__ {int* proto; int /*<<< orphan*/  type; int /*<<< orphan*/  flags; int /*<<< orphan*/  protolen; int /*<<< orphan*/ * ctx; } ;
typedef  int /*<<< orphan*/  RedisModuleCtx ;
typedef  TYPE_1__ RedisModuleCallReply ;

/* Variables and functions */
 int /*<<< orphan*/  REDISMODULE_REPLYFLAG_TOPARSE ; 
 int /*<<< orphan*/  REDISMODULE_REPLY_ARRAY ; 
 int /*<<< orphan*/  REDISMODULE_REPLY_ERROR ; 
 int /*<<< orphan*/  REDISMODULE_REPLY_INTEGER ; 
 int /*<<< orphan*/  REDISMODULE_REPLY_NULL ; 
 int /*<<< orphan*/  REDISMODULE_REPLY_STRING ; 
 int /*<<< orphan*/  REDISMODULE_REPLY_UNKNOWN ; 
 int /*<<< orphan*/  sdslen (int*) ; 
 TYPE_1__* zmalloc (int) ; 

RedisModuleCallReply *moduleCreateCallReplyFromProto(RedisModuleCtx *ctx, sds proto) {
    RedisModuleCallReply *reply = zmalloc(sizeof(*reply));
    reply->ctx = ctx;
    reply->proto = proto;
    reply->protolen = sdslen(proto);
    reply->flags = REDISMODULE_REPLYFLAG_TOPARSE; /* Lazy parsing. */
    switch(proto[0]) {
    case '$':
    case '+': reply->type = REDISMODULE_REPLY_STRING; break;
    case '-': reply->type = REDISMODULE_REPLY_ERROR; break;
    case ':': reply->type = REDISMODULE_REPLY_INTEGER; break;
    case '*': reply->type = REDISMODULE_REPLY_ARRAY; break;
    default: reply->type = REDISMODULE_REPLY_UNKNOWN; break;
    }
    if ((proto[0] == '*' || proto[0] == '$') && proto[1] == '-')
        reply->type = REDISMODULE_REPLY_NULL;
    return reply;
}