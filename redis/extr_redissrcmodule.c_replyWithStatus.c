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
typedef  int /*<<< orphan*/  sds ;
typedef  int /*<<< orphan*/  client ;
typedef  int /*<<< orphan*/  RedisModuleCtx ;

/* Variables and functions */
 int REDISMODULE_OK ; 
 int /*<<< orphan*/  addReplySds (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * moduleGetReplyClient (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdscat (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  sdscatlen (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sdsnewlen (char*,int) ; 

int replyWithStatus(RedisModuleCtx *ctx, const char *msg, char *prefix) {
    client *c = moduleGetReplyClient(ctx);
    if (c == NULL) return REDISMODULE_OK;
    sds strmsg = sdsnewlen(prefix,1);
    strmsg = sdscat(strmsg,msg);
    strmsg = sdscatlen(strmsg,"\r\n",2);
    addReplySds(c,strmsg);
    return REDISMODULE_OK;
}