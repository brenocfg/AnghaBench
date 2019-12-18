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
typedef  int /*<<< orphan*/  client ;
typedef  int /*<<< orphan*/  RedisModuleCtx ;

/* Variables and functions */
 int REDISMODULE_OK ; 
 int /*<<< orphan*/  addReplyProto (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/ * moduleGetReplyClient (int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 

int replyWithStatus(RedisModuleCtx *ctx, const char *msg, char *prefix) {
    client *c = moduleGetReplyClient(ctx);
    if (c == NULL) return REDISMODULE_OK;
    addReplyProto(c,prefix,strlen(prefix));
    addReplyProto(c,msg,strlen(msg));
    addReplyProto(c,"\r\n",2);
    return REDISMODULE_OK;
}