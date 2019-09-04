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
typedef  int /*<<< orphan*/  RedisModuleString ;
typedef  int /*<<< orphan*/  RedisModuleCtx ;
typedef  int /*<<< orphan*/  RedisModuleCallReply ;

/* Variables and functions */
 scalar_t__ REDISMODULE_REPLY_STRING ; 
 scalar_t__ RedisModule_CallReplyType (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RedisModule_CreateString (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/ * RedisModule_CreateStringFromCallReply (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_Log (int /*<<< orphan*/ *,char*,char*,char const*,...) ; 
 scalar_t__ RedisModule_StringCompare (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* RedisModule_StringPtrLen (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int TestAssertStringReply(RedisModuleCtx *ctx, RedisModuleCallReply *reply, char *str, size_t len) {
    RedisModuleString *mystr, *expected;

    if (RedisModule_CallReplyType(reply) != REDISMODULE_REPLY_STRING) {
        RedisModule_Log(ctx,"warning","Unexpected reply type %d",
            RedisModule_CallReplyType(reply));
        return 0;
    }
    mystr = RedisModule_CreateStringFromCallReply(reply);
    expected = RedisModule_CreateString(ctx,str,len);
    if (RedisModule_StringCompare(mystr,expected) != 0) {
        const char *mystr_ptr = RedisModule_StringPtrLen(mystr,NULL);
        const char *expected_ptr = RedisModule_StringPtrLen(expected,NULL);
        RedisModule_Log(ctx,"warning",
            "Unexpected string reply '%s' (instead of '%s')",
            mystr_ptr, expected_ptr);
        return 0;
    }
    return 1;
}